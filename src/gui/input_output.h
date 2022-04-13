#pragma once
#include "i_input_output.hpp"
#include "mainwindow.h"


class GUI_InputOutput final : public I_InputOutput
{
public:
    GUI_InputOutput(std::shared_ptr<MainWindow> gui);

    void redrawField(std::shared_ptr<Field> field) override;
    CellPosition readPlayerInput() override;
    FieldSize readFieldSize() override;
    void showMessage(std::string_view msg) override;

private:
    std::shared_ptr<MainWindow> gui_;
};
