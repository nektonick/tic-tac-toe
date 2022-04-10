#pragma once
#include <optional>
#include <vector>
#include "base_types.h"


class FieldSize
{
public:
    FieldSize();
    // Input parameter is signed because to avoid conversion from negative value to positive if negative value passed
    FieldSize(int64_t columns_and_rows_count);
    FieldSize(int64_t rows_count, int64_t columns_count);

    uint64_t getRowsCount() const noexcept;
    uint64_t getColumnsCount() const noexcept;

private:
    const uint64_t rows_count_;
    const uint64_t columns_count_;
};


class Cell
{
public:
    Cell() noexcept;

    bool isEmpty() const noexcept;
    void updateState(CellContent newState);
    void resetState() noexcept;
    std::optional<CellContent> getState() const noexcept;

private:
    std::optional<CellContent> state_;
};
using CellsRow = std::vector<Cell>;
using CellsGrid = std::vector<CellsRow>;


class Field
{
public:
    explicit Field(FieldSize size);

    void updateCellOnPosition(const CellPosition& position, CellContent newState);
    const CellsGrid& getCellsInfo() const noexcept;

private:
    bool isPositionCorrect(const CellPosition& position) const noexcept;

    FieldSize size_;
    CellsGrid grid_;
};
