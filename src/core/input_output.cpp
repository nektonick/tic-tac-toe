#include "input_output.h"

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


void GUI_InputOutput::draw(const CellsGrid&)
{
    // TODO
}

PlayerInput GUI_InputOutput::get_input()
{
    // TODO
    return PlayerInput(CellContent::x, CellPosition(0, 0));
}


void Console_InputOutut::draw(const CellsGrid& grid)
{
}

PlayerInput Console_InputOutut::get_input()
{
    // TODO
    return PlayerInput(CellContent::x, CellPosition(0, 0));
}
