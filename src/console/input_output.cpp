#include "input_output.h"
#include "field.h"


FieldSize Console_InputOutut::readFieldSize()
{
    // TODO
    return FieldSize();
}

void Console_InputOutut::initField(std::shared_ptr<Field> field)
{
    // TODO
}

void Console_InputOutut::updateField(std::shared_ptr<Field> field)
{
    // TODO
}

CellPosition Console_InputOutut::readPlayerInput()
{
    // TODO
    return CellPosition(0, 0);
}


void Console_InputOutut::showMessage(std::string_view msg)
{
    std::cout << msg << std::endl;
}
