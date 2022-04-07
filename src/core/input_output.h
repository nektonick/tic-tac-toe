#pragma once
#include <iostream>
#include <vector>
#include "base_types.h"

// Forward declaration
class Cell;
using CellsRow = std::vector<Cell>;
using CellsGrid = std::vector<CellsRow>;


class PlayerInput
{
public:
    PlayerInput(CellContent symbol, CellPosition position)
        : symbol_(symbol)
        , position_(position)
    {
    }

    CellContent getSymbol() const noexcept
    {
        return symbol_;
    }

    CellPosition getPosition() const noexcept
    {
        return position_;
    }

private:
    CellContent symbol_;
    CellPosition position_;
};


class I_InputOutput
{
public:
    virtual ~I_InputOutput() = default;
    virtual void draw(const CellsGrid&) = 0;
    virtual PlayerInput get_input() = 0;
};


class GUI_InputOutput final : public I_InputOutput
{
public:
    void draw(const CellsGrid&) override
    {
        // TODO
    }
    PlayerInput get_input() override
    {
        // TODO
        return PlayerInput(CellContent::x, CellPosition(0, 0));
    }
};


class Console_InputOutut final : public I_InputOutput
{
public:
    void draw(const CellsGrid& grid) override
    {
        for(const auto& row : grid) {
            for(const auto& cell : row) {
                // TODO
            }
        }
    }
    PlayerInput get_input() override
    {
        // TODO
        return PlayerInput(CellContent::x, CellPosition(0, 0));
    }
};
