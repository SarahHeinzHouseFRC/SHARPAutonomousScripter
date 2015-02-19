#ifndef MENUITEM_H
#define MENUITEM_H
#include "autonomousguiobject.h"
#include <QLabel>


class MenuItem : public QLabel
{
public:


    enum MenuItemType{

        DRIVEFORWARD,
        DRIVEBACKWARD,
        DRIVELEFT,
        DRIVERIGHT,
        AUTOSTART,
        TIMEOUT,
        ELEVATORUP,
        ELEVATORDOWN,
        GRABTOTE,
        RELEASETOTE,
        ROTATERIGHT,
        ROTATELEFT
    };

    MenuItem(std::string pathToPixmap, MenuItemType type, QWidget *parent);
    bool isSelected();
    void setCurrentlySelectedMenuItem();
    void setNotCurrentlySelectedMenuItem();
    void setNotSelected();
    void drawBox();
    QPixmap pixmap;
    MenuItemType getType();


protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseHoverEvent();
    bool selected;
    bool currentlySelectedMenuItem;

private:
    MenuItemType itemType;

};

#endif // MENUITEM_H
