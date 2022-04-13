#pragma once
#include "i_input_output.hpp"


class Console_InputOutut final : public I_InputOutput
{
public:
    void redrawField(std::shared_ptr<Field> field) override;
    CellPosition readPlayerInput() override;
    FieldSize readFieldSize() override;
    void showMessage(std::string_view msg) override;
};
