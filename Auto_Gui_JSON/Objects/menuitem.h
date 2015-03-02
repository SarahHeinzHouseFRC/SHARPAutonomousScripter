#ifndef MENUITEM_H
#define MENUITEM_H
#include "autonomousguiobject.h"
#include <QLabel>
#include "ScriptedAutonomous.h"


class MenuItem : public QLabel
{
public:

    MenuItem(ScriptedAutonomous::JsonCommandBlock *relativeCommand, QWidget *parent);
    MenuItem(QWidget *parent);
    bool isSelected();
    void setCurrentlySelectedMenuItem();
    void setNotCurrentlySelectedMenuItem();
    void setNotSelected();
    void drawBox();
    QPixmap pixmap;
    ScriptedAutonomous::JsonCommandBlock *getRealtiveCommand();

    int getID();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseHoverEvent();
    bool selected;
    bool currentlySelectedMenuItem;
    ScriptedAutonomous::JsonCommandBlock* relativeCommand;

private:
    int ID;

};

#endif // MENUITEM_H
