#include "ai_core.h"

AI_Core::AI_Core(std::shared_ptr<Field> field)
    : field_(field)
{
}

CellPosition AI_Core::makeMove()
{
    // TODO
    return CellPosition(0, 0);
}
