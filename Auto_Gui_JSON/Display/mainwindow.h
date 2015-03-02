#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtCore>
#include <QMenu>
#include "Objects/commandblock.h"
#include "Objects//menuitem.h"
#include "Managers/menumanager.h"
#include <thread>
#include "Display/buildcanvas.h"
#include <QProgressBar>
#include <fstream>
#include <boost/algorithm/string/join.hpp>
#include <unordered_map>
#include <sstream>
#include <QFileDialog>
#include "Resources/csv_v3.h"
#include<QMessageBox>
#include "ScriptedAutonomous.h"
#include <QMainWindow>
#include "Managers/buildmenu.h"
#include "settingsdialog.h"



namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MenuManager menuManagerMain;
    QThreadPool pool;
    QProgressBar * generateBar;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *driveMenuScene;
    QGraphicsScene *buildScene;
    BuildCanvas *buildView;
    AutonomousGuiObject *object;
    vector<MenuItem*> toolBoxItems;
    vector<MenuItem*> constantBlocks;
    vector<AutonomousGuiObject> visionBlocks;
    vector<AutonomousGuiObject> timeoutBlocks;
    QTimer *timer;
    vector<vector<Connector*> > connections;
    void loadGuiElelements();
    string keys[9] = {"ID","Command Timeout","Drive Speed","Elevator Speed","Time Out", "Drive Distance", "Elevator Position","Degree to Rotate","Zero Gyro"};
    ScriptedAutonomous autonomous;
    SettingsDialog settingsDialog;
protected:
    void resizeEvent(QResizeEvent *);

private slots:
    void on_graphicsView_destroyed();
    void on_clearButton_released();
    void updateMenuManager();
    void loadAutoFile();
    void generate();
    void openSettingsMenu();

};

#endif // MAINWINDOW_H
