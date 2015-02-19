#include "autonomousguiobject.h"

AutonomousGuiObject::AutonomousGuiObject()
{
    shouldRemove = false;

}

QRectF AutonomousGuiObject::boundingRect() const
{

    return QRectF(xCoord,yCoord,pixmap.width(),pixmap.height());

}


void AutonomousGuiObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    selected = true;
    update();
    setFlags(ItemSendsGeometryChanges);

   QGraphicsItem::mousePressEvent(event);

}

void AutonomousGuiObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    selected = false;
    //update();



     QGraphicsItem::mouseReleaseEvent(event);

}


void AutonomousGuiObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if(!pixmap.isNull())painter->drawPixmap(xCoord, yCoord, pixmap.width(),pixmap.height(),pixmap);

}

void AutonomousGuiObject::setXY(int x, int y)
{

    this->xCoord = x;
    this->yCoord = y;
}

void AutonomousGuiObject::setMoveable()
{
   // setFlags(ItemIsMovable);

}

bool AutonomousGuiObject::isSelected()
{

    return selected;

}
void AutonomousGuiObject::setNotSelected()
{

        selected = false;

}
int AutonomousGuiObject::getX(){

    return xCoord;

}
int AutonomousGuiObject::getY(){

    return yCoord;
}
bool AutonomousGuiObject::toBeDeleted()
{

    return shouldRemove;
}

void AutonomousGuiObject::setToBeDeleted()
{

    shouldRemove = true;
}
void AutonomousGuiObject::setPixmap(std::string pathToPimap){

    this->pixmap.load(QString::fromStdString(pathToPimap));

}
