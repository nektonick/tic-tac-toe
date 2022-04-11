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
    // we start counting from zero
    CellPosition(int64_t row, int64_t column);

    uint64_t getRow() const noexcept;
    uint64_t getColumn() const noexcept;

private:
    const uint64_t row_;
    const uint64_t column_;
};
