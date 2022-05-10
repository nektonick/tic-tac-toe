#include "input_output.h"
#include "field.h"
#include "player.h"


FieldSize Console_InputOutut::readFieldSize()
{
    int64_t fieldWidthAndLenght = -1;
    auto doInput = [&fieldWidthAndLenght]() {
        // TODO: crate constants for input mix and max and write it here
        std::cout << "Enter field size (n*n, where 'n' is a digit in range [2, 1000]): ";
        std::cin >> fieldWidthAndLenght;
    };
    auto isInputCorrect = [](int64_t input) {
        return input > 1 && input <= 1000;
    };

    doInput();
    while(!isInputCorrect(fieldWidthAndLenght)) {
        std::cout << "Invalid input. ";
        doInput();
    }
    return FieldSize(fieldWidthAndLenght);
}

void Console_InputOutut::initField(std::shared_ptr<Field> field)
{
    std::cout << "Rows and columns starts from 0" << std::endl;
    const auto size = field->getFieldSize();
    std::cout << "Max row: " << size.getRowsCount() - 1 << std::endl;
    std::cout << "Max column: " << size.getColumnsCount() - 1 << std::endl;
}

void Console_InputOutut::updateField(std::shared_ptr<Field> field)
{
    printField(std::move(field));
}

PlayerType Console_InputOutut::getPlayerType(std::string_view msg)
{
    int input = -1;
    auto doInput = [&input, &msg]() {
        // TODO: static cast for digits
        std::cout << msg << "(0 for AI, 1 for human): ";
        std::cin >> input;
    };
    auto isInputCorrect = [](int input) {
        return input == static_cast<int>(PlayerType::AI) || input == static_cast<int>(PlayerType::human);
    };

    doInput();
    while(!isInputCorrect(input)) {
        std::cout << "Invalid input. ";
        doInput();
    }
    return static_cast<PlayerType>(input);
}

uint32_t Console_InputOutut::getCellsInRowToWinCount(uint32_t maxValue)
{
    int64_t input = -1;
    auto doInput = [&input, &maxValue]() {
        std::cout << "Cells in row to win (digit in range [2," << maxValue << "]: ";
        std::cin >> input;
    };
    auto isInputCorrect = [maxValue](int64_t input) {
        return input > 1 && input <= maxValue;
    };

    doInput();
    while(!isInputCorrect(input)) {
        std::cout << "Invalid input. ";
        doInput();
    }
    // input value is more than 0, so this cast from in64_t to uint32_t is safe
    return static_cast<int32_t>(input);
}

CellPosition Console_InputOutut::readPlayerInput()
{
    int64_t row = -1;
    int64_t column = -1;

    auto doInput = [&row, &column]() {
        std::cout << "Select row: ";
        std::cin >> row;
        std::cout << "Select column: ";
        std::cin >> column;
    };
    auto isInputCorrect = [](int64_t row, int64_t column) {
        // TODO: check, is field already marked (or handle exception in app)
        return row >= 0 && column >= 0;
    };

    doInput();
    while(!isInputCorrect(row, column)) {
        std::cout << "Invalid input. ";
        doInput();
    }
    return CellPosition(row, column);
}


void Console_InputOutut::showMessage(std::string_view msg)
{
    std::cout << msg << std::endl;
}

void Console_InputOutut::printField(std::shared_ptr<Field>&& field) const noexcept
{
    const auto size = field->getFieldSize();
    // TODO: print columns and strings numbers
    for(uint32_t row = 0; row < size.getRowsCount(); ++row) {
        for(uint32_t column = 0; column < size.getColumnsCount(); ++column) {
            printMark(field->getCellMark(CellPosition(row, column)));
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void Console_InputOutut::printMark(const std::optional<MarkType>& mark) const noexcept
{
    if(mark) {
        std::cout << (mark.value() == MarkType::x ? "X" : "O");
    } else {
        std::cout << ".";
    }
}
