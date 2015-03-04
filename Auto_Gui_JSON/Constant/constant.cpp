#include "constant.h"

Constant::Constant(AutonomousGuiObject *parent, Type type, Location location):QTextEdit()
{
    this->type = type;

    switch(location){

    case TOP:
        this->setGeometry(parent->getX()-7,parent->getY()-30,35,25);
        break;

    case LEFT:
        this->setGeometry(parent->getX()-40,parent->getY()-7,35,25);
        break;
    }


    this->setMinimumWidth(35);
    this->setMinimumHeight(25);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setAutoFillBackground(true);
    this->setFontPointSize(6);
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    switch(type){

    case INT:
        this->setStyleSheet("border: 4px solid blue");
        break;

    case DOUBLE:
        this->setStyleSheet("border: 4px solid orange");
        break;

    case STATE:
        this->setStyleSheet("border: 4px solid purple");
        break;

    }
}


std::string Constant::getValue()
{

    return this->toPlainText().toStdString();
}

void Constant::setLine(QGraphicsLineItem *line)
{
    this->line = line;

}

QGraphicsLineItem *Constant::getLine()
{

    return line;
}

void Constant::setValue(std::string value)
{

   setText(QString::fromStdString(value));
}
