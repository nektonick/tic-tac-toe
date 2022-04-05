#include <cstdlib>
#ifdef USE_GUI
#    include <QApplication>
#    include "gui/mainwindow.h"
#else
#    include <iostream>
#endif


#ifdef USE_GUI
int show_ui(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
#else
int show_console(int argc, char* argv[])
{
    std::cout << "App is under development" << std::endl;
    return EXIT_SUCCESS;
}
#endif


int main(int argc, char* argv[])
{
#ifdef USE_GUI
    return show_ui(argc, argv);
#else
    return show_console(argc, argv);
#endif
}
