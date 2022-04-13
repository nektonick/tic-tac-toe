#pragma once
#include <memory> // unique_ptr
#include <vector>
#include "ai_core.h"
#include "base_types.h"


// Forward declaration
class I_InputOutput;
class Field;


enum class PlayerType
{
    AI,
    human
};


class I_Player
{
public:
    I_Player(MarkType player_mark, std::shared_ptr<I_InputOutput> input_output_module);
    virtual ~I_Player() = default;

    MarkType getMark() const noexcept;
    virtual PlayerType getType() const noexcept = 0;
    virtual CellPosition selectCellToMark() = 0;

protected:
    const MarkType mark_;
    std::shared_ptr<I_InputOutput> io_;
};


class AI_Player final : public I_Player
{
public:
    AI_Player(MarkType player_mark, std::shared_ptr<I_InputOutput> input_output_module, std::shared_ptr<Field> field);

    PlayerType getType() const noexcept override;
    CellPosition selectCellToMark() override;

private:
    AI_Core ai_;
};


class Human_Player final : public I_Player
{
public:
    Human_Player(MarkType player_mark, std::shared_ptr<I_InputOutput> input_output_module);

    PlayerType getType() const noexcept override;
    CellPosition selectCellToMark() override;
};


class PlayersFabric
{
public:
    static std::unique_ptr<I_Player> getPlayerOfType(PlayerType,
                                                     MarkType,
                                                     std::shared_ptr<I_InputOutput> input_output_module,
                                                     std::shared_ptr<Field> field);
};
