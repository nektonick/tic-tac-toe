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
    PlayerInput(CellContent symbol, CellPosition position);

    CellContent getSymbol() const noexcept;
    CellPosition getPosition() const noexcept;

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
    void draw(const CellsGrid&) override;
    PlayerInput get_input() override;
};


class Console_InputOutut final : public I_InputOutput
{
public:
    void draw(const CellsGrid& grid) override;
    PlayerInput get_input() override;
};
