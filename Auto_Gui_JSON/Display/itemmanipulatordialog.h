#ifndef ITEMMANIPULATORDIALOG_H
#define ITEMMANIPULATORDIALOG_H

#include <QDialog>
#include "ScriptedAutonomous.h"

namespace Ui {
class ItemManipulatorDialog;
}

class ItemManipulatorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ItemManipulatorDialog(QWidget *parent = 0, std::string name = "No Name Specified");
    ~ItemManipulatorDialog();

private slots:
    void on_addButton_clicked();

    void on_removeButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::ItemManipulatorDialog *ui;
    void loadCommands();
    ScriptedAutonomous autonomous;
    string name;
    ScriptedAutonomous::JsonMenuGroup * menuGroup;
};

#endif // ITEMMANIPULATORDIALOG_H
