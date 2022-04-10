#include "player.h"

PlayerType AI_Player::getType() const noexcept
{
    return PlayerType::AI;
}


PlayerType Human_Player::getType() const noexcept
{
    return PlayerType::human;
}


std::unique_ptr<I_Player> PlayersFabric::getPlayerOfType(PlayerType type)
{
    std::unique_ptr<I_Player> player;
    switch(type) {
    case PlayerType::AI:
        player = std::make_unique<AI_Player>();
        break;
    case PlayerType::human:
        player = std::make_unique<Human_Player>();
        break;
    }
    return player;
}
