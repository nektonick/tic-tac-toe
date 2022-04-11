#pragma once
#include "i_input_output.h"
#include "mainwindow.h"


class GUI_InputOutput final : public I_InputOutput
{
public:
    GUI_InputOutput();

    void redrawField(const CellsGrid&) override;
    PlayerInput readPlayerInput() override;
    FieldSize readFieldSize() override;
    void showMessage(std::string_view msg) override;

private:
    MainWindow w;
};
