#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "ScriptedAutonomous.h"
#include <QFileDialog>

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

private:
    Ui::SettingsDialog *ui;
    ScriptedAutonomous autonomous;
    void showEvent(QShowEvent *event);
    void loadSettings();
    string newUSBPath;
    string newLocalPath;
    string newFTPAddress;

};

#endif // SETTINGSDIALOG_H
