#include "i_input_output.h"

PlayerInput::PlayerInput(MarkType symbol, CellPosition position)
    : symbol_(symbol)
    , position_(position)
{
}

MarkType PlayerInput::getSymbol() const noexcept
{
    return symbol_;
}

CellPosition PlayerInput::getPosition() const noexcept
{
    return position_;
}
