#include "field.h"

FieldSize::FieldSize()
    : FieldSize(3, 3)
{
}

FieldSize::FieldSize(int64_t columns_and_rows_count)
    : FieldSize(columns_and_rows_count, columns_and_rows_count)
{
}

FieldSize::FieldSize(int64_t rows_count, int64_t columns_count)
    : rows_count_(rows_count)
    , columns_count_(columns_count)

{
    if(rows_count <= 0) {
        throw std::invalid_argument("Invalid rows count");
    }
    if(columns_count <= 0) {
        throw std::invalid_argument("Invalid columns count");
    }
}

uint64_t FieldSize::getRowsCount() const noexcept
{
    return rows_count_;
}

uint64_t FieldSize::getColumnsCount() const noexcept
{
    return columns_count_;
}

bool Cell::isMarked() const noexcept
{
    return mark_ != std::nullopt;
}

void Cell::mark(MarkType mark)
{
    if(isMarked()) {
        throw std::logic_error("This cell already marked");
    }
    mark_ = mark;
}

std::optional<MarkType> Cell::getMark() const noexcept
{
    return mark_;
}


Field::Field()
    : Field(FieldSize())
{
}

Field::Field(FieldSize size)
    : size_(size)
    , cells_(CellsGrid(size.getRowsCount(), CellsRow{size.getColumnsCount(), Cell{}}))
{
}

FieldSize Field::getFieldSize() const noexcept
{
    return size_;
}

void Field::markCell(const CellPosition& position, MarkType mark)
{
    auto& cell = getCellAt(position);
    cell.mark(mark);
    markedCellsCount_ += 1;
}

std::optional<MarkType> Field::getCellMark(const CellPosition& position) const
{
    const auto& cell = getCellAt(position);
    return cell.getMark();
}

bool Field::isAllCellsMarked() const noexcept
{
    // NOTE: potential overflow here if RowsCount is too much
    uint64_t totalCellsCount = size_.getRowsCount() * size_.getColumnsCount();
    return markedCellsCount_ == totalCellsCount;
}

bool Field::isFieldContainsSomeMarksConsecutive(MarkType requiredMark, uint32_t requiredMarksCount) const noexcept
{
    // going to check rows, columns and diagonals
    const auto rowsCount = size_.getRowsCount();
    const auto columnsCount = size_.getColumnsCount();

    for(uint64_t row = 0; row < rowsCount; ++row) {
        uint32_t numberOfMarksInRow = 0;
        for(uint64_t column = 0; column < columnsCount; ++column) {
            auto currentMark = cells_[row][column].getMark();
            if(currentMark.has_value() && currentMark.value() == requiredMark) {
                numberOfMarksInRow += 1;
            } else {
                numberOfMarksInRow = 0;
            }
            if(numberOfMarksInRow >= requiredMarksCount) {
                return true;
            }
        }
    }

    for(uint64_t column = 0; column < columnsCount; ++column) {
        uint32_t numberOfMarksInRow = 0; // inRow here mean 'successively'
        for(uint64_t row = 0; row < rowsCount; ++row) {
            auto currentMark = cells_[row][column].getMark();
            if(currentMark.has_value() && currentMark.value() == requiredMark) {
                numberOfMarksInRow += 1;
            } else {
                numberOfMarksInRow = 0;
            }
            if(numberOfMarksInRow >= requiredMarksCount) {
                return true;
            }
        }
    }


    using vectorOfMarks = std::vector<std::optional<MarkType>>;
    const size_t diagonalsCount = rowsCount + columnsCount - 1;
    std::vector<vectorOfMarks> diagonalMarks(diagonalsCount, vectorOfMarks{});
    std::vector<vectorOfMarks> backwardDiagonalMarks(diagonalsCount, vectorOfMarks{});
    for(uint64_t row = 0; row < rowsCount; ++row) {
        for(uint64_t column = 0; column < columnsCount; ++column) {
            auto currentMark = cells_[row][column].getMark();
            diagonalMarks[row + column].push_back(currentMark);
            backwardDiagonalMarks[row + (columnsCount - 1 - column)].push_back(currentMark);
        }
    }

    for(const auto& diagonal : diagonalMarks) {
        if(diagonal.size() < requiredMarksCount) {
            continue;
        }
        uint32_t numberOfMarksInRow = 0; // inRow here mean 'successively'
        for(const auto& currentMark : diagonal) {
            if(currentMark.has_value() && currentMark.value() == requiredMark) {
                numberOfMarksInRow += 1;
            } else {
                numberOfMarksInRow = 0;
            }
            if(numberOfMarksInRow >= requiredMarksCount) {
                return true;
            }
        }
    }

    // Same for backward diagonals
    for(const auto& diagonal : backwardDiagonalMarks) {
        if(diagonal.size() < requiredMarksCount) {
            continue;
        }
        uint32_t numberOfMarksInRow = 0; // inRow here mean 'successively'
        for(const auto& currentMark : diagonal) {
            if(currentMark.has_value() && currentMark.value() == requiredMark) {
                numberOfMarksInRow += 1;
            } else {
                numberOfMarksInRow = 0;
            }
            if(numberOfMarksInRow >= requiredMarksCount) {
                return true;
            }
        }
    }

    return false;
}

void Field::reset(FieldSize newSize)
{
    size_ = newSize;
    // TODO: alternative: update cells state in loop if we don't want to recreate cells
    cells_ = CellsGrid(size_.getRowsCount(), CellsRow{size_.getColumnsCount(), Cell()});
    markedCellsCount_ = 0;
}

const Cell& Field::getCellAt(const CellPosition& position) const
{
    if(!isPositionCorrect(position)) {
        throw std::invalid_argument("invalid position");
    }
    auto& row = cells_.at(position.getRow());
    auto& cell = row.at(position.getColumn());
    return cell;
}

Cell& Field::getCellAt(const CellPosition& position)
{
    // Some magic, see link below for explanation
    // https://stackoverflow.com/questions/123758/how-do-i-remove-code-duplication-between-similar-const-and-non-const-member-func
    return const_cast<Cell&>(std::as_const(*this).getCellAt(position));
}

bool Field::isPositionCorrect(const CellPosition& position) const noexcept
{
    if(position.getRow() >= size_.getRowsCount()) {
        return false;
    }
    if(position.getColumn() >= size_.getColumnsCount()) {
        return false;
    }
    return true;
}
