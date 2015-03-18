#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "ScriptedAutonomous.h"
#include <QFileDialog>
#include <QListWidgetItem>
#include <jsoncpp/json/json.h>
#include "Display/itemmanipulatordialog.h"
#include <QInputDialog>


namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_USBPushButton_clicked();

    void on_localPushButton_clicked();

    void on_menuList_itemSelectionChanged();

    void on_loadedMenus_itemSelectionChanged();

    void on_menuCommands_itemSelectionChanged();

    void on_loadedMenus_itemClicked(QListWidgetItem *item);

    void on_saveButtonRobotClass_clicked();

    void on_addRemoveMenuItemsButton_clicked();

    void on_addMenuToProgram_clicked();

private:
    Ui::SettingsDialog *ui;
    ScriptedAutonomous autonomous;
    void showEvent(QShowEvent *event);
    void loadSettings();
    string newUSBPath;
    string newLocalPath;
    string newFTPAddress;
    QList<QString> menuString;
    QList<QString> loadedMenus;
    void loadMenus();
    void loadCommands();


};

#endif // SETTINGSDIALOG_H
