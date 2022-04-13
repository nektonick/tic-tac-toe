﻿#pragma once
#include <iostream>
#include <memory>
#include <string_view> // string_view is like const reference to std::string
#include <vector>
#include "base_types.h"

// Forward declaration
class FieldSize;
class Field;


class I_InputOutput
{
public:
    I_InputOutput() = default;
    virtual ~I_InputOutput() = default;

    virtual void redrawField(std::shared_ptr<Field> field) = 0;
    virtual CellPosition readPlayerInput() = 0;
    virtual FieldSize readFieldSize() = 0;
    virtual void showMessage(std::string_view msg) = 0;
};