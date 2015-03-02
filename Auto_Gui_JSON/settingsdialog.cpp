#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

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
