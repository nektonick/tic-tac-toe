#pragma once
#include <iostream> // For debug only
#include <limits>
#include <memory>
#include "field.h"


// TODO: difficulty level
class AI_Core
{
public:
    AI_Core(std::shared_ptr<Field>);
    CellPosition makeMove(MarkType currentPlayerMark);

private:
    CellPosition getBestMove(MarkType currentPlayerMark);
    using CellScore = int;
    CellScore minimax(MarkType currentPlayerMark, bool isCurrentPlayerMove, int depth, int alpha, int beta);

    uint32_t minMaxCallsCount = 0; // For statistic
    CellPosition currentBestMove{0, 0};
    std::shared_ptr<Field> field_;
};
