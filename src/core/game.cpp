#include "game.h"

Game::Game(std::unique_ptr<I_InputOutput> input_output)
    : input_output_(std::move(input_output))
    , field_(std::make_shared<Field>())
{
    if(input_output_ == nullptr) {
        throw std::invalid_argument("Unexpected nullptr: 'input_output'");
    }
    player1_ = PlayersFabric::getPlayerOfType(input_output_->getPlayerType("First player type"), MarkType::x, input_output_, field_);
    player2_ = PlayersFabric::getPlayerOfType(input_output_->getPlayerType("Second player type"), MarkType::o, input_output_, field_);
}

void Game::play()
{
    try {
        restart();
        while(gameShouldBeContinued()) {
            doTurn();
            updateStatusAfterTurn();
        }
        processGameEnd();
    } catch(const std::exception& e) {
        input_output_->showMessage(std::string("Error: ") + e.what());
        // TODO: ask about restart
    }
}

void Game::restart()
{
    auto newSize = input_output_->readFieldSize();
    auto maxAllowedCellsInRowToWinCount = std::max(newSize.getColumnsCount(), newSize.getRowsCount()); // TODO: validate
    cellsInRowToWin_ = input_output_->getCellsInRowToWinCount(maxAllowedCellsInRowToWinCount);
    field_->reset(newSize);
    is_player1_turn_ = true;
    turn_number_ = 0;
    status_ = Game::Status::should_be_continued;
    input_output_->initField(field_);
    input_output_->updateField(field_);
}

bool Game::gameShouldBeContinued() const noexcept
{
    return status_ == Status::should_be_continued;
}

void Game::doTurn()
{
    auto& current_player = is_player1_turn_ ? player1_ : player2_;
    current_player->doTurn();
}

void Game::updateStatusAfterTurn()
{
    status_ = getNewStatus(is_player1_turn_);
    ++turn_number_;
    is_player1_turn_ = !is_player1_turn_;
}
Game::Status Game::getNewStatus(bool isPlayer1JustEndItsTurn)
{
    /* Cases:
     * - all cells marked
     *   - some player win
     *   - game ended in a draw
     * - not all cell marked
     *   - some player win
     *   - game should be continued
     * - no cells marked
     *   - game should be continued
     */

    // This function called after player turn, so we don't check is other player win
    auto& current_player = isPlayer1JustEndItsTurn ? player1_ : player2_;
    auto current_player_mark = current_player->getMark();
    bool isCurrentPlayerWin = field_->isFieldContainsSomeMarksConsecutive(current_player_mark, cellsInRowToWin_);

    if(isCurrentPlayerWin) {
        return isPlayer1JustEndItsTurn ? Status::player1_win : Status::player2_win;
    }
    if(field_->isAllCellsMarked()) {
        return Status::ended_in_a_draw;
    }
    return Status::should_be_continued;
}

void Game::processGameEnd()
{
    switch(status_) {
    case Status::player1_win:
        input_output_->showMessage("Player 1 win!");
        break;
    case Status::player2_win:
        input_output_->showMessage("Player 2 win!");
        break;
    case Status::ended_in_a_draw:
        input_output_->showMessage("The game ended in a draw. There is no winner.");
        break;
    case Status::should_be_continued:
        throw std::runtime_error("Unexpected game status: 'should_be_continued'");
    }
}
