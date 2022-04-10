#include "player.h"

PlayerType AI_Player::getType() const noexcept
{
    return PlayerType::AI;
}


PlayerType Human_Player::getType() const noexcept
{
    return PlayerType::human;
}
