#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
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


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    MenuManager menuManagerMain;
    QThreadPool pool;
    QProgressBar * generateBar;

private:
    Ui::Dialog *ui;
    QGraphicsScene *driveMenuScene;
    QGraphicsScene *buildScene;
    BuildCanvas *buildView;
    AutonomousGuiObject *object;
    vector<MenuItem*> driveBlocks;
    vector<MenuItem*> constantBlocks;
    vector<AutonomousGuiObject> visionBlocks;
    vector<AutonomousGuiObject> timeoutBlocks;
    QTimer *timer;
    vector<vector<Connector*> > connections;
    void loadGuiElelements();
    string keys[9] = {"ID","Command Timeout","Drive Speed","Elevator Speed","Time Out", "Drive Distance", "Elevator Position","Degree to Rotate","Zero Gyro"};


private slots:
    void on_graphicsView_destroyed();
    void updateMenuManager();

    void on_generateButton_released();
    void on_loadButton_released();
    void on_clearButton_released();
};

#endif // DIALOG_H
