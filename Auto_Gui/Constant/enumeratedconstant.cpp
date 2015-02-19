#include "enumeratedconstant.h"
#include <QComboBox>

EnumeratedConstant::EnumeratedConstant(QWidget parent): QComboBox( parent)
{
     this->setGeometry(parent->getX()-7,parent->getY()-30,100,100);
}
