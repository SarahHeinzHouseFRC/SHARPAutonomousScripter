#-------------------------------------------------
#
# Project created by QtCreator 2015-02-26T22:17:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Auto_Gui_As_Main_Window
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
    Constant/constant.cpp \
    Display/mainwindow.cpp \
    Display/buildscene.cpp \
    Display/buildcanvas.cpp \
    Managers/menumanager.cpp \
    Objects/menuitem.cpp \
    Objects/connector.cpp \
    Objects/connection.cpp \
    Objects/commandblock.cpp \
    Objects/autonomousguiobject.cpp \
    ScriptedAutonomous.cpp \
    Managers/buildmenu.cpp \
    settingsdialog.cpp

HEADERS  += \
    Constant/enumeratedconstant.h \
    Constant/constant.h \
    Display/mainwindow.h \
    Display/buildscene.h \
    Display/buildcanvas.h \
    Managers/menumanager.h \
    Objects/visionobject.h \
    Objects/menuitem.h \
    Objects/connector.h \
    Objects/connection.h \
    Objects/commandblock.h \
    Objects/autonomousguiobject.h \
    ScriptedAutonomous.h \
    Managers/buildmenu.h \
    settingsdialog.h

FORMS    += mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    Resources.qrc \
    Resources.qrc
    unix:!macx: LIBS += -ljsoncpp
