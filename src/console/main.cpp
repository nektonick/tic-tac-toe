#include <cstdlib>
#include <iostream>
#include "cmd_parser.h"
#include "game.h"
#include "input_output.h"


int runInConsole(int argc, char* argv[])
{
    auto settings = parseCmdParams(argc, argv);
    auto input_output = std::make_unique<Console_InputOutut>();
    Game game(settings, std::move(input_output));
    game.play();
    // TODO: add restart option
    return EXIT_SUCCESS;
}


int main(int argc, char* argv[])
{
    try {
        return runInConsole(argc, argv);
    } catch(const std::exception& e) {
        std::cerr << "Error: '" << e.what() << "'" << std::endl;
        return EXIT_FAILURE;
    }
}
