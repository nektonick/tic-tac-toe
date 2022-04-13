#pragma once
#include <optional>
#include <vector>
#include "base_types.h"


// TODO: what about infinity field?
class FieldSize
{
public:
    FieldSize();
    // Input parameter is signed to avoid conversion from negative value to positive (-1 => 255 for uint8_t for example)
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
    void updateState(MarkType newState);
    std::optional<MarkType> getState() const noexcept;

private:
    std::optional<MarkType> state_;
};
using CellsRow = std::vector<Cell>;
using CellsGrid = std::vector<CellsRow>;


class Field
{
public:
    explicit Field(FieldSize size);

    void updateCellState(const CellPosition& position, MarkType newState);
    std::optional<MarkType> getCellState(const CellPosition& position) const;

    void clear();

private:
    const Cell& getCellAt(const CellPosition& position) const;
    Cell& getCellAt(const CellPosition& position); // The same as function above but non-const
    bool isPositionCorrect(const CellPosition& position) const noexcept;

    FieldSize size_;
    CellsGrid cells_;
};
