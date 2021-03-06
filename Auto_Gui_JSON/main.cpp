#include "Display/mainwindow.h"
#include <QApplication>
#include <ScriptedAutonomous.h>

int main(int argc, char *argv[])
{

    ScriptedAutonomous * autonomous = new ScriptedAutonomous;
    autonomous->loadJsonCommands();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
