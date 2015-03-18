/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLocal_Deploy;
    QAction *actionUSB_Deploy;
    QAction *actionFTP_Deply;
    QAction *actionDeploy_Options;
    QAction *actionOpen;
    QAction *actionSave;
    QWidget *centralWidget;
    QPushButton *clearButton;
    QTabWidget *toolBox;
    QMenuBar *menuBar;
    QMenu *menuDeploy;
    QMenu *menuOptions;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(902, 653);
        MainWindow->setContextMenuPolicy(Qt::DefaultContextMenu);
        actionLocal_Deploy = new QAction(MainWindow);
        actionLocal_Deploy->setObjectName(QStringLiteral("actionLocal_Deploy"));
        actionUSB_Deploy = new QAction(MainWindow);
        actionUSB_Deploy->setObjectName(QStringLiteral("actionUSB_Deploy"));
        actionFTP_Deply = new QAction(MainWindow);
        actionFTP_Deply->setObjectName(QStringLiteral("actionFTP_Deply"));
        actionDeploy_Options = new QAction(MainWindow);
        actionDeploy_Options->setObjectName(QStringLiteral("actionDeploy_Options"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Icons/Resources/scripterIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QStringLiteral("clearButton"));
        clearButton->setGeometry(QRect(10, 20, 85, 27));
        toolBox = new QTabWidget(centralWidget);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setGeometry(QRect(100, 10, 791, 111));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 902, 27));
        menuDeploy = new QMenu(menuBar);
        menuDeploy->setObjectName(QStringLiteral("menuDeploy"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuDeploy->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuDeploy->addAction(actionLocal_Deploy);
        menuDeploy->addAction(actionUSB_Deploy);
        menuDeploy->addAction(actionFTP_Deply);
        menuDeploy->addSeparator();
        menuDeploy->addAction(actionDeploy_Options);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);

        retranslateUi(MainWindow);

        toolBox->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SHARP Scripter", 0));
        actionLocal_Deploy->setText(QApplication::translate("MainWindow", "Local Deploy", 0));
        actionUSB_Deploy->setText(QApplication::translate("MainWindow", "USB Deploy", 0));
        actionFTP_Deply->setText(QApplication::translate("MainWindow", "FTP Deploy", 0));
        actionDeploy_Options->setText(QApplication::translate("MainWindow", "Deploy Settings...", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        clearButton->setText(QApplication::translate("MainWindow", "Clear Canvas", 0));
        menuDeploy->setTitle(QApplication::translate("MainWindow", "Deploy", 0));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
