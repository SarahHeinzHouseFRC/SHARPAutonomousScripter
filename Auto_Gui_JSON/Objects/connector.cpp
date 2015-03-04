#include "connector.h"
#include <QMenu>
#include <QToolTip>

Connector::Connector(ScriptedAutonomous::JsonConnector* connectorFromJson)
{

    Location location;
    Type type;
    name = connectorFromJson->name;

    switch(connectorFromJson->location)
    {

        case 1:
            location = Connector::RIGHT;
            break;
        case 2:
            location = Connector::TOP;
            break;
        case 3:
            location = Connector::LEFT;
            break;
        case 4 :
            location = Connector::BOTTOM;
            break;
        default:
            break;

    }
    string arg;
    switch(connectorFromJson->type)
    {

        case 1:
            type = Connector::INT;
             arg = "INT";
            break;
        case 2:
            type = Connector::DOUBLE;
            arg = "DOUBLE";
            break;
        case 3:
            type = Connector::ENUM;
            arg = "ENUM";
            break;
        case 4 :
            type = Connector::BOOL;
            break;
        default:
            break;

    }
    this->setToolTip(QString::fromStdString(name + " "+ arg));

    this->location = location;
    selected = false;
    constantReady = false;
    shouldRemove = false;
    deleteConnection = false;
    constant = NULL;
    partOfConnection = false;
    this->type = type;
    this->name = connectorFromJson->name;
    this->pathToPixmap = connectorFromJson->pathToPixmap;
    setAcceptHoverEvents(true);
    setFlag(ItemStacksBehindParent);

}

Connector::Connector(Type type, Location location)
{
    this->type = type;
    this->location = location;
    if(type == SEQUNTIAL && location == RIGHT)
    {
        pathToPixmap = ":/Icons/Resources/connectorOut";
        name = "Right Sequential";
    }
    else if (location == LEFT && type == SEQUNTIAL)
    {
            pathToPixmap = ":/Icons/Resources/connectorIn";
            name = "Left Sequential";


    }

    this->location = location;
    selected = false;
    constantReady = false;
    shouldRemove = false;
    deleteConnection = false;
    constant = NULL;
    partOfConnection = false;
    this->type = type;
    setAcceptHoverEvents(true);
    setFlag(ItemStacksBehindParent);

}

string Connector::getName()
{

    return name;

}

string Connector::getValue()
{
    if(constant != NULL){
        value = constant->getValue();
    }
    return value;

}
Connector::Location Connector::getLocation(){

    return location;

}

void Connector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if(!selected){
        this->pixmap.load(QString::fromStdString(pathToPixmap));

    }
    else{
        this->pixmap.load(":/Icons/Resources/connectorSelected.png");
    }
    painter->drawPixmap(xCoord, yCoord, pixmap.width(),pixmap.height(),pixmap);
    update();
}

Constant *Connector::getConstant()
{

    return constant;
}

void Connector::updatePixmapByLocation(Location location){
    this->location = location;
    if(location == LEFT){
        this->pathToPixmap = ":/Icons/Resources/connectorIn.png";

    }else if(location == RIGHT){
        this->pathToPixmap = ":/Icons/Resources/connectorOut.png";

    }

    if(partOfConnection) deleteConnection = true;

}


void Connector::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton){


        QPoint globalPos;
        globalPos.setX(this->getX()+180);
        globalPos.setY(this->getY()+100);
        selected= true;

        QMenu myMenu;
        if(constant == NULL && type != SEQUNTIAL){
            myMenu.addAction("Add Constant");
        }
        if(constant != NULL && type != SEQUNTIAL){
            myMenu.addAction("Remove Constant");
        }
        if(type == SEQUNTIAL && partOfConnection){
            myMenu.addAction("Remove Connection");
        }
        QAction* selectedItem = myMenu.exec(globalPos);
        if(selectedItem !=NULL && this->type != SEQUNTIAL){
            if(selectedItem->iconText().toStdString() == "Add Constant"){
                if(constant == NULL){
                    createConstant();
                }
                constantReady = true;
                selected = false;
            }else if(selectedItem->iconText().toStdString() == "Remove Constant" && constant != NULL){
                selected = false;
                delete constant;
                delete constant->getLine();
                constant = NULL;

            }
        }else if(type == SEQUNTIAL){
            if(selectedItem != NULL)
            {
                if(selectedItem ->iconText().toStdString() == "Remove Connection") deleteConnection = true;
            }
        }

    }else{

        if(selected == true){
            selected = false;
        }else{

            selected = true;

        }
    }
    update();
    QGraphicsItem::mousePressEvent(event);



}

void Connector::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    toolTip();

}


bool Connector::constantIsReady()
{

    if(constantReady == NULL){

        return NULL;
    }else{

        return constantReady;
    }
}

void Connector::setInConnection()
{

    partOfConnection = true;
}

bool Connector::isPartOfConnection()
{

    return partOfConnection;
}

bool Connector::setConstantDone()
{

    constantReady = false;
}

Connector::Type Connector::getType()
{

    return type;
}

bool Connector::shouldDeleteConnection()
{
    return deleteConnection;
}

void Connector::setConstantReady()
{
    if(constant == NULL) createConstant();
    constantReady = true;

}

Json::Value Connector::toJson()
{
    Json::Value value;

    if(constant ==NULL)
        value[name] = NULL;
    else
        value[name] = constant->getValue();

    return value;
}

void Connector::setConnectionDeleted(){

    deleteConnection = false;

}
void Connector::createConstant()
{
    Constant::Location constantLocation;

    switch(location){
    case TOP:
        constantLocation = Constant::TOP;
        break;
    case LEFT:
        constantLocation = Constant::LEFT;
        break;
    }

    switch(type){

    case INT:
        this->constant = new Constant(this, Constant::INT, constantLocation);
        break;
    case DOUBLE:
        this->constant = new Constant(this, Constant::DOUBLE, constantLocation);
        break;
    case ENUM:
        this->constant = new Constant(this,Constant::STATE ,constantLocation);
        break;

    }


}
Connector::~Connector(){


    if(constant != NULL);
    delete constant;

}

