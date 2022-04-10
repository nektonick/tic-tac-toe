#include "game.h"

GameSettings::GameSettings(FieldSize field_size, PlayerType first_player_type, PlayerType second_player_type)
    : field_size_(field_size)
    , first_player_type_(first_player_type)
    , second_player_type_(second_player_type)
{
}

FieldSize GameSettings::getFiledSize() const noexcept
{
    return field_size_;
}

PlayerType GameSettings::getFirstPlayerType() const noexcept
{
    return first_player_type_;
}

PlayerType GameSettings::getSecondPlayerType() const noexcept
{
    return second_player_type_;
}


Game::Game(GameSettings settings)
    : field_(settings.getFiledSize())
    , player1_(PlayersFabric::getPlayerOfType(settings.getFirstPlayerType()))
    , player2_(PlayersFabric::getPlayerOfType(settings.getSecondPlayerType()))
{
}
