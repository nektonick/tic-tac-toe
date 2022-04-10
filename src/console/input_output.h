#pragma once
#include "i_input_output.h"


class Console_InputOutut final : public I_InputOutput
{
public:
    void draw(const CellsGrid& grid) override;
    PlayerInput get_input() override;
};
