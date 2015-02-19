#include "constant.h"

Constant::Constant(AutonomousGuiObject* parent, Type type, Location location):QTextEdit()
{
	this->type = type;

	switch (location)
	{
	case TOP:
		this->setGeometry(parent->getX() - 7, parent->getY() - 30, 100, 100);
		break;

	case LEFT:
		this->setGeometry(parent->getX() - 40, parent->getY() - 7, 100, 100);
		break;
	}

	this->setMaximumWidth(35);
	this->setMaximumHeight(25);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setAlignment(Qt::AlignCenter);
	this->setAutoFillBackground(true);
	this->setFontPointSize(10);

	connect(this,SIGNAL(textChanged()),SLOT(resizeBox()));

	switch (type)
	{
	case INT:
		this->setStyleSheet("border: 4px solid blue");
		break;

	case DOUBLE:
		this->setStyleSheet("border: 4px solid orange");
		break;

	case STATE:
		this->setStyleSheet("border: 4px solid purple");
		this->document()->size().width();
		break;
	}
}


std::string Constant::getValue()
{
	return this->toPlainText().toStdString();
}

void Constant::setLine(QGraphicsLineItem* line)
{
	this->line = line;
}

QGraphicsLineItem* Constant::getLine()
{
	return line;
}

void Constant::resizeBox()
{
	printf("%d", 1);
	this->setMaximumWidth(this->document()->size().width());
	this->resize(this->document()->size().width(), this->document()->size().height());
}
