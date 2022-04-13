#include "input_output.h"
#include "field.h"


GUI_InputOutput::GUI_InputOutput(std::shared_ptr<MainWindow> gui)
{
    gui->renderField();
}

void GUI_InputOutput::redrawField(std::shared_ptr<Field> field)
{
    // TODO
}

CellPosition GUI_InputOutput::readPlayerInput()
{
    // TODO
    return CellPosition(0, 0);
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
