#include "itemmanipulatordialog.h"
#include "ui_itemmanipulatordialog.h"

ItemManipulatorDialog::ItemManipulatorDialog(QWidget *parent, std::string name) :
    QDialog(parent),
    ui(new Ui::ItemManipulatorDialog)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromStdString(name));
    this->name = name;
    menuGroup = autonomous.loadedMenus.find(name)->second;

    loadCommands();
}

ItemManipulatorDialog::~ItemManipulatorDialog()
{
    delete ui;
}

void ItemManipulatorDialog::loadCommands()
{

    QStringList notInMenu;
    QStringList inMenu;

    ui->notInMenuList->clear();
    ui->inMenuList->clear();

    for(int ID : *menuGroup->menuGroupIDs)
    {
        inMenu.push_back(QString::fromStdString(autonomous.loadedCommandBlocks.find(ID)->second->relativeRobotClass));
    }

    typedef unordered_multimap<int, ScriptedAutonomous::JsonCommandBlock*>::iterator it;
    for(it iterator= autonomous.loadedCommandBlocks.begin(); iterator != autonomous.loadedCommandBlocks.end(); iterator++){

            if(!inMenu.contains(QString::fromStdString(iterator->second->relativeRobotClass)))
                notInMenu.push_back(QString::fromStdString(iterator->second->relativeRobotClass));
    }
    ui->inMenuList->addItems(inMenu);
    ui->notInMenuList->addItems(notInMenu);
}

void ItemManipulatorDialog::on_removeButton_clicked()
{

    int idToRemove = autonomous.loadedCommandBlocksByName.find(ui->inMenuList->selectedItems().at(0)->text().toStdString())->second->ID;
    for(int i = 0; i < menuGroup->menuGroupIDs->size(); i++)
    {
        if(idToRemove == menuGroup->menuGroupIDs->at(i))
        {
            menuGroup->menuGroupIDs->erase(menuGroup->menuGroupIDs->begin()+i);
        }
    }
    loadCommands();
}

void ItemManipulatorDialog::on_addButton_clicked()
{

    int idToAdd = autonomous.loadedCommandBlocksByName.find(ui->notInMenuList->selectedItems().at(0)->text().toStdString())->second->ID;
    menuGroup->menuGroupIDs->push_back(idToAdd);
    loadCommands();
}

void ItemManipulatorDialog::on_buttonBox_accepted()
{
    autonomous.exportMenus();
    close();
}
