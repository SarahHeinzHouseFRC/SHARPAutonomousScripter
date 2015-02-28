#include "connector.h"
#include <QMenu>
#include <QToolTip>

Connector::Connector(Connector::Location location, Type type, string name)
{

    this->location = location;
    selected = false;
    constantReady = false;
    shouldRemove = false;
    deleteConnection = false;
    constant = NULL;
    partOfConnection = false;
    this->type = type;
    this->name = name;
    setAcceptHoverEvents(true);
    setFlag(ItemStacksBehindParent);

    string arg;
    switch(type){

    case INT:
        this->pathToPixmap = ":/Icons/Resources/intConnector.png";
        arg = "INT";
        break;
    case DOUBLE:
        this->pathToPixmap = ":/Icons/Resources/doubleConnector.png";
        arg = "DOUBLE";
        break;
    case SEQUNTIAL:
        if(location == LEFT){
            this->pathToPixmap = ":/Icons/Resources/connectorIn.png";
        }
        if(location == RIGHT){
            this->pathToPixmap = ":/Icons/Resources/connectorOut.png";
        }

        break;
    case STATE:
        arg = "ENUM";
        this->pathToPixmap = ":/Icons/Resources/intConnector.png";
        break;
    }
    this->setToolTip(QString::fromStdString(name + " "+ arg));

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
    case STATE:
        this->constant = new Constant(this, Constant::STATE, constantLocation);
        break;

    }


}
Connector::~Connector(){


    delete constant;

}

