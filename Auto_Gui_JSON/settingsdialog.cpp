#include "settingsdialog.h"
#include "ui_settingsdialog.h"
SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    menuString.push_back("Deploy");
    menuString.push_back("Commands");
    ui->menuList->addItems(menuString);

    loadMenus();

}

SettingsDialog::~SettingsDialog()
{

    delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{

    if(!newLocalPath.empty() && newLocalPath != autonomous.localPath)
    {

        autonomous.localPath = newLocalPath;

    }

    if(!newUSBPath.empty() && newUSBPath != autonomous.usbPath)
    {

        autonomous.usbPath = newUSBPath;

    }

    autonomous.setSettings();
    close();
}

void SettingsDialog::on_buttonBox_rejected()
{
    close();
}

void SettingsDialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    loadSettings();
}

void SettingsDialog::on_USBPushButton_clicked()
{

    newUSBPath = QFileDialog::getExistingDirectory(this,
                                                   tr("Select USB Path"), "/media", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks).toStdString();

    autonomous.usbPath = newUSBPath;
    loadSettings();

}

void SettingsDialog::on_localPushButton_clicked()
{

    newLocalPath = QFileDialog::getExistingDirectory(this,
                                                     tr("Selected Local Path"),"/home",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks).toStdString();

    autonomous.localPath = newLocalPath;
    loadSettings();

}
void SettingsDialog::loadSettings()
{



    ui->ftpLineEdit->setText(QString::fromStdString(autonomous.ftpAddress));
    ui->localLineEdit->setText(QString::fromStdString(autonomous.localPath));
    ui->USBLineEdit->setText(QString::fromStdString(autonomous.usbPath));


}

void SettingsDialog::loadMenus()
{

    typedef unordered_multimap<string, ScriptedAutonomous::JsonMenuGroup*>::iterator it;
    for(it iterator= autonomous.loadedMenus.begin(); iterator != autonomous.loadedMenus.end(); iterator++)
    {
        loadedMenus.push_back(QString::fromStdString(iterator->first));
    }
    ui->loadedMenus->addItems(loadedMenus);
}

void SettingsDialog::loadCommands()
{
    ui->menuNameEdit->setText(ui->loadedMenus->selectedItems().at(0)->text());
    ui->selectedObjectStackedWidget->setCurrentIndex(0);

    ui->menuCommands->clear();

    QList<QString> commands;

    QString name = ui->loadedMenus->selectedItems().at(0)->text();

    for(int id: *autonomous.loadedMenus.find(name.toStdString())->second->menuGroupIDs){

        commands.push_back(QString::fromStdString(autonomous.loadedCommandBlocks.find(id)->second->relativeRobotClass));

    }
    ui->menuCommands->addItems(commands);

commands.clear();



}

void SettingsDialog::on_menuList_itemSelectionChanged()
{
    QString name = ui->menuList->selectedItems().at(0)->text();

    if(name == "Deploy")
        ui->stackedWidget->setCurrentIndex(0);
    else if(name == "Commands")
        ui->stackedWidget->setCurrentIndex(1);
}


void SettingsDialog::on_loadedMenus_itemSelectionChanged()
{

        ui->menuNameEdit->setText(ui->loadedMenus->selectedItems().at(0)->text());
        ui->selectedObjectStackedWidget->setCurrentIndex(0);

        ui->menuCommands->clear();

        QList<QString> commands;

        QString name = ui->loadedMenus->selectedItems().at(0)->text();

        for(int id: *autonomous.loadedMenus.find(name.toStdString())->second->menuGroupIDs){

            commands.push_back(QString::fromStdString(autonomous.loadedCommandBlocks.find(id)->second->relativeRobotClass));

        }
        ui->menuCommands->addItems(commands);

    commands.clear();

}

void SettingsDialog::on_menuCommands_itemSelectionChanged()
{

    string name;
    QPixmap pixmap;
    if(ui->menuCommands->selectedItems().size() !=0){
        name = ui->menuCommands->selectedItems().at(0)->text().toStdString();

        //not sure if doing this has any point, but I want to stick to using IDs
        int ID = autonomous.loadedCommandBlocksByName.find(name)->second->ID;
        pixmap.load(QString::fromStdString(autonomous.loadedCommandBlocks.find(ID)->second->pathToPixmap));
        ui->pixmapLabel->setPixmap(pixmap);
        ui->selectedObjectStackedWidget->setCurrentIndex(1);

        ui->robotClassEdit->setText(QString::fromStdString(autonomous.loadedCommandBlocks.find(ID)->second->relativeRobotClass));
    }

}

void SettingsDialog::on_loadedMenus_itemClicked(QListWidgetItem *item)
{
    ui->selectedObjectStackedWidget->setCurrentIndex(0);
}

void SettingsDialog::on_saveButtonRobotClass_clicked()
{

    printf("testing");
    int ID = autonomous.loadedCommandBlocksByName.find(ui->menuCommands->selectedItems().at(0)->text().toStdString())->second->ID;

    autonomous.loadedCommandBlocks.find(ID)->second->relativeRobotClass = ui->robotClassEdit->text().toStdString();

    //Reload Changes Made To A Command

       autonomous.exportCommands();
       autonomous.loadJsonCommands();

       loadCommands();
}
