#pragma once
#include "i_input_output.hpp"


class Console_InputOutut final : public I_InputOutput
{
public:
    Console_InputOutut() = default;

    FieldSize readFieldSize() override;
    void initField(std::shared_ptr<Field> field) override;
    void updateField(std::shared_ptr<Field> field) override;

    CellPosition readPlayerInput() override;
    void showMessage(std::string_view msg) override;
};
