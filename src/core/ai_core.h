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
    CellPosition makeMove(MarkType playerMark);

private:
    CellPosition getBestMove();
    using Score = int;
    Score minimax(bool isOurMove, int depth, int alpha, int beta);
    Score getCurrentStateScore(bool isPlayerWin, bool isOpponentWin, bool isGameEnded, int currentDepth);

    MarkType ourMark_{MarkType::x};
    uint32_t minMaxCallsCount = 0; // For statistic
    CellPosition currentBestMove{0, 0};
    std::shared_ptr<Field> field_;
};
