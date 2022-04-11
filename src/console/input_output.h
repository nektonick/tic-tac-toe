#pragma once
#include "i_input_output.h"


class Console_InputOutut final : public I_InputOutput
{
public:
    void redrawField(const CellsGrid& grid) override;
    PlayerInput readPlayerInput() override;
    FieldSize readFieldSize() override;
    void showMessage(std::string_view msg) override;
};
