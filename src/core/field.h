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
    explicit FieldSize(int64_t columns_and_rows_count);
    FieldSize(int64_t rows_count, int64_t columns_count);

    uint64_t getRowsCount() const noexcept;
    uint64_t getColumnsCount() const noexcept;

private:
    uint64_t rows_count_;
    uint64_t columns_count_;
};


class Cell
{
public:
    Cell() = default;

    bool isMarked() const noexcept;
    void mark(MarkType);
    void unmark();
    std::optional<MarkType> getMark() const noexcept;

private:
    std::optional<MarkType> mark_;
};
using CellsRow = std::vector<Cell>;
using CellsGrid = std::vector<CellsRow>;


class Field
{
public:
    Field();
    explicit Field(FieldSize size, uint32_t marksInRowToWin);
    void reset(FieldSize newSize, uint32_t marksInRowToWin);

    FieldSize getFieldSize() const noexcept;
    bool isAllCellsMarked() const noexcept;
    bool isPlayerWin(MarkType playerMark) const noexcept;
    std::optional<MarkType> getCellMark(const CellPosition& position) const;
    std::vector<CellPosition> getEmptyCells() const noexcept;

    // NOTE: cell can't be re-marked with other mark
    void markCell(const CellPosition& position, MarkType mark);
    void unmarkCell(const CellPosition& position);

private:
    bool isFieldContainsSomeMarksConsecutive(MarkType, uint32_t requiredMarksCount) const noexcept;
    const Cell& getCellAt(const CellPosition& position) const;
    Cell& getCellAt(const CellPosition& position); // The same as function above but non-const
    bool isPositionCorrect(const CellPosition& position) const noexcept;

    FieldSize size_;
    CellsGrid cells_;
    uint64_t markedCellsCount_ = 0;
    uint32_t marksInRowToWin_;
};
