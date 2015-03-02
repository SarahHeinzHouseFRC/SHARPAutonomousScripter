#ifndef BUILDMENU_H
#define BUILDMENU_H

#include <QWidget>
#include"ScriptedAutonomous.h"
#include "Objects/menuitem.h"
#include "menumanager.h"

class BuildMenu : public QWidget
{
    Q_OBJECT
public:
    explicit BuildMenu(ScriptedAutonomous::JsonMenuGroup *menuGroup, unordered_multimap<int, ScriptedAutonomous::JsonCommandBlock *> *loadedCommandBlocks, MenuManager * menuManager,  QWidget *parent = 0);
    
signals:
    
public slots:

private:
    vector<MenuItem*> items;
    MenuManager* menuManager;
    static vector<MenuItem *> universalMenuItems;
    
};

#endif // BUILDMENU_H
