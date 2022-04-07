#include <cstdlib>
#include "game.h"

#ifdef USE_GUI
#    include <QApplication>
#    include "gui/mainwindow.h"
#else
#    include <iostream>
#endif


// TODO: get players types and filed size from params
#ifdef USE_GUI
int run_in_gui(int argc, char* argv[])
{
    Game game(GameSettings(FieldSize(), PlayerType::human, PlayerType::AI));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
#else
int run_in_console(int argc, char* argv[])
{
    Game game(GameSettings(FieldSize(), PlayerType::human, PlayerType::AI));
    std::cout << "App is under development" << std::endl;
    return EXIT_SUCCESS;
}
#endif


int main(int argc, char* argv[])
{
#ifdef USE_GUI
    return run_in_gui(argc, argv);
#else
    return run_in_console(argc, argv);
#endif
}
