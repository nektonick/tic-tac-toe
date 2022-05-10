#pragma once
#include <optional>
#include "i_input_output.hpp"


class Console_InputOutut final : public I_InputOutput
{
public:
    Console_InputOutut() = default;

    FieldSize readFieldSize() override;
    void initField(std::shared_ptr<Field> field) override;
    void updateField(std::shared_ptr<Field> field) override;

    PlayerType getPlayerType(std::string_view msg) override;
    uint32_t getMarksInRowToWinCount(uint32_t maxValues) override;
    CellPosition readPlayerInput() override;
    void showMessage(std::string_view msg) override;

private:
    void printField(std::shared_ptr<Field>&& field) const noexcept;
    void printMark(const std::optional<MarkType>& mark) const noexcept;
};
