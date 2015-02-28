#ifndef APPLOOP_H
#define APPLOOP_H
#include <QApplication>
class appLoop : QApplication
{
public:
    appLoop(int & argc, char ** argv);
};

#endif // APPLOOP_H
