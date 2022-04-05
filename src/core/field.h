#pragma once
#include <cstdint>
#include <stdexcept>
#include <vector>


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


class FieldCellPosition
{
public:
    // we start counting from zero
    FieldCellPosition(int64_t row, int64_t column)
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


class FieldCell
{
public:
    enum class State : uint8_t
    {
        none,
        x, // cross
        o // nought
    };


    FieldCell()
        : state_(State::none)
    {
    }

    bool isEmpty() const noexcept
    {
        return state_ == State::none;
    }

    void updateState(State newState)
    {
        if(!isEmpty()) {
            throw std::logic_error("Already set");
        }
        state_ = newState;
    }

    State getState() const noexcept
    {
        return state_;
    }

private:
    State state_;
};
using CellsRow = std::vector<FieldCell>;
using CellsGrid = std::vector<CellsRow>;


class Field
{
public:
    explicit Field(FieldSize size)
        : size_(size)
        , grid_(size.getRowsCount(), CellsRow{size.getColumnsCount(), FieldCell{}})
    {
    }

    void updateCellOnPosition(const FieldCellPosition& position, FieldCell::State newState)
    {
        if(!isPositionCorrect(position)) {
            throw std::invalid_argument("invalid position");
        }
        auto& row = grid_.at(position.getRow());
        auto& cell = row.at(position.getColumn());
        cell.updateState(newState);
    }

    void render()
    {
        for(const auto& row : grid_) {
            for(const auto& cell : row) {
                // TODO
            }
        }
    }

private:
    bool isPositionCorrect(const FieldCellPosition& position) const noexcept
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
