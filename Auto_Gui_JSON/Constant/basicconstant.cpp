#include "basicconstant.h"

BasicConstant::BasicConstant(AutonomousGuiObject *parent, Location location, Type type) :
    Constant(parent, location) ,
    QTextEdit()
{

    this->type = type;

    this->QTextEdit::setMinimumWidth(35);
    this->QTextEdit::setMinimumHeight(25);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->QTextEdit::setAutoFillBackground(false);
    this->setFontPointSize(6);
    this->QTextEdit::setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);


    switch(location){

    case TOP:
        this->QTextEdit::setGeometry(parent->getX()-7,parent->getY()-30,35,25);
        break;

    case LEFT:
        this->QTextEdit::setGeometry(parent->getX()-40,parent->getY()-7,35,25);
        break;
    }

    switch(type){

    case INT:
        this->QTextEdit::setStyleSheet("border: 4px solid blue");
        break;

    case DOUBLE:
        this->QTextEdit::setStyleSheet("border: 4px solid orange");
        break;

    }
}
std::string BasicConstant::getValue()
{

    return this->toPlainText().toStdString();
}
