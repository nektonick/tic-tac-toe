#include <cstdlib>
#include <iostream>
#include "game.h"
#include "input_output.h"


int runInConsole()
{
    auto input_output = std::make_unique<Console_InputOutut>();
    Game game(std::move(input_output));
    game.play();
    // TODO: add restart option
    return EXIT_SUCCESS;
}


int main()
{
    try {
        return runInConsole();
    } catch(const std::exception& e) {
        std::cerr << "Error: '" << e.what() << "'" << std::endl;
        return EXIT_FAILURE;
    }
}
