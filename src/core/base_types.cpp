﻿#include "base_types.h"

CellPosition::CellPosition(int64_t row, int64_t column)
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

uint64_t CellPosition::getRow() const noexcept
{
    return row_;
}

uint64_t CellPosition::getColumn() const noexcept
{
    return column_;
}
