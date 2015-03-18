/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QDialogButtonBox *buttonBox;
    QListWidget *menuList;
    QStackedWidget *stackedWidget;
    QWidget *deploy;
    QFrame *deploySettingFrame;
    QFrame *line_2;
    QLineEdit *ftpLineEdit;
    QLineEdit *localLineEdit;
    QLineEdit *USBLineEdit;
    QPushButton *testButton;
    QPushButton *localPushButton;
    QPushButton *USBPushButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *commands;
    QListWidget *loadedMenus;
    QLabel *label_5;
    QLabel *label_6;
    QStackedWidget *selectedObjectStackedWidget;
    QWidget *page;
    QFrame *frame;
    QPushButton *addRemoveMenuItemsButton;
    QLineEdit *menuNameEdit;
    QLabel *label_4;
    QPushButton *saveButtonMenu;
    QWidget *page_2;
    QPushButton *saveButtonRobotClass;
    QLineEdit *robotClassEdit;
    QLabel *label_8;
    QLabel *pixmapLabel;
    QWidget *page_3;
    QPushButton *addItemToProgramButtom;
    QPushButton *addMenuToProgram;
    QListWidget *menuCommands;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QStringLiteral("SettingsDialog"));
        SettingsDialog->resize(625, 300);
        buttonBox = new QDialogButtonBox(SettingsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(270, 260, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        menuList = new QListWidget(SettingsDialog);
        menuList->setObjectName(QStringLiteral("menuList"));
        menuList->setGeometry(QRect(10, 10, 91, 271));
        stackedWidget = new QStackedWidget(SettingsDialog);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(100, 20, 511, 231));
        deploy = new QWidget();
        deploy->setObjectName(QStringLiteral("deploy"));
        deploySettingFrame = new QFrame(deploy);
        deploySettingFrame->setObjectName(QStringLiteral("deploySettingFrame"));
        deploySettingFrame->setGeometry(QRect(0, 10, 481, 221));
        deploySettingFrame->setFrameShape(QFrame::StyledPanel);
        deploySettingFrame->setFrameShadow(QFrame::Raised);
        line_2 = new QFrame(deploySettingFrame);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(0, 60, 471, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        ftpLineEdit = new QLineEdit(deploySettingFrame);
        ftpLineEdit->setObjectName(QStringLiteral("ftpLineEdit"));
        ftpLineEdit->setGeometry(QRect(10, 20, 331, 27));
        localLineEdit = new QLineEdit(deploySettingFrame);
        localLineEdit->setObjectName(QStringLiteral("localLineEdit"));
        localLineEdit->setGeometry(QRect(10, 90, 341, 27));
        USBLineEdit = new QLineEdit(deploySettingFrame);
        USBLineEdit->setObjectName(QStringLiteral("USBLineEdit"));
        USBLineEdit->setGeometry(QRect(10, 130, 341, 27));
        testButton = new QPushButton(deploySettingFrame);
        testButton->setObjectName(QStringLiteral("testButton"));
        testButton->setGeometry(QRect(370, 20, 85, 27));
        localPushButton = new QPushButton(deploySettingFrame);
        localPushButton->setObjectName(QStringLiteral("localPushButton"));
        localPushButton->setGeometry(QRect(370, 90, 85, 27));
        USBPushButton = new QPushButton(deploySettingFrame);
        USBPushButton->setObjectName(QStringLiteral("USBPushButton"));
        USBPushButton->setGeometry(QRect(370, 130, 85, 27));
        label = new QLabel(deploySettingFrame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 81, 20));
        label_2 = new QLabel(deploySettingFrame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 110, 81, 20));
        label_3 = new QLabel(deploySettingFrame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 70, 81, 20));
        stackedWidget->addWidget(deploy);
        commands = new QWidget();
        commands->setObjectName(QStringLiteral("commands"));
        loadedMenus = new QListWidget(commands);
        loadedMenus->setObjectName(QStringLiteral("loadedMenus"));
        loadedMenus->setGeometry(QRect(10, 30, 111, 192));
        label_5 = new QLabel(commands);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 10, 57, 17));
        label_5->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(commands);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(130, 10, 57, 17));
        label_6->setAlignment(Qt::AlignCenter);
        selectedObjectStackedWidget = new QStackedWidget(commands);
        selectedObjectStackedWidget->setObjectName(QStringLiteral("selectedObjectStackedWidget"));
        selectedObjectStackedWidget->setGeometry(QRect(310, 30, 171, 191));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        frame = new QFrame(page);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 0, 181, 191));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        addRemoveMenuItemsButton = new QPushButton(frame);
        addRemoveMenuItemsButton->setObjectName(QStringLiteral("addRemoveMenuItemsButton"));
        addRemoveMenuItemsButton->setGeometry(QRect(10, 60, 121, 31));
        menuNameEdit = new QLineEdit(frame);
        menuNameEdit->setObjectName(QStringLiteral("menuNameEdit"));
        menuNameEdit->setGeometry(QRect(10, 30, 161, 27));
        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 10, 71, 17));
        saveButtonMenu = new QPushButton(frame);
        saveButtonMenu->setObjectName(QStringLiteral("saveButtonMenu"));
        saveButtonMenu->setGeometry(QRect(10, 160, 85, 27));
        selectedObjectStackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        saveButtonRobotClass = new QPushButton(page_2);
        saveButtonRobotClass->setObjectName(QStringLiteral("saveButtonRobotClass"));
        saveButtonRobotClass->setGeometry(QRect(80, 160, 85, 27));
        robotClassEdit = new QLineEdit(page_2);
        robotClassEdit->setObjectName(QStringLiteral("robotClassEdit"));
        robotClassEdit->setGeometry(QRect(0, 30, 171, 27));
        label_8 = new QLabel(page_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 10, 71, 17));
        pixmapLabel = new QLabel(page_2);
        pixmapLabel->setObjectName(QStringLiteral("pixmapLabel"));
        pixmapLabel->setGeometry(QRect(60, 70, 71, 61));
        selectedObjectStackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        selectedObjectStackedWidget->addWidget(page_3);
        addItemToProgramButtom = new QPushButton(commands);
        addItemToProgramButtom->setObjectName(QStringLiteral("addItemToProgramButtom"));
        addItemToProgramButtom->setGeometry(QRect(230, 10, 21, 20));
        addMenuToProgram = new QPushButton(commands);
        addMenuToProgram->setObjectName(QStringLiteral("addMenuToProgram"));
        addMenuToProgram->setGeometry(QRect(100, 10, 21, 20));
        menuCommands = new QListWidget(commands);
        menuCommands->setObjectName(QStringLiteral("menuCommands"));
        menuCommands->setGeometry(QRect(130, 30, 121, 192));
        stackedWidget->addWidget(commands);

        retranslateUi(SettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingsDialog, SLOT(reject()));

        stackedWidget->setCurrentIndex(1);
        selectedObjectStackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Settings", 0));
        testButton->setText(QApplication::translate("SettingsDialog", "Test", 0));
        localPushButton->setText(QApplication::translate("SettingsDialog", "Browse....", 0));
        USBPushButton->setText(QApplication::translate("SettingsDialog", "Browse....", 0));
        label->setText(QApplication::translate("SettingsDialog", "FTP Address", 0));
        label_2->setText(QApplication::translate("SettingsDialog", "USB Path", 0));
        label_3->setText(QApplication::translate("SettingsDialog", "Local Path", 0));
        label_5->setText(QApplication::translate("SettingsDialog", "Menus", 0));
        label_6->setText(QApplication::translate("SettingsDialog", "Items", 0));
        addRemoveMenuItemsButton->setText(QApplication::translate("SettingsDialog", "Add/Remove Items", 0));
        label_4->setText(QApplication::translate("SettingsDialog", "Menu Name", 0));
        saveButtonMenu->setText(QApplication::translate("SettingsDialog", "Save", 0));
        saveButtonRobotClass->setText(QApplication::translate("SettingsDialog", "Save", 0));
        label_8->setText(QApplication::translate("SettingsDialog", "Robot Class", 0));
        pixmapLabel->setText(QApplication::translate("SettingsDialog", "Icon", 0));
        addItemToProgramButtom->setText(QApplication::translate("SettingsDialog", "+", 0));
        addMenuToProgram->setText(QApplication::translate("SettingsDialog", "+", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
