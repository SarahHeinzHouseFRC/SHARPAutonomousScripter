#include "Display/dialog.h"
#include <QtWidgets>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}
