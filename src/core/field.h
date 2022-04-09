#pragma once
#include <optional>
#include <vector>
#include "input_output.h"


class FieldSize
{
public:
    FieldSize()
        : FieldSize(3, 3)
    {
    }

    // Input parameter is signed because to avoid conversion from negative value to positive if negative value passed
    FieldSize(int64_t columns_and_rows_count)
        : FieldSize(columns_and_rows_count, columns_and_rows_count)
    {
    }

    FieldSize(int64_t rows_count, int64_t columns_count)
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

    uint64_t getRowsCount() const noexcept
    {
        return rows_count_;
    }

    uint64_t getColumnsCount() const noexcept
    {
        return columns_count_;
    }

private:
    const uint64_t rows_count_;
    const uint64_t columns_count_;
};


class Cell
{
public:
    Cell() noexcept
        : state_(std::nullopt)
    {
    }

    bool isEmpty() const noexcept
    {
        return state_ == std::nullopt;
    }

    void updateState(CellContent newState)
    {
        if(!isEmpty()) {
            throw std::logic_error("Already set");
        }
        state_ = newState;
    }

    void resetState() noexcept
    {
        state_ = std::nullopt;
    }

    std::optional<CellContent> getState() const noexcept
    {
        return state_;
    }

private:
    std::optional<CellContent> state_;
};
using CellsRow = std::vector<Cell>;
using CellsGrid = std::vector<CellsRow>;


class Field
{
public:
    explicit Field(FieldSize size)
        : size_(size)
        , grid_(size.getRowsCount(), CellsRow{size.getColumnsCount(), Cell{}})
    {
    }

    void updateCellOnPosition(const CellPosition& position, CellContent newState)
    {
        if(!isPositionCorrect(position)) {
            throw std::invalid_argument("invalid position");
        }
        auto& row = grid_.at(position.getRow());
        auto& cell = row.at(position.getColumn());
        cell.updateState(newState);
    }

private:
    bool isPositionCorrect(const CellPosition& position) const noexcept
    {
        if(position.getRow() >= size_.getRowsCount()) {
            return false;
        }
        if(position.getColumn() >= size_.getColumnsCount()) {
            return false;
        }
        return true;
    }


    FieldSize size_;
    CellsGrid grid_;
};
