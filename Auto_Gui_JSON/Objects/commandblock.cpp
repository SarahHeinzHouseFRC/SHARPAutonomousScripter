#include "commandblock.h"


CommandBlock::CommandBlock(ScriptedAutonomous::CommandType type): AutonomousGuiObject(){
 // setFlags(ItemIsMovable | ItemSendsScenePositionChanges);


    switch(type){

    case ScriptedAutonomous::AUTOSTART:
        setPixmap(":/Icons/Resources/startAuto.png");
        ID =0;
        break;
    case ScriptedAutonomous::DRIVEFORWARD:
        connectors.push_back(new Connector( Connector::TOP,Connector::DOUBLE, "Drive Distance"));
        connectors.push_back(new Connector( Connector::TOP,Connector::DOUBLE, "Command Timeout"));
        setPixmap(":/Icons/Resources/Drive GUI.png");

        ID = 1;
        break;
    case ScriptedAutonomous::DRIVEBACKWARD:
        connectors.push_back(new Connector( Connector::TOP,Connector::DOUBLE, "Drive Distance"));
        connectors.push_back(new Connector( Connector::TOP,Connector::DOUBLE, "Command Timeout"));

        setPixmap(":/Icons/Resources/driveBack.png");
        ID = -1;
        break;


    case ScriptedAutonomous::ROTATEPOSITIVE:
        connectors.push_back(new Connector( Connector::TOP,Connector::INT, "Degree to Rotate"));
        connectors.push_back(new Connector( Connector::LEFT,Connector::DOUBLE, "Command Timeout"));

        setPixmap(":/Icons/Resources/rotatePositive.png");
        ID = 2;

        break;

    case ScriptedAutonomous::ROTATENEGATIVE:
        connectors.push_back(new Connector( Connector::TOP,Connector::INT, "Degree to Rotate"));
        connectors.push_back(new Connector( Connector::LEFT,Connector::DOUBLE, "Command Timeout"));
        setPixmap(":/Icons/Resources/rotateNegative.png");
        ID = -2;

        break;

    case ScriptedAutonomous::TIMEOUT:
        connectors.push_back(new Connector( Connector::TOP,Connector::INT, "Time Out"));
        setPixmap(":/Icons/Resources/Timeout.png");
        ID = 5;
        break;
    case ScriptedAutonomous::GRABTOTE:
        setPixmap(":/Icons/Resources/Arm.png");
        ID =-6;
        break;
    case ScriptedAutonomous::RELEASETOTE:
        setPixmap(":/Icons/Resources/releaseArm.png");
        ID = 6;
        break;
    case ScriptedAutonomous::ELEVATORUP:
        connectors.push_back(new Connector( Connector::TOP,Connector::STATE, "Elevator Position"));
        setPixmap(":/Icons/Resources/elevatorUp.png");
        ID = 7;
        break;
    case ScriptedAutonomous::ELEVATORDOWN:
        connectors.push_back(new Connector( Connector::TOP,Connector::STATE, "Elevator Position"));
        setPixmap(":/Icons/Resources/elevatorDown.png");
        ID = -7;
        break;
    case ScriptedAutonomous::NAVX:
        setPixmap(":/Icons/Resources/navX.png");
        connectors.push_back(new Connector( Connector::TOP,Connector::INT, "Zero Gyro"));
        ID = 8;
        break;
    }
    connectors.push_back(new Connector( Connector::RIGHT,Connector::SEQUNTIAL, "Sequence To"));
    if(type != ScriptedAutonomous::AUTOSTART) connectors.push_back(new Connector( Connector::LEFT,Connector::SEQUNTIAL, "Sequence From"));
    this->type = type;
}
void CommandBlock::getInputs(){


    commandIO.insert(std::make_pair<std::string,string>("ID", to_string(getID())));
    for(int i =0; i < connectors.size(); i++){
        if(connectors.at(i)->getConstant() != NULL){
            commandIO.insert(std::make_pair<std::string,string>(connectors.at(i)->getName(),connectors.at(i)->getValue()));
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
            return connector;
        }
    }
}

void CommandBlock::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    printf("X: %d, Y: %d", scenePos().x(),scenePos().y());
    printf("%d \n", xCoord);

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

void CommandBlock::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

/*QVariant CommandBlock::itemChange(GraphicsItemChange change, const QVariant &value)
{

    if(change == ItemScenePositionHasChanged)
    {

        changed++;
        prepareGeometryChange();
        if(changed < 1)setXY(value.toPoint().x()+ xCoord,value.toPoint().y()+ yCoord);
        else(setXY(value.toPoint().x(), value.toPoint().y()));
        setUpConnectors(value.toPoint().x() , value.toPoint().y());
    }


    //}
    //printf("%d", value.Point);

    return QGraphicsItem::itemChange(change, value);
}*/

CommandBlock::~CommandBlock(){

}

Json::Value CommandBlock::toJson()
{
    Json::Value commandAsJason;

    commandAsJason["Type"] = getID();

    for(Connector* currentConnector: connectors)
    {
        if(currentConnector->getType() != Connector::SEQUNTIAL)
         commandAsJason[currentConnector->getName()] =  std::stoi(currentConnector->getValue());

    }

    return commandAsJason;

}
