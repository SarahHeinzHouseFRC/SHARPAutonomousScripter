#ifndef MENUMANAGER_H
#define MENUMANAGER_H
#include "Objects/menuitem.h"
#include <QRunnable>
#include <QObject>
#include <QPixmap>

class MenuManager
{

public:
    MenuManager();
    void updateSelectedItem();
    void changeCurrentMenu(std::vector<MenuItem*> *menu);
    bool itemIsSelected();
    MenuItem* getCurrentlySelectedItem();


private:

    MenuItem *currentlySelectedItem;
    std::vector<MenuItem*> * currentMenu;
    std::vector<MenuItem *> selectedMenuItems;
    bool anItemIsSelected;

protected:

};

#endif // MENUMANAGER_H
