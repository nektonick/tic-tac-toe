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


Cell::Cell() noexcept
    : state_(std::nullopt)
{
}

bool Cell::isEmpty() const noexcept
{
    return state_ == std::nullopt;
}

void Cell::updateState(MarkType newState)
{
    if(!isEmpty()) {
        throw std::logic_error("Already set");
    }
    state_ = newState;
}

void Cell::resetState() noexcept
{
    state_ = std::nullopt;
}

std::optional<MarkType> Cell::getState() const noexcept
{
    return state_;
}


Field::Field(FieldSize size)
    : size_(size)
    , cells_(std::make_shared<CellsGrid>(size.getRowsCount(), CellsRow{size.getColumnsCount(), Cell{}}))
{
}

void Field::updateCellOnPosition(const CellPosition& position, MarkType newState)
{
    if(!isPositionCorrect(position)) {
        throw std::invalid_argument("invalid position");
    }
    auto& row = cells_->at(position.getRow());
    auto& cell = row.at(position.getColumn());
    cell.updateState(newState);
}

std::weak_ptr<CellsGrid> Field::getCellsInfo() const noexcept
{
    return cells_;
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
