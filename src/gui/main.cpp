#include <QApplication>
#include <cstdlib>
#include "game.h"
#include "input_output.h"


int run_in_gui(int argc, char* argv[])
{
    QApplication a(argc, argv);
    auto input_output = std::make_unique<GUI_InputOutput>();
    Game game(std::move(input_output));
    game.play();

    // TODO: add restart option
    return a.exec();
}


int main(int argc, char* argv[])
{
    return run_in_gui(argc, argv);
}
