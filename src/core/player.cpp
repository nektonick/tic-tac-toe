#include "player.h"
#include "i_input_output.hpp"


I_Player::I_Player(MarkType player_mark, std::shared_ptr<I_InputOutput> input_output_module, std::shared_ptr<Field> field)
    : mark_(player_mark)
    , io_(std::move(input_output_module))
    , field_(field)
{
}

MarkType I_Player::getMark() const noexcept
{
    return mark_;
}

void I_Player::doTurn()
{
    auto mark = getMark();
    auto cell_to_mark = selectCellToMark();
    field_->markCell(cell_to_mark, mark);
    io_->updateField(field_);
}


AI_Player::AI_Player(MarkType player_mark,
                     std::shared_ptr<I_InputOutput> input_output_module,
                     std::shared_ptr<Field> field)
    : I_Player(player_mark, std::move(input_output_module), field)
    , ai_(field)
{
}

PlayerType AI_Player::getType() const noexcept
{
    return PlayerType::AI;
}

CellPosition AI_Player::selectCellToMark()
{
    return ai_.makeMove(getMark());
}


Human_Player::Human_Player(MarkType player_mark, std::shared_ptr<I_InputOutput> input_output_module, std::shared_ptr<Field> field)
    : I_Player(player_mark, std::move(input_output_module), field)
{
}

PlayerType Human_Player::getType() const noexcept
{
    return PlayerType::human;
}

CellPosition Human_Player::selectCellToMark()
{
    return io_->readPlayerInput();
}


std::unique_ptr<I_Player> PlayersFabric::getPlayerOfType(PlayerType type,
                                                         MarkType mark,
                                                         std::shared_ptr<I_InputOutput> input_output_module,
                                                         std::shared_ptr<Field> field)
{
    std::unique_ptr<I_Player> player;
    switch(type) {
    case PlayerType::AI:
        player = std::make_unique<AI_Player>(mark, std::move(input_output_module), std::move(field));
        break;
    case PlayerType::human:
        player = std::make_unique<Human_Player>(mark, std::move(input_output_module), std::move(field));
        break;
    }
    return player;
}
