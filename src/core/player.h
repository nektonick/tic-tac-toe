#pragma once
#include <memory> // unique_ptr
#include <vector>
#include "base_types.h"


// Forward declaration
class Cell;
using CellsRow = std::vector<Cell>;
using CellsGrid = std::vector<CellsRow>;
class I_InputOutput; // TODO: use it


enum class PlayerType
{
    AI,
    human
};


class I_Player
{
public:
    I_Player(MarkType player_mark);
    virtual ~I_Player() = default;

    virtual PlayerType getType() const noexcept = 0;
    MarkType getMark() const noexcept;
    virtual CellPosition selectCellToMark() = 0;

private:
    const MarkType mark_;
};


class AI_Player final : public I_Player
{
public:
    AI_Player(MarkType player_mark);

    PlayerType getType() const noexcept override;
    CellPosition selectCellToMark() override;

private:
};


class Human_Player final : public I_Player
{
public:
    Human_Player(MarkType player_mark);

    PlayerType getType() const noexcept override;
    CellPosition selectCellToMark() override;
};


class PlayersFabric
{
public:
    static std::unique_ptr<I_Player> getPlayerOfType(PlayerType, MarkType);
};
