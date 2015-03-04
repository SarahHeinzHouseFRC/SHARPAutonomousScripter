#include "enumeratedconstant.h"
#include <QComboBox>

EnumeratedConstant::EnumeratedConstant(Json::Value enums,QWidget parent): QComboBox( parent)
{
     this->setGeometry(parent->getX()-7,parent->getY()-30,100,100);

    this->enums = enums;



    this->addItem("Testing");

}
