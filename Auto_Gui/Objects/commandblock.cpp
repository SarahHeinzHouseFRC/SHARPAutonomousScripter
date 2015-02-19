#include "commandblock.h"

CommandBlock::CommandBlock(CommandBlock::Type type): AutonomousGuiObject()
{

    setMoveable();

    switch(type){

         case AUTOSTART:
            connectors.push_back(new Connector( Connector::RIGHT,Connector::SEQUNTIAL, "Sequence To"));
            setPixmap(":/Icons/Resources/startAuto.png");

             ID =0;
         break;


        case DRIVEFORWARD:
            connectors.push_back(new Connector( Connector::TOP,Connector::DOUBLE, "Drive Distance"));
            connectors.push_back(new Connector( Connector::TOP,Connector::DOUBLE, "Command Timeout"));
            connectors.push_back(new Connector( Connector::RIGHT,Connector::SEQUNTIAL, "Sequence To"));
            connectors.push_back(new Connector( Connector::LEFT,Connector::SEQUNTIAL, "Sequence From"));
            setPixmap(":/Icons/Resources/Drive GUI.png");

            ID = 1;
        break;
        case DRIVEBACKWARD:
            connectors.push_back(new Connector( Connector::TOP,Connector::DOUBLE, "Drive Distance"));
            connectors.push_back(new Connector( Connector::TOP,Connector::DOUBLE, "Command Timeout"));
            connectors.push_back(new Connector( Connector::RIGHT,Connector::SEQUNTIAL, "Sequence To"));
            connectors.push_back(new Connector( Connector::LEFT,Connector::SEQUNTIAL, "Sequence From"));

            setPixmap(":/Icons/Resources/driveBack.png");
        ID = -1;
        break;


        case ROTATERIGHT:
            connectors.push_back(new Connector( Connector::TOP,Connector::INT, "Degree to Rotate"));
            connectors.push_back(new Connector( Connector::TOP,Connector::INT, "Zero Gyro"));
            connectors.push_back(new Connector( Connector::LEFT,Connector::DOUBLE, "Command Timeout"));

            connectors.push_back(new Connector( Connector::RIGHT,Connector::SEQUNTIAL, "Sequence To"));
            connectors.push_back(new Connector( Connector::LEFT,Connector::SEQUNTIAL, "Sequence From"));
            setPixmap(":/Icons/Resources/rotateRight90.png");
        ID = 2;

        break;

        case ROTATELEFT:

            connectors.push_back(new Connector( Connector::TOP,Connector::INT, "Degree to Rotate"));
            connectors.push_back(new Connector( Connector::TOP,Connector::INT, "Zero Gyro"));
            connectors.push_back(new Connector( Connector::LEFT,Connector::DOUBLE, "Command Timeout"));

            connectors.push_back(new Connector( Connector::RIGHT,Connector::SEQUNTIAL, "Sequence To"));
            connectors.push_back(new Connector( Connector::LEFT,Connector::SEQUNTIAL, "Sequence From"));
            setPixmap(":/Icons/Resources/rotateLeft90.png");
        ID = -2;

        break;

        case TIMEOUT:

            connectors.push_back(new Connector( Connector::TOP,Connector::INT, "Time Out"));

            connectors.push_back(new Connector( Connector::RIGHT,Connector::SEQUNTIAL, "Sequence To"));
            connectors.push_back(new Connector( Connector::LEFT,Connector::SEQUNTIAL, "Sequence From"));
            setPixmap(":/Icons/Resources/Timeout.png");
        ID = 5;
        break;
        case GRABTOTE:

            connectors.push_back(new Connector( Connector::RIGHT,Connector::SEQUNTIAL, "Sequence To"));
            connectors.push_back(new Connector( Connector::LEFT,Connector::SEQUNTIAL, "Sequence From"));
            setPixmap(":/Icons/Resources/Arm.png");

        ID =-6;
        break;
        case RELEASETOTE:

           connectors.push_back(new Connector( Connector::RIGHT,Connector::SEQUNTIAL, "Sequence To"));
           connectors.push_back(new Connector( Connector::LEFT,Connector::SEQUNTIAL, "Sequence From"));

            setPixmap(":/Icons/Resources/releaseArm.png");
        ID = 6;
        break;
        case ELEVATORUP:

            connectors.push_back(new Connector( Connector::TOP,Connector::STATE, "Elevator Position"));

            connectors.push_back(new Connector( Connector::RIGHT,Connector::SEQUNTIAL, "Sequence To"));
            connectors.push_back(new Connector( Connector::LEFT,Connector::SEQUNTIAL, "Sequence From"));
            setPixmap(":/Icons/Resources/elevatorUp.png");

        ID = 7;
        break;
        case ELEVATORDOWN:

            connectors.push_back(new Connector( Connector::TOP,Connector::STATE, "Elevator Position"));

            connectors.push_back(new Connector( Connector::RIGHT,Connector::SEQUNTIAL, "Sequence To"));
            connectors.push_back(new Connector( Connector::LEFT,Connector::SEQUNTIAL, "Sequence From"));
            setPixmap(":/Icons/Resources/elevatorDown.png");
        ID = -7;
        break;
    }
    this->type = type;
}
void CommandBlock::getInputs(){


    commandIO.insert(std::make_pair<std::string,string>("ID", to_string(this->getID())));
    for(int i =0; i < connectors.size(); i++){
        if(connectors.at(i)->getConstant() != NULL && type != TIMEOUT){
        commandIO.insert(std::make_pair<std::string,string>(connectors.at(i)->getName(),connectors.at(i)->getValue()));
        }else if (type == TIMEOUT){
            commandIO.insert(std::make_pair<std::string,string>(connectors.at(i)->getName(),"100"));


        }

    }

}

unordered_multimap<string, string> *CommandBlock::sendOutputs()
{

    return &commandIO;

}



void CommandBlock::setUpConnectors(int x, int y)
{

    int r,l,t,b;
    r=0;
    l=0;
    t=0;
    b=0;
    for(int i = 0; i < connectors.size(); i++){
        Connector * currentConnector = connectors.at(i);


        switch(currentConnector->getLocation()){

        case Connector::TOP:

            currentConnector->setParentItem(this);
            currentConnector->setXY(x+36*(t),y-10);
            t++;
            break;
         case Connector::BOTTOM:
                b++;

            break;
         case Connector::LEFT:
            l++;
            currentConnector->setParentItem(this);
            currentConnector->setXY(x-9,(y+37*r));

            if(currentConnector->getType() == Connector::SEQUNTIAL){
                leftSequential= currentConnector;
            }

             break;
         case Connector::RIGHT:
            r++;
            currentConnector->setParentItem(this);
            currentConnector->setXY(x+45,(y+37*r));

            if(currentConnector->getType() == Connector::SEQUNTIAL){
                rightSequential= currentConnector;
            }

            break;
        }

    }
}

vector<Connector *> *CommandBlock::getConnectors()
{

    if(connectors.size() == 0){

        return NULL;
    }else{

    return &connectors;
    }
}

string CommandBlock::getName()
{

    //return name;
}

Connector *CommandBlock::getLeftSideSequential()
{

    return leftSequential;
}

Connector *CommandBlock::getRightSideSequential()
{

    return rightSequential;
}

int CommandBlock::getID()
{

    return ID;
}

Connector *CommandBlock::getConnectorByName(string name)
{
    for(Connector* connector: connectors){

        if(connector->getName() == name){
            printf("%d",9);
            return connector;
        }
    }
}

void CommandBlock::mousePressEvent(QGraphicsSceneMouseEvent *event)
{


    if(event->button() == Qt::RightButton){
    QPoint globalPos;
    globalPos.setX(this->getX()+180);
    globalPos.setY(this->getY()+100);

        QMenu myMenu;
        myMenu.addAction("Remove Command");
        myMenu.addAction("Switch Sequential Connectors");

        QAction* selectedItem = myMenu.exec(globalPos);
        if(selectedItem !=NULL){
            if(selectedItem->iconText().toStdString() == "Remove Command"){
                for(int i = 0; i < connectors.size(); i++){
                     connectors.at(i)->setToBeDeleted();
                     connectors.at(i)->setNotSelected();
                }
                this->setToBeDeleted();
              }else if(selectedItem->iconText().toStdString() == "Switch Sequential Connectors"){
                printf("switched");
                Connector * swap = rightSequential;
                rightSequential = leftSequential;
                leftSequential = swap;

                rightSequential->updatePixmapByLocation(Connector::RIGHT);
                leftSequential->updatePixmapByLocation(Connector::LEFT);
            }

         }
    }
}
CommandBlock::~CommandBlock(){

}
