#pragma once
#include <iostream>
#include <memory>
#include <string_view> // string_view is like const reference to std::string
#include <vector>
#include "base_types.h"

// Forward declaration
class FieldSize;
class Field;
enum class PlayerType;


class I_InputOutput
{
public:
    I_InputOutput() = default;
    virtual ~I_InputOutput() = default;

    virtual FieldSize readFieldSize() = 0;
    virtual void initField(std::shared_ptr<Field> field) = 0;
    virtual void updateField(std::shared_ptr<Field> field) = 0;

    virtual PlayerType getPlayerType(std::string_view msg) = 0;
    virtual uint32_t getCellsInRowToWinCount(uint32_t maxValue) = 0;
    virtual CellPosition readPlayerInput() = 0;

    virtual void showMessage(std::string_view msg) = 0;
};
