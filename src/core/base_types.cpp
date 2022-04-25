#include "base_types.h"

CellPosition::CellPosition(int64_t row, int64_t column)
    : row_(row)
    , column_(column)
{
    if(row < 0) {
        throw std::invalid_argument("Invalid row");
    }
    if(column < 0) {
        throw std::invalid_argument("Invalid column");
    }
}

uint32_t CellPosition::getRow() const noexcept
{
    return row_;
}

uint32_t CellPosition::getColumn() const noexcept
{
    return column_;
}
