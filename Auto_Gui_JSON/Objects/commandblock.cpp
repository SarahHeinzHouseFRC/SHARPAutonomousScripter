#include "commandblock.h"


CommandBlock::CommandBlock(ScriptedAutonomous::JsonCommandBlock* commandFromJson): AutonomousGuiObject(){
 // setFlags(ItemIsMovable | ItemSendsScenePositionChanges);


    this->ID = commandFromJson->ID;

    setPixmap(commandFromJson->pathToPixmap);
    this->relativeRobotClass = commandFromJson->relativeRobotClass;

    for(ScriptedAutonomous::JsonConnector* currentConnector: *commandFromJson->connectors)
    {
        connectors.push_back(new Connector(currentConnector));
    }
    if(ID !=0)
        connectors.push_back(new Connector(Connector::SEQUNTIAL,Connector::LEFT));
    connectors.push_back(new Connector(Connector::SEQUNTIAL,Connector::RIGHT));

    printf("%d", connectors.size());

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
            currentConnector->setXY(x-9,(y+37*l));

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



CommandBlock::~CommandBlock(){

}

Json::Value CommandBlock::toJson()
{
    Json::Value commandAsJason;
    Json::Value parameters(Json::arrayValue);


    for(Connector* currentConnector: connectors)
    {
        if(currentConnector->getName().find("Sequential") == std::string::npos )
         {
            parameters.append(currentConnector->toJson());
        }
    }
    commandAsJason["Command"] = relativeRobotClass;
    commandAsJason["ID"] = ID;
    commandAsJason["Parameters"] = parameters;

    return commandAsJason;

}
