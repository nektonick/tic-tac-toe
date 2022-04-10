#pragma once
#include <memory> // unique_ptr
#include "field.h"
#include "i_input_output.h"
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

    void doTurn();

private:
    bool isGameFinished() const noexcept;
    enum class Winner
    {
        player1,
        player2
    };
    std::optional<Winner> getWinner() const noexcept;


    Field field_;
    std::unique_ptr<I_Player> player1_;
    std::unique_ptr<I_Player> player2_;

    bool game_finished_{false};
    bool is_player1_turn_{true};
};
