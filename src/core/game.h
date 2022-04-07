#pragma once
#include "field.h"
#include "player.h"


class GameSettings
{
public:
    GameSettings(FieldSize field_size, PlayerType first_player_type, PlayerType second_player_type)
        : field_size_(field_size)
        , first_player_type_(first_player_type)
        , second_player_type_(second_player_type)
    {
    }

    FieldSize getFiledSize() const noexcept
    {
        return field_size_;
    }

    PlayerType getFirstPlayerType() const noexcept
    {
        return first_player_type_;
    }

    PlayerType getSecondPlayerType() const noexcept
    {
        return second_player_type_;
    }

private:
    FieldSize field_size_;
    PlayerType first_player_type_;
    PlayerType second_player_type_;
};


class Game
{
public:
    Game(GameSettings settings)
        : field_(settings.getFiledSize())
    {
        // TODO: create fabric method
        switch(auto playerType = settings.getFirstPlayerType()) {
        case PlayerType::AI:
            player1_ = std::make_unique<AI_Player>();
            break;
        case PlayerType::human:
            player1_ = std::make_unique<Human_Player>();
            break;
        }

        switch(auto playerType = settings.getSecondPlayerType()) {
        case PlayerType::AI:
            player2_ = std::make_unique<AI_Player>();
            break;
        case PlayerType::human:
            player2_ = std::make_unique<Human_Player>();
            break;
        }
    }

private:
    Field field_;
    std::unique_ptr<I_Player> player1_;
    std::unique_ptr<I_Player> player2_;
};
