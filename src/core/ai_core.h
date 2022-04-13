#pragma once
#include <memory>
#include "field.h"

// TODO: difficulty level
class AI_Core
{
public:
    AI_Core(std::shared_ptr<Field>);
    CellPosition makeMove();

private:
    std::shared_ptr<Field> field_;
};
