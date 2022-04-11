#include "player.h"


I_Player::I_Player(MarkType player_mark)
    : mark_(player_mark)
{
}

AI_Player::AI_Player(MarkType player_mark)
    : I_Player(player_mark)
{
}

PlayerType AI_Player::getType() const noexcept
{
    return PlayerType::AI;
}

CellPosition AI_Player::selectCellToMark()
{
    // TODO
    return CellPosition(0, 0);
}

MarkType I_Player::getMark() const noexcept
{
    return mark_;
}


Human_Player::Human_Player(MarkType player_mark)
    : I_Player(player_mark)
{
}

PlayerType Human_Player::getType() const noexcept
{
    return PlayerType::human;
}

CellPosition Human_Player::selectCellToMark()
{
    // TODO
    return CellPosition(0, 0);
}


std::unique_ptr<I_Player> PlayersFabric::getPlayerOfType(PlayerType type, MarkType mark)
{
    std::unique_ptr<I_Player> player;
    switch(type) {
    case PlayerType::AI:
        player = std::make_unique<AI_Player>(mark);
        break;
    case PlayerType::human:
        player = std::make_unique<Human_Player>(mark);
        break;
    }
    return player;
}
