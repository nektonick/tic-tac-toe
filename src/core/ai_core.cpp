#include "ai_core.h"
#include <algorithm>
#include <thread> // for sleep
#include "player.h"

constexpr int aphaBetaMin = std::numeric_limits<int>::min();
constexpr int aphaBetaMax = std::numeric_limits<int>::max();

AI_Core::AI_Core(std::shared_ptr<Field> field)
    : field_(field)
{
}

CellPosition AI_Core::makeMove(MarkType currentPlayerMark)
{
    return getBestMove(currentPlayerMark);
}

CellPosition AI_Core::getBestMove(MarkType currentPlayerMark)
{
    const int aphaValue = aphaBetaMin;
    const int betaValue = aphaBetaMax;
    bool isCurrentPlayerMove = true;
    const int depth = 0;

    minMaxCallsCount = 0;
    // Here we ignore the output value of minimax func
    minimax(currentPlayerMark, isCurrentPlayerMove, depth, aphaValue, betaValue);

    std::cout << "Minimax took " << minMaxCallsCount << " tries" << std::endl; // For debug only
    // Add some delay (useful when two AI play)
    if(minMaxCallsCount < 10000) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    return currentBestMove;
}

AI_Core::CellScore AI_Core::minimax(MarkType currentPlayerMark, bool isCurrentPlayerMove, int depth, int alpha, int beta)
{
    minMaxCallsCount++;
    const MarkType oponentMark = currentPlayerMark == MarkType::x ? MarkType::o : MarkType::x;
    const bool isCurrentPlayerWin = field_->isPlayerWin(currentPlayerMark);
    const bool isOpponentWin = field_->isPlayerWin(oponentMark);
    const bool isGameEnded = isCurrentPlayerWin || isOpponentWin || field_->isAllCellsMarked();
    if(isGameEnded) {
        const uint64_t fieldSize = field_->getFieldSize().getColumnsCount() * field_->getFieldSize().getRowsCount();
        if(isCurrentPlayerWin) {
            return fieldSize - depth;
        }
        if(isOpponentWin) {
            return -fieldSize + depth;
        }
        // If game ended in a draw return 0
        return 0;
    }

    auto possibleMoves = field_->getEmptyCells();
    std::vector<int> moveScores;
    moveScores.reserve(possibleMoves.size());
    for(const auto& move : possibleMoves) {
        int x = move.getRow();
        int y = move.getColumn();

        const auto marker = isCurrentPlayerMove ? currentPlayerMark : oponentMark;
        field_->markCell({x, y}, marker);
        int curentMoveScore = minimax(currentPlayerMark, !isCurrentPlayerMove, depth + 1, alpha, beta);
        moveScores.push_back(curentMoveScore);
        field_->unmarkCell({x, y});

        // pruning
        if(isCurrentPlayerMove) {
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
    if(isCurrentPlayerMove) {
        scoreIndex = std::max_element(moveScores.cbegin(), moveScores.cend()) - moveScores.cbegin();
    } else {
        scoreIndex = std::min_element(moveScores.cbegin(), moveScores.cend()) - moveScores.cbegin();
    }
    currentBestMove = possibleMoves[scoreIndex];

    return moveScores.at(scoreIndex);
}
