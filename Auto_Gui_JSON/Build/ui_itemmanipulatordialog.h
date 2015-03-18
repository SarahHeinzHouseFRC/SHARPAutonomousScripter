/********************************************************************************
** Form generated from reading UI file 'itemmanipulatordialog.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMMANIPULATORDIALOG_H
#define UI_ITEMMANIPULATORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ItemManipulatorDialog
{
public:
    QDialogButtonBox *buttonBox;
    QListWidget *notInMenuList;
    QListWidget *inMenuList;
    QPushButton *removeButton;
    QPushButton *addButton;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *ItemManipulatorDialog)
    {
        if (ItemManipulatorDialog->objectName().isEmpty())
            ItemManipulatorDialog->setObjectName(QStringLiteral("ItemManipulatorDialog"));
        ItemManipulatorDialog->resize(332, 300);
        buttonBox = new QDialogButtonBox(ItemManipulatorDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(240, 40, 81, 241));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        notInMenuList = new QListWidget(ItemManipulatorDialog);
        notInMenuList->setObjectName(QStringLiteral("notInMenuList"));
        notInMenuList->setGeometry(QRect(10, 40, 101, 192));
        inMenuList = new QListWidget(ItemManipulatorDialog);
        inMenuList->setObjectName(QStringLiteral("inMenuList"));
        inMenuList->setGeometry(QRect(130, 40, 101, 192));
        removeButton = new QPushButton(ItemManipulatorDialog);
        removeButton->setObjectName(QStringLiteral("removeButton"));
        removeButton->setGeometry(QRect(160, 240, 41, 21));
        addButton = new QPushButton(ItemManipulatorDialog);
        addButton->setObjectName(QStringLiteral("addButton"));
        addButton->setGeometry(QRect(30, 240, 41, 21));
        label = new QLabel(ItemManipulatorDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 71, 17));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(ItemManipulatorDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(150, 20, 57, 17));
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(ItemManipulatorDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ItemManipulatorDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ItemManipulatorDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ItemManipulatorDialog);
    } // setupUi

    void retranslateUi(QDialog *ItemManipulatorDialog)
    {
        ItemManipulatorDialog->setWindowTitle(QApplication::translate("ItemManipulatorDialog", "Dialog", 0));
        removeButton->setText(QApplication::translate("ItemManipulatorDialog", "<<", 0));
        addButton->setText(QApplication::translate("ItemManipulatorDialog", ">>", 0));
        label->setText(QApplication::translate("ItemManipulatorDialog", "Not In Menu", 0));
        label_2->setText(QApplication::translate("ItemManipulatorDialog", "In Menu", 0));
    } // retranslateUi

};

namespace Ui {
    class ItemManipulatorDialog: public Ui_ItemManipulatorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMMANIPULATORDIALOG_H
