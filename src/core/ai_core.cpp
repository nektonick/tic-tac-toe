#include "ai_core.h"
#include <algorithm>
#include <cmath> // std::pow
#include <thread> // for sleep
#include "player.h"

constexpr int aphaBetaMin = std::numeric_limits<int>::min();
constexpr int aphaBetaMax = std::numeric_limits<int>::max();
constexpr int maxDepth = 5; // TODO: experiment with this value
constexpr bool limitMaxDepth = true;

AI_Core::AI_Core(std::shared_ptr<Field> field)
    : field_(field)
{
}

CellPosition AI_Core::makeMove(MarkType currentPlayerMark)
{
    ourMark_ = currentPlayerMark;
    return getBestMove();
}

CellPosition AI_Core::getBestMove()
{
    const int aphaValue = aphaBetaMin;
    const int betaValue = aphaBetaMax;
    bool isCurrentPlayerMove = true;
    const int currentDepth = 0;

    minMaxCallsCount = 0;
    // Here we ignore the output value of minimax func
    minimax(isCurrentPlayerMove, currentDepth, aphaValue, betaValue);

    std::cout << "Minimax took " << minMaxCallsCount << " tries" << std::endl; // For debug only
    // Add some delay (useful when two AI play)
    if(minMaxCallsCount < 10000) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    return currentBestMove;
}

AI_Core::Score AI_Core::minimax(bool isOurMove, int currentDepth, int alpha, int beta)
{
    // TODO: try to improve performance
    minMaxCallsCount++;
    const MarkType oponentMark = ourMark_ == MarkType::x ? MarkType::o : MarkType::x;
    const bool isCurrentPlayerWin = field_->isPlayerWin(ourMark_);
    const bool isOpponentWin = field_->isPlayerWin(oponentMark);
    const bool isGameEnded = isCurrentPlayerWin || isOpponentWin || field_->isAllCellsMarked();
    if(isGameEnded || (limitMaxDepth && (currentDepth > maxDepth))) {
        return getCurrentStateScore(isCurrentPlayerWin, isOpponentWin, isGameEnded, currentDepth);
    }

    auto possibleMoves = field_->getEmptyCells();
    std::vector<int> moveScores;
    moveScores.reserve(possibleMoves.size());
    for(const auto& move : possibleMoves) {
        int x = move.getRow();
        int y = move.getColumn();

        const auto marker = isOurMove ? ourMark_ : oponentMark;
        field_->markCell({x, y}, marker);
        int curentMoveScore = minimax(!isOurMove, currentDepth + 1, alpha, beta);
        moveScores.push_back(curentMoveScore);
        field_->unmarkCell({x, y});

        // pruning
        if(isOurMove) {
            int maxValue = std::max(aphaBetaMin, curentMoveScore);
            alpha = std::max(alpha, maxValue);
            if(alpha > beta) {
                return maxValue;
            }
        } else {
            int minValue = std::min(aphaBetaMax, curentMoveScore);
            beta = std::min(beta, minValue);
            if(beta < alpha) {
                return minValue;
            }
        }
    }

    int scoreIndex = 0;
    if(isOurMove) {
        scoreIndex = std::max_element(moveScores.cbegin(), moveScores.cend()) - moveScores.cbegin();
    } else {
        scoreIndex = std::min_element(moveScores.cbegin(), moveScores.cend()) - moveScores.cbegin();
    }
    currentBestMove = possibleMoves[scoreIndex];

    return moveScores.at(scoreIndex);
}

AI_Core::Score AI_Core::getCurrentStateScore(bool isPlayerWin, bool isOpponentWin, bool isGameEnded, int currentDepth)
{
    if(isGameEnded) {
        const uint64_t fieldSize = field_->getFieldSize().getColumnsCount() * field_->getFieldSize().getRowsCount();
        if(isPlayerWin) {
            return fieldSize - currentDepth;
        }
        if(isOpponentWin) {
            return -fieldSize + currentDepth;
        }
        // If game ended in a draw return 0
        return 0;
    }


    // TODO: experiment with different evaluation functions
    const auto rowsCount = field_->getFieldSize().getRowsCount();
    const auto columnsCount = field_->getFieldSize().getColumnsCount();
    uint32_t maxNumberOfOurMarksInRow = 0;
    uint32_t maxNumberOfOpponentMarksInRow = 0;

    // rows:
    for(uint32_t row = 0; row < rowsCount; ++row) {
        uint32_t numberOfOurMarksInRow = 0;
        uint32_t numberOfOpponentMarksInRow = 0;
        for(uint32_t column = 0; column < columnsCount; ++column) {
            auto currentMark = field_->getCellMark(CellPosition{row, column});
            if(currentMark.has_value()) {
                if(currentMark.value() == ourMark_) {
                    numberOfOurMarksInRow += 1;
                    numberOfOpponentMarksInRow = 0;
                } else {
                    numberOfOpponentMarksInRow += 1;
                    numberOfOurMarksInRow = 0;
                }
            } else {
                numberOfOurMarksInRow = 0;
                numberOfOpponentMarksInRow = 0;
            }
            if(numberOfOurMarksInRow > maxNumberOfOurMarksInRow) {
                maxNumberOfOurMarksInRow = numberOfOurMarksInRow;
            }
            if(numberOfOpponentMarksInRow > maxNumberOfOpponentMarksInRow) {
                maxNumberOfOpponentMarksInRow = numberOfOpponentMarksInRow;
            }
        }
    }

    // columns:
    for(uint32_t column = 0; column < columnsCount; ++column) {
        uint32_t numberOfOurMarksInRow = 0;
        uint32_t numberOfOpponentMarksInRow = 0;
        for(uint32_t row = 0; row < rowsCount; ++row) {
            auto currentMark = field_->getCellMark(CellPosition{row, column});
            if(currentMark.has_value()) {
                if(currentMark.value() == ourMark_) {
                    numberOfOurMarksInRow += 1;
                    numberOfOpponentMarksInRow = 0;
                } else {
                    numberOfOpponentMarksInRow += 1;
                    numberOfOurMarksInRow = 0;
                }
            } else {
                numberOfOurMarksInRow = 0;
                numberOfOpponentMarksInRow = 0;
            }
            if(numberOfOurMarksInRow > maxNumberOfOurMarksInRow) {
                maxNumberOfOurMarksInRow = numberOfOurMarksInRow;
            }
            if(numberOfOpponentMarksInRow > maxNumberOfOpponentMarksInRow) {
                maxNumberOfOpponentMarksInRow = numberOfOpponentMarksInRow;
            }
        }
    }

    // diagonals:
    using vectorOfMarks = std::vector<std::optional<MarkType>>;
    const size_t diagonalsCount = rowsCount + columnsCount - 1;
    std::vector<vectorOfMarks> diagonalMarks(diagonalsCount, vectorOfMarks{});
    std::vector<vectorOfMarks> backwardDiagonalMarks(diagonalsCount, vectorOfMarks{});
    for(uint32_t row = 0; row < rowsCount; ++row) {
        for(uint32_t column = 0; column < columnsCount; ++column) {
            auto currentMark = field_->getCellMark(CellPosition{row, column});
            diagonalMarks[row + column].push_back(currentMark);
            backwardDiagonalMarks[row + (columnsCount - 1 - column)].push_back(currentMark);
        }
    }
    for(const auto& diagonal : diagonalMarks) {
        uint32_t numberOfOurMarksInRow = 0;
        uint32_t numberOfOpponentMarksInRow = 0;
        for(const auto& currentMark : diagonal) {
            if(currentMark.has_value()) {
                if(currentMark.value() == ourMark_) {
                    numberOfOurMarksInRow += 1;
                    numberOfOpponentMarksInRow = 0;
                } else {
                    numberOfOpponentMarksInRow += 1;
                    numberOfOurMarksInRow = 0;
                }
            } else {
                numberOfOurMarksInRow = 0;
                numberOfOpponentMarksInRow = 0;
            }
            if(numberOfOurMarksInRow > maxNumberOfOurMarksInRow) {
                maxNumberOfOurMarksInRow = numberOfOurMarksInRow;
            }
            if(numberOfOpponentMarksInRow > maxNumberOfOpponentMarksInRow) {
                maxNumberOfOpponentMarksInRow = numberOfOpponentMarksInRow;
            }
        }
    }
    // Same for backward diagonals
    for(const auto& diagonal : backwardDiagonalMarks) {
        uint32_t numberOfOurMarksInRow = 0;
        uint32_t numberOfOpponentMarksInRow = 0;
        for(const auto& currentMark : diagonal) {
            if(currentMark.has_value()) {
                if(currentMark.value() == ourMark_) {
                    numberOfOurMarksInRow += 1;
                    numberOfOpponentMarksInRow = 0;
                } else {
                    numberOfOpponentMarksInRow += 1;
                    numberOfOurMarksInRow = 0;
                }
            } else {
                numberOfOurMarksInRow = 0;
                numberOfOpponentMarksInRow = 0;
            }
            if(numberOfOurMarksInRow > maxNumberOfOurMarksInRow) {
                maxNumberOfOurMarksInRow = numberOfOurMarksInRow;
            }
            if(numberOfOpponentMarksInRow > maxNumberOfOpponentMarksInRow) {
                maxNumberOfOpponentMarksInRow = numberOfOpponentMarksInRow;
            }
        }
    }

    return maxNumberOfOurMarksInRow - maxNumberOfOpponentMarksInRow;
}
