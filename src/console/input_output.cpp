#include "input_output.h"
#include "field.h"


void Console_InputOutut::redrawField(std::shared_ptr<Field> field)
{
    // TODO
}

CellPosition Console_InputOutut::readPlayerInput()
{
    // TODO
    return CellPosition(0, 0);
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
