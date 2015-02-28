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
    buildView->setGeometry(10,this->height()*.1,geometry().width() -20,geometry().height() - ui->toolBox->geometry().height());
    buildView->setSceneRect(10,120,geometry().width() -20,geometry().height() - ui->toolBox->geometry().height());
    buildView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    buildView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);



    loadGuiElelements();

    connect(ui->menuDeploy->actions().at(0), SIGNAL(triggered()),this,SLOT(on_generateButton_released()));
    connect(ui->menuFile->actions().at(0), SIGNAL(triggered()),this,SLOT(on_loadButton_released()));


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

    toolBoxItems.push_back(new MenuItem(ScriptedAutonomous::DRIVEFORWARD, ui->driveTab));
    toolBoxItems.push_back(new MenuItem( ScriptedAutonomous::DRIVEBACKWARD,ui->driveTab));
    toolBoxItems.push_back(new MenuItem( ScriptedAutonomous::ROTATEPOSITIVE, ui->driveTab));
    toolBoxItems.push_back(new MenuItem( ScriptedAutonomous::ROTATENEGATIVE,ui->driveTab));

    toolBoxItems.push_back(new MenuItem(ScriptedAutonomous::GRABTOTE, ui->armTab));
    toolBoxItems.push_back(new MenuItem(ScriptedAutonomous::RELEASETOTE, ui->armTab));

    toolBoxItems.push_back(new MenuItem( ScriptedAutonomous::ELEVATORUP, ui->elevatorTab));
    toolBoxItems.push_back(new MenuItem( ScriptedAutonomous::ELEVATORDOWN, ui->elevatorTab));
    toolBoxItems.push_back(new MenuItem( ScriptedAutonomous::NAVX, ui->sensorTab));

    toolBoxItems.push_back(new MenuItem(ScriptedAutonomous::AUTOSTART, ui->startStopTab));

    toolBoxItems.push_back(new MenuItem(ScriptedAutonomous::TIMEOUT,ui->timeoutTab));



    menuManagerMain.changeCurrentMenu(&toolBoxItems);

    int k = 0;
    for(int i = 0; i < toolBoxItems.size(); i++)
    {
        if(i > 0){
            if(toolBoxItems.at(i)->parent() != toolBoxItems.at(i-1)->parent()) k = 0;}

        toolBoxItems.at(i)->setGeometry(10+(k*80),10,61,61);
        k++;

    }

}

void MainWindow::resizeEvent(QResizeEvent * event)
{
    buildView->setGeometry(10,150,geometry().width() -20,geometry().height() - ui->toolBox->geometry().height());
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

void MainWindow::on_generateButton_released()
{

    Json::Value root(Json::objectValue);
    ofstream out("BUTTS.json", ofstream::out);
    Json::Value commands(Json::arrayValue);

    root["Autonomous Name"] =  ui->fileNameTextEdit->text().toStdString();

    vector<CommandBlock* > orderedCommands = buildView->orderConnections();

    for(CommandBlock * currentCommand : orderedCommands)
    {
        printf("About to add commands");
        commands.append(currentCommand->toJson());
    }
    root["Commands"] = commands;

    out << root;
    out.close();

}

void MainWindow::on_loadButton_released()
{

    QMessageBox warningMessage;
    warningMessage.setText("Loading a file will delete your current workspace.");
    warningMessage.setInformativeText("Do you want to load file?");
    warningMessage.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int choice = warningMessage.exec();

    if(choice == QMessageBox::Yes){

        buildView->wipe();

        std::unordered_map<std::string,vector<string>*> commandsIN;

        string value;
        string fileName = QFileDialog::getOpenFileName(this,
                                                       tr("Open CSV File"), "/home/lucas", tr("CSV Files (*.csv)")).toStdString();
        if(!fileName.empty()){
            for(int i = 0; i < sizeof(keys)/sizeof(keys[0]); i++){
                io::CSVReader<1> in(fileName);
                in.read_header(io::ignore_extra_column,string(keys[i]));
                commandsIN.insert(std::make_pair<string, vector<string>*>(string(keys[i]),new vector<string>(sizeof(keys)/sizeof(keys[0]))));
                while(in.read_row(value)){
                    std::unordered_map<std::string,vector<string>* >::const_iterator place  = commandsIN.find(std::string(keys[i]));
                    place->second->push_back(value);
                }
            }
            vector <CommandBlock *> commandsToSendToCanvas;
            int x = 10;
            int y = 250;

            commandsToSendToCanvas.push_back(new CommandBlock(ScriptedAutonomous::AUTOSTART));
            commandsToSendToCanvas.at(0)->setXY(x,y);
            commandsToSendToCanvas.at(0)->setUpConnectors(x,y);

            std::unordered_map<std::string,vector<string>* >::const_iterator place = commandsIN.find("ID");

            for(int i =0; i < place->second->size();i++){

                if(!place->second->at(i).empty()){
                    int currentID = atoi(place->second->at(i).c_str());
                    CommandBlock* newCommand;
                    string value;
                    vector<string*> constantKeys;
                    x+=100;

                    switch(currentID){
                    case(1):
                        newCommand = new CommandBlock(ScriptedAutonomous::DRIVEFORWARD);
                        break;
                    case(-1):
                        newCommand = new CommandBlock(ScriptedAutonomous::DRIVEBACKWARD);
                        break;
                    case(2):
                        newCommand = new CommandBlock(ScriptedAutonomous::ROTATEPOSITIVE);
                        break;
                    case(-2):
                        newCommand = new CommandBlock(ScriptedAutonomous::ROTATENEGATIVE);
                        break;
                    case(5):
                        newCommand = new CommandBlock(ScriptedAutonomous::TIMEOUT);
                        break;
                    case(6):
                        newCommand = new CommandBlock(ScriptedAutonomous::RELEASETOTE);
                        break;
                    case(-6):
                        newCommand = new CommandBlock(ScriptedAutonomous::GRABTOTE);
                        break;
                    case(7):
                        newCommand = new CommandBlock(ScriptedAutonomous::ELEVATORUP);
                        break;
                    case(-7):
                        newCommand = new CommandBlock(ScriptedAutonomous::ELEVATORDOWN);
                        break;
                    case(8):
                        newCommand = new CommandBlock(ScriptedAutonomous::NAVX);
                        break;
                    default:
                        break;
                    }

                    newCommand->setXY(x,y);
                    newCommand->setUpConnectors(x,y);
                    for(int k = 0; k < newCommand->getConnectors()->size(); k++){

                        Connector* currentConnector = newCommand->getConnectors()->at(k);
                        if(currentConnector->getName().find("Sequence") == std::string::npos){
                            ui->debug->setText(QString::fromStdString(currentConnector->getName()));
                            constantKeys.push_back(new string(currentConnector->getName()));
                        }
                        for(string* key : constantKeys){
                            std::unordered_map<std::string,vector<string>* >::const_iterator newPlace  = commandsIN.find(std::string(*key));
                            value = newPlace->second->at(i);
                            newCommand->getConnectorByName(*key)->setConstantReady();
                            newCommand->getConnectorByName(*key)->getConstant()->setText(QString::fromStdString(value));
                        }
                    }
                    commandsToSendToCanvas.push_back(newCommand);
                }
            }
            buildView->addCommandsToCanvas(&commandsToSendToCanvas);
        }
    }
}


void MainWindow::on_clearButton_released()
{
    buildView->wipe();
}
