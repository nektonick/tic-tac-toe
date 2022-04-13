﻿#pragma once
#include <memory> // unique_ptr
#include "field.h"
#include "i_input_output.hpp"
#include "player.h"


class GameSettings
{
public:
    GameSettings(PlayerType first_player_type, PlayerType second_player_type);

    PlayerType getFirstPlayerType() const noexcept;
    PlayerType getSecondPlayerType() const noexcept;

private:
    PlayerType first_player_type_;
    PlayerType second_player_type_;
};


class Game
{
public:
    Game(GameSettings, std::unique_ptr<I_InputOutput> input_output_interface);

    void play();

private:
    void restart();
    bool gameShouldBeContinued() const noexcept;
    void doTurn();
    enum class Status
    {
        player1_win,
        player2_win,
        ended_in_a_draw,
        should_be_continued
    };
    Status getNewStatus();
    void processGameEnd();

    Status status_;
    std::shared_ptr<I_InputOutput> input_output_; // shared with human players
    std::shared_ptr<Field> field_; // shared with AI_module
    std::unique_ptr<I_Player> player1_;
    std::unique_ptr<I_Player> player2_;
    bool is_player1_turn_{true};
    uint64_t turn_number_{0};
};
