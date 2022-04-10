#include "i_input_output.h"

PlayerInput::PlayerInput(CellContent symbol, CellPosition position)
    : symbol_(symbol)
    , position_(position)
{
}

CellContent PlayerInput::getSymbol() const noexcept
{
    return symbol_;
}

CellPosition PlayerInput::getPosition() const noexcept
{
    return position_;
}
