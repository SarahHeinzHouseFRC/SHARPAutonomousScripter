#include "dialog.h"
#include "ui_dialog.h"
#include <libssh/sftp.h>

using std::make_pair;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //testScene->addItem(new DriveCommand("/home/lucas/Desktop/Auto_Gui/driveForward.png"));

    driveMenuScene = new QGraphicsScene(this);
    buildScene = new QGraphicsScene(this);
    buildView = new BuildCanvas(this, &menuManagerMain);
    buildView->setScene(buildScene);
    buildView->setGeometry(10,120,790,360);
    buildView->setSceneRect(10,120,2000,340);
    buildView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    buildView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //ui->driveGraphicsView->setScene(driveMenuScene);

    //buildScene->addItem(new MenuItem("/home/lucas/Desktop/Auto_Gui/driveForward.png", MenuItem::DRIVE));

    //ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    //connect(ui->graphicsView,SIGNAL(customContextMenuRequested(const QPoint)),this,SLOT(ShowContextMenu(QPoint)));

    loadGuiElelements();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMenuManager()));
    timer->start(10);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::loadGuiElelements()
{
    toolBoxItems.push_back(new MenuItem(ScriptedAutonomous::DRIVEFORWARD, ui->driveTab));
    toolBoxItems.push_back(new MenuItem( ScriptedAutonomous::DRIVEBACKWARD,ui->driveTab));
    toolBoxItems.push_back(new MenuItem( ScriptedAutonomous::ROTATERIGHT, ui->driveTab));
    toolBoxItems.push_back(new MenuItem( ScriptedAutonomous::ROTATELEFT,ui->driveTab));

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

void Dialog::on_graphicsView_destroyed()
{

}
void Dialog::updateMenuManager(){
    timer->start(100);
    menuManagerMain.updateSelectedItem();
    buildView->updateCanvas();
}

void Dialog::on_generateButton_released()
{;

    int sizeOfKeys = sizeof(keys) / sizeof(keys[0]);

    unordered_multimap<std::string,std::vector<string>*> outPutStuff;

    for(int i = 0; i < sizeOfKeys; i++){
        outPutStuff.insert(std::make_pair<string , vector<string>*>
                           (std::string(keys[i]),
                            new std::vector<string>(sizeOfKeys)));
    }

    vector<unordered_multimap<string,string>*> commandIOVector;
    ofstream csvFile;
    string sendCommmandCode;

    vector<CommandBlock* > orderedCommands = buildView->orderConnections();
    vector<string> commandCode;
    for(int i = 0; i < orderedCommands.size(); i++){
        orderedCommands.at(i)->getInputs();
        //ommandCode.push_back(std::to_string(orderedCommands.at(i)->getID()));
        commandIOVector.push_back(orderedCommands.at(i)->sendOutputs());
    }
    csvFile.open("/home/lucas/Desktop/autonomousVariables.csv");

    sendCommmandCode = boost::algorithm::join(keys,",");
    csvFile << sendCommmandCode << endl;

    /* for(int i = 0; i < commandIOVector.size();i++){

            for(int k = 0; k  < sizeof(keys) / sizeof(keys[0]); k++){
                std::unordered_map<std::string,string>::const_iterator place  = currentCommandBlock->find(std::string(keys[k]));
                std::unordered_map<std::string,vector<string>*>::const_iterator placeVector = outPutStuff.find(std::string(keys[k]));
                if(place == currentCommandBlock->end()){
                    placeVector->second->push_back("0");
                    //printf("%d \n", 0);
                }else{
                    placeVector->second->push_back(place->second);
                }
            }
        }


        for(int i = 0; i < outPutStuff.size();i++){
            std::unordered_map<std::string,vector<string>*>::const_iterator place  = outPutStuff.find(std::string(keys[i]));
            vector<string> outPutString;
            for(int k = 0; k < place->second->size(); k++){
                if(place->second->at(k) != ""){
                outPutString.push_back(place->second->at(k));
                }
            }



       }*/



    for(int i = 0; i < commandIOVector.size(); i++){
        vector<string> outPutString;
        unordered_multimap<string,string>* currentCommand = commandIOVector.at(i);
        for(int k =0; k < sizeOfKeys; k++){
            std::unordered_map<std::string,string>::const_iterator place  = currentCommand->find(std::string(keys[k]));
            if(place == currentCommand->end()){
                outPutString.push_back("0");
            }else{
                outPutString.push_back(place->second);
            }

        }
        //copy(outPutString.begin(), outPutString.end(), ostream_iterator<string>(send, ","));
        string send = boost::algorithm::join(outPutString,",");
        csvFile << send << endl;

    }

    csvFile.close();


    //sftp to the roboRIO

    // TODO: Find a better way to ftp files to the roboRIO

    /* -> cheaty way*/ system("python /home/lucas/Desktop/Auto_Gui/Python_Scripts/ftpCSV.py");



}

void Dialog::on_loadButton_released()
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
                                                       tr("Open Image"), "/home/lucas", tr("CSV Files (*.csv)")).toStdString();
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
            std::unordered_map<std::string,vector<string>*> dataWithoutWhiteSpaces;

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
                        newCommand = new CommandBlock(ScriptedAutonomous::ROTATERIGHT);
                        break;
                    case(-2):
                        newCommand = new CommandBlock(ScriptedAutonomous::ROTATELEFT);
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
                        newCommand = new CommandBlock(ScriptedAutonomous::ELEVATORDOWN);
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
                        commandsToSendToCanvas.push_back(newCommand);
                    }

                }
                buildView->addCommandsToCanvas(&commandsToSendToCanvas);
            }
        }
    }
}


void Dialog::on_clearButton_released()
{
    buildView->wipe();
}
