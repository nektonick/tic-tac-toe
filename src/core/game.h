#pragma once
#include <memory> // unique_ptr
#include "field.h"
#include "player.h"


class GameSettings
{
public:
    GameSettings(FieldSize field_size, PlayerType first_player_type, PlayerType second_player_type);

    FieldSize getFiledSize() const noexcept;
    PlayerType getFirstPlayerType() const noexcept;
    PlayerType getSecondPlayerType() const noexcept;

private:
    FieldSize field_size_;
    PlayerType first_player_type_;
    PlayerType second_player_type_;
};


class Game
{
public:
    Game(GameSettings settings);

private:
    Field field_;
    std::unique_ptr<I_Player> player1_;
    std::unique_ptr<I_Player> player2_;
};
