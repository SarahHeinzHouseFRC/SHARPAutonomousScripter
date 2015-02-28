#include "enumeratedconstant.h"
#include <QComboBox>

numeratedConstant::EnumeratedConstant(QWidget parent): QComboBox( parent)
{
     this->setGeometry(parent->getX()-7,parent->getY()-30,100,100);
}
