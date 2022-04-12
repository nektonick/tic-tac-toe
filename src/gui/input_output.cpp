#include "input_output.h"
#include "field.h"


GUI_InputOutput::GUI_InputOutput()
{
    w.renderField();
}

void GUI_InputOutput::redrawField(const CellsGrid&)
{
    // TODO
}

PlayerInput GUI_InputOutput::readPlayerInput()
{
    // TODO
    return PlayerInput(MarkType::x, CellPosition(0, 0));
}

FieldSize GUI_InputOutput::readFieldSize()
{
    // TODO
    return FieldSize();
}

void GUI_InputOutput::showMessage(std::string_view msg)
{
    // TODO
}
