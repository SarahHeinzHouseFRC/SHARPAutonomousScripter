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
    case BOTTOM:
        this->setGeometry(parent->getX()-7,parent->getY()+15,25,25);
        break;

    }


    this->setMinimumWidth(15);
    this->setMinimumHeight(15);
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
    case BOOL:
        this->setStyleSheet("border: 4px solid red");
        this->setFontPointSize(10);
        this->setText("F");
        this->setTextInteractionFlags(Qt::NoTextInteraction);
        break;
    }
}


std::string Constant::getValue()
{
    if(type == BOOL)
    {
        if(toPlainText().toStdString() == "F")
            value = "0";
        else
            value = "1";

    }else
        value = toPlainText().toStdString();
    return value;
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

void Constant::mousePressEvent(QMouseEvent *e)
{

    printf("Clicked \n");


    if(type == BOOL)
    {
        if(toPlainText().toStdString() == "T"){
            this->setStyleSheet("border: 4px solid red");
            this->setText("F");
        }else if(toPlainText().toStdString() == "F")
        {
            this->setStyleSheet("border: 4px solid green");
            this->setText("T");
        }
        QTextEdit::mousePressEvent(e);


    }
}


