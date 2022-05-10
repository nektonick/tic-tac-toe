#pragma once
#include <memory> // unique_ptr
#include "field.h"
#include "i_input_output.hpp"
#include "player.h"


class Game
{
public:
    Game(std::unique_ptr<I_InputOutput> input_output_interface);

    void play();

private:
    void restart();
    bool gameShouldBeContinued() const noexcept;
    void doTurn();
    void updateStatusAfterTurn();
    enum class Status
    {
        player1_win,
        player2_win,
        ended_in_a_draw,
        should_be_continued
    };
    Status getNewStatus(bool isPlayer1JustEndItsTurn) const noexcept;
    void processGameEnd();

    Status status_{Status::should_be_continued};
    std::shared_ptr<I_InputOutput> input_output_; // shared with human players
    std::shared_ptr<Field> field_; // shared with AI_module
    std::unique_ptr<I_Player> player1_;
    std::unique_ptr<I_Player> player2_;
    bool is_player1_turn_{true};
    uint64_t turn_number_{0};
};
