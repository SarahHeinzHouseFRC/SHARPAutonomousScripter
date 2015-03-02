#include "buildmenu.h"
#include "ScriptedAutonomous.h"'"

vector<MenuItem*> BuildMenu::universalMenuItems;

BuildMenu::BuildMenu(ScriptedAutonomous::JsonMenuGroup * menuGroup, unordered_multimap<int,ScriptedAutonomous::JsonCommandBlock*>* loadedCommandBlocks, MenuManager * menuManager,QWidget *parent) :
    QWidget(parent)
{

    this->menuManager = menuManager;
    for(int currentID : *menuGroup->menuGroupIDs)
    {

       std::unordered_map<int,ScriptedAutonomous::JsonCommandBlock*>::const_iterator place = loadedCommandBlocks->find(currentID);
       if(place != loadedCommandBlocks->end())
       {
           MenuItem * item = new MenuItem(place->second,this);
           items.push_back(item);
           universalMenuItems.push_back(item);

       }
    }

    for(int i = 0; i < items.size(); i++)
    {
        if(i == 0)items.at(i)->setGeometry(20,10,61,61);
        else items.at(i)->setGeometry(10+(i*100),10,61,61);

    }

    menuManager->changeCurrentMenu(&universalMenuItems);
}
