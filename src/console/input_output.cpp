#include "input_output.h"
#include "field.h"


void Console_InputOutut::redrawField(const CellsGrid& grid)
{
}

PlayerInput Console_InputOutut::readPlayerInput()
{
    // TODO
    return PlayerInput(MarkType::x, CellPosition(0, 0));
}

FieldSize Console_InputOutut::readFieldSize()
{
    // TODO
    return FieldSize();
}

void Console_InputOutut::showMessage(std::string_view msg)
{
    std::cout << msg << std::endl;
}
