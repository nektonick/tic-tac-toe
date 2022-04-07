#pragma once
#include <cstdint>
#include <stdexcept>


enum class CellContent
{
    x, // cross
    o // nought
};


class CellPosition
{
public:
    // we start counting from zero
    CellPosition(int64_t row, int64_t column)
        : row_(row)
        , column_(column)
    {
        if(row_ < 0) {
            throw std::invalid_argument("Invalid row");
        }
        if(column_ < 0) {
            throw std::invalid_argument("Invalid column");
        }
    }

    uint64_t getRow() const noexcept
    {
        return row_;
    }

    uint64_t getColumn() const noexcept
    {
        return column_;
    }

private:
    const uint64_t row_;
    const uint64_t column_;
};
