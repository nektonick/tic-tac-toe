#include <cstdlib>
#include <iostream>
#include "game.h"


// TODO: get players types and filed size from params
int run_in_console(int argc, char* argv[])
{
    Game game(GameSettings(FieldSize(), PlayerType::human, PlayerType::AI));
    std::cout << "App is under development" << std::endl;
    return EXIT_SUCCESS;
}


int main(int argc, char* argv[])
{
    return run_in_console(argc, argv);
}
