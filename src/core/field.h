#pragma once
#include <memory>
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
    void resetState() noexcept;
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

    void updateCellOnPosition(const CellPosition& position, MarkType newState);
    std::weak_ptr<CellsGrid> getCellsInfo() const noexcept;

private:
    bool isPositionCorrect(const CellPosition& position) const noexcept;

    FieldSize size_;
    std::shared_ptr<CellsGrid> cells_;
};
