#pragma once

enum class PlayerType
{
    AI,
    human
};


class I_Player
{
public:
    I_Player() = default;
    virtual ~I_Player() = default;

    virtual PlayerType getType() const noexcept = 0;
};


class AI_Player final : public I_Player
{
public:
    PlayerType getType() const noexcept;
};


class Human_Player final : public I_Player
{
public:
    PlayerType getType() const noexcept;
};
