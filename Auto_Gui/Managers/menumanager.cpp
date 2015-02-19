#include "menumanager.h"

MenuManager::MenuManager()
{



}
void MenuManager::updateSelectedItem(){

    int k = 0;
    std::reverse(currentMenu->begin(),currentMenu->end());
    for(int i = 0; i < currentMenu->size(); i++)
    {
           if(currentMenu->at(i)->isSelected()){
               k++;
               anItemIsSelected = true;
             if(k > 1){

                currentlySelectedItem->setNotCurrentlySelectedMenuItem();
                currentlySelectedItem->setNotSelected();
                currentlySelectedItem = currentMenu->at(i);
              }else{
            currentlySelectedItem = currentMenu->at(i);
            currentlySelectedItem->setCurrentlySelectedMenuItem();
            currentlySelectedItem->drawBox();

             }
           }else{
               if(k == 0 ){anItemIsSelected = false;}
               currentMenu->at(i)->setNotCurrentlySelectedMenuItem();
               currentMenu->at(i)->drawBox();
           }
    }
}

void MenuManager::changeCurrentMenu(std::vector<MenuItem *> *menu)
{

    currentMenu = menu;


}

bool MenuManager::itemIsSelected()
{

    return anItemIsSelected;

}

MenuItem *MenuManager::getCurrentlySelectedItem()
{

    return currentlySelectedItem;
}

