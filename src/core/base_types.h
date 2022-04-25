#pragma once
#include <cstdint>
#include <stdexcept>


enum class MarkType
{
    x, // cross
    o // nought
};


class CellPosition
{
public:
    // We start counting from zero
    // Input parameter is signed to avoid conversion from negative value to positive (-1 => 255 for uint8_t for example)
    CellPosition(int64_t row, int64_t column);

    // NOTE: max positive value of int64_t is the same as max positive value of uint32_t
    uint32_t getRow() const noexcept;
    uint32_t getColumn() const noexcept;

private:
    uint64_t row_;
    uint64_t column_;
};
