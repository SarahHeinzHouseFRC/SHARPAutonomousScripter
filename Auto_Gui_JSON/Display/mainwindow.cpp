#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <jsoncpp/json/autolink.h>
#include<jsoncpp/json/json.h>



using std::make_pair;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buildView = new BuildCanvas(this, &menuManagerMain);
    buildScene = new QGraphicsScene(buildView);
    buildView->setScene(buildScene);
    buildView->setGeometry(10,this->height()*.2,geometry().width() -20,geometry().height() - ui->toolBox->geometry().height());
    buildView->setSceneRect(10,120,geometry().width() -20,geometry().height() - ui->toolBox->geometry().height());
    buildView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    buildView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    loadGuiElelements();

    connect(ui->menuDeploy->actions().at(0), SIGNAL(triggered()),this,SLOT(generateLocal()));
    connect(ui->menuDeploy->actions().at(1), SIGNAL(triggered()),this,SLOT(generateUSB()));
    connect(ui->menuFile->actions().at(0), SIGNAL(triggered()),this,SLOT(loadAutoFile()));
    connect(ui->menuDeploy->actions().at(4), SIGNAL(triggered()),this,SLOT(openSettingsMenu()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadGuiElelements()
{


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMenuManager()));
    timer->start(10);

    typedef unordered_multimap<string, ScriptedAutonomous::JsonMenuGroup*>::iterator it;
    for(it iterator= autonomous.loadedMenus.begin(); iterator != autonomous.loadedMenus.end(); iterator++)
    {
        string groupName = iterator->first;
        ScriptedAutonomous::JsonMenuGroup* menu = iterator->second;

        ui->toolBox->addTab(new BuildMenu(menu,&autonomous.loadedCommandBlocks,&menuManagerMain),QString::fromStdString(groupName));

    }
}

void MainWindow::resizeEvent(QResizeEvent * event)
{
    buildView->setGeometry(10,175,geometry().width() -20,geometry().height() - ui->toolBox->geometry().height());
    buildView->setSceneRect(10,150,geometry().width() -20 ,geometry().height() - ui->toolBox->geometry().height() - 50);
    QWidget::resizeEvent(event);
}

void MainWindow::on_graphicsView_destroyed()

{

}
void MainWindow::updateMenuManager(){
    timer->start(100);
    menuManagerMain.updateSelectedItem();
    buildView->updateCanvas();
}

void MainWindow::generateLocal()
{
    bool ok;
    string autoName = QInputDialog::getText(this, tr("Deploy File"),
                                            tr("Autonomous Name"), QLineEdit::Normal,NULL,&ok).toStdString();
    if(ok){
        Json::Value root(Json::objectValue);
        ofstream out(autonomous.localPath + "/"+ autoName + ".json", ofstream::out);
        Json::Value commands(Json::arrayValue);

        root["Autonomous Name"] =  autoName;

        vector<CommandBlock* > orderedCommands = buildView->orderConnections();

        for(CommandBlock * currentCommand : orderedCommands)
        {
            commands.append(currentCommand->toJson());

        }
        root["Commands"] = commands;

        out << root;
        out.close();
    }

}
void MainWindow::generateUSB()
{
    bool ok;
    string autoName = QInputDialog::getText(this, tr("Deploy File"),
                                            tr("Autonomous Name"), QLineEdit::Normal,NULL,&ok).toStdString();
    if(ok){
        Json::Value root(Json::objectValue);
        ofstream out(autonomous.usbPath + "/"+ autoName + ".json", ofstream::out);
        Json::Value commands(Json::arrayValue);

        root["Autonomous Name"] =  autoName;

        vector<CommandBlock* > orderedCommands = buildView->orderConnections();

        for(CommandBlock * currentCommand : orderedCommands)
        {
            commands.append(currentCommand->toJson());

        }
        root["Commands"] = commands;

        out << root;
        out.close();
    }

}

void MainWindow::openSettingsMenu()
{

    settingsDialog.show();
}

void MainWindow::loadAutoFile()
{
    vector<CommandBlock*> commandsToSendToCanvas;
    QMessageBox warningMessage;
    warningMessage.setText("Loading a file will delete your current workspace.");
    warningMessage.setInformativeText("Do you want to load file?");
    warningMessage.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int choice = warningMessage.exec();

    if(choice == QMessageBox::Yes){

        ofstream myfile;


        buildView->wipe();

        string fileName = QFileDialog::getOpenFileName(this,
                                                       tr("Open JSON File"), "/home/lucas", tr("JSON Files (*.json)")).toStdString();
        if(!fileName.empty()){

            int x = 80;
            int y = 250;

            Json::Value root;
            Json::Reader reader;
            Json::Value autonomousIn(Json::arrayValue);
            std::ifstream fileAsString(fileName, std::ifstream::binary);

            bool suc = reader.parse(fileAsString,root);

            if(!suc)
            {
                printf(reader.getFormatedErrorMessages().c_str());

            }

            autonomousIn= root["Commands"];


            //add startAuto commands
            CommandBlock * autoCommand = new CommandBlock(autonomous.loadedCommandBlocks.find(0)->second);
            autoCommand->setXY(10,250);
            autoCommand->setUpConnectors(10, 250);
            commandsToSendToCanvas.push_back(autoCommand);

            int i = 0;
            for(Json::Value command: autonomousIn)
            {
                i++;
                int ID = command["ID"].asInt();
                CommandBlock * newCommandBlock = new CommandBlock(autonomous.loadedCommandBlocks.find(ID)->second);
                Json::Value parameters = new Json::Value(Json::arrayValue);
                parameters = command["Parameters"];
                newCommandBlock->setXY(x*i,y);
                newCommandBlock->setUpConnectors(x*i,y);


                for(Connector *currentConnector : *newCommandBlock->getConnectors())
                {
                    if(currentConnector->getName().find("Sequential") == std::string::npos)
                    {
                        for(Json::Value value : parameters)
                        {
                            currentConnector->setConstantReady();


                            if(value["Name"] == currentConnector->getName()){
                                if(value["Value"].isBool())
                                {
                                    if(value["Value"].asBool())
                                        currentConnector->getConstant()->setText("T");
                                    else
                                        currentConnector->getConstant()->setText("F");
                                }else if(value["Value"].isDouble())
                                    currentConnector->getConstant()->setText(QString::fromStdString(to_string(value["Value"].asDouble())));
                                else if(value["Value"].isInt())
                                    currentConnector->getConstant()->setText(QString::fromStdString(to_string(value["Value"].asInt())));

                            }

                        }
                    }
                }
                commandsToSendToCanvas.push_back(newCommandBlock);
            }
            buildView->addCommandsToCanvas(&commandsToSendToCanvas);

        }
    }

}

void MainWindow::on_clearButton_released()
{
    buildView->wipe();
}
