#include "Display/mainwindow.h"
#include <QApplication>
#include "ScriptedAutonomous.h"'"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    ScriptedAutonomous autonomous;
    autonomous.loadJsonCommands();
    w.show();
    return a.exec();
}
