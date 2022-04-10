#pragma once
#include "i_input_output.h"


class GUI_InputOutput final : public I_InputOutput
{
public:
    void draw(const CellsGrid&) override;
    PlayerInput get_input() override;
};
