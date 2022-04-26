#include "input_output.h"
#include "field.h"
#include "player.h"


FieldSize Console_InputOutut::readFieldSize()
{
    // TODO
    return FieldSize();
}

void Console_InputOutut::initField(std::shared_ptr<Field> field)
{
    // TODO
}

void Console_InputOutut::updateField(std::shared_ptr<Field> field)
{
    // TODO
}

PlayerType Console_InputOutut::getPlayerType(std::string_view msg)
{
    // TODO
    return PlayerType::human;
}

uint32_t Console_InputOutut::getCellsInRowToWinCount(uint32_t maxValue)
{
    // TODO
    return 3;
}

CellPosition Console_InputOutut::readPlayerInput()
{
    // TODO
    return CellPosition(0, 0);
}


void Console_InputOutut::showMessage(std::string_view msg)
{
    std::cout << msg << std::endl;
}
