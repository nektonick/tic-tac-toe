#pragma once
#include <iostream>
#include <string_view> // string_view is like const reference to std::string
#include <vector>
#include "base_types.h"

// Forward declaration
class Cell;
using CellsRow = std::vector<Cell>;
using CellsGrid = std::vector<CellsRow>;
class FieldSize;


class PlayerInput
{
public:
    PlayerInput(MarkType symbol, CellPosition position);

    MarkType getSymbol() const noexcept;
    CellPosition getPosition() const noexcept;

private:
    MarkType symbol_;
    CellPosition position_;
};


class I_InputOutput
{
public:
    I_InputOutput() = default;
    virtual ~I_InputOutput() = default;

    virtual void redrawField(const CellsGrid& newFieldState) = 0;
    virtual PlayerInput readPlayerInput() = 0;
    virtual FieldSize readFieldSize() = 0;
    virtual void showMessage(std::string_view msg) = 0;
};
