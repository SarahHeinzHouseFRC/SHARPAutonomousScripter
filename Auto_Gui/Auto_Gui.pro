#-------------------------------------------------
#
# Project created by QtCreator 2015-01-29T21:27:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Auto_Gui
TEMPLATE = app
CONFIG += static qt
QMAKE_CXXFLAGS += -std=c++11
CONFIG += qt

SOURCES += main.cpp\
    Constant/constant.cpp \
    Display/dialog.cpp \
    Display/buildcanvas.cpp \
    Managers/menumanager.cpp \
    Objects/menuitem.cpp \
    Objects/connector.cpp \
    Objects/connection.cpp \
    Objects/commandblock.cpp \
    Objects/autonomousguiobject.cpp

HEADERS += Constant/constant.h \
    Display/dialog.h \
    Display/buildcanvas.h \
    Managers/menumanager.h \
    Objects/visionobject.h \
    Objects/menuitem.h \
    Objects/connector.h \
    Objects/connection.h \
    Objects/commandblock.h \
    Objects/autonomousguiobject.h

FORMS    += dialog.ui

RESOURCES += \
    Resources.qrc
