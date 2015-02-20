#ifndef MENUITEM_H
#define MENUITEM_H
#include "autonomousguiobject.h"
#include <QLabel>
#include "ScriptedAutonomous.h"


class MenuItem : public QLabel
{
public:

    MenuItem(ScriptedAutonomous::CommandType, QWidget *parent);
    bool isSelected();
    void setCurrentlySelectedMenuItem();
    void setNotCurrentlySelectedMenuItem();
    void setNotSelected();
    void drawBox();
    QPixmap pixmap;
    ScriptedAutonomous::CommandType getType();


protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseHoverEvent();
    bool selected;
    bool currentlySelectedMenuItem;

private:
    ScriptedAutonomous::CommandType itemType;

};

#endif // MENUITEM_H
