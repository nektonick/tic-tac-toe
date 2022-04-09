#include <QApplication>
#include <cstdlib>
#include "game.h"
#include "mainwindow.h"


// TODO: get players types and filed size from params
int run_in_gui(int argc, char* argv[])
{
    Game game(GameSettings(FieldSize(), PlayerType::human, PlayerType::AI));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


int main(int argc, char* argv[])
{
    return run_in_gui(argc, argv);
}
