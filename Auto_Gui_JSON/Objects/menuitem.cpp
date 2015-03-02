#include "menuitem.h"

MenuItem::MenuItem(ScriptedAutonomous::JsonCommandBlock* relativeCommand, QWidget *parent): QLabel(parent)
{

    this->relativeCommand = relativeCommand;
    pixmap.load(QString::fromStdString(relativeCommand->pathToPixmap));
    setPixmap(pixmap);
    this->ID = relativeCommand->ID;
    selected = false;
    currentlySelectedMenuItem = false;
    setFrameShape(Box);
    setFrameShadow(Raised);
    setAlignment(Qt::AlignCenter | Qt::AlignCenter);
}
MenuItem::MenuItem(QWidget * parent): QLabel(parent)
{

    this->ID = 1;
    pixmap.load(QString::fromStdString(":/Icons/Resources/startAuto.png"));
    setPixmap(pixmap);
    selected = false;
    currentlySelectedMenuItem = false;
    setFrameShape(Box);
    setFrameShadow(Raised);
    setAlignment(Qt::AlignCenter | Qt::AlignCenter);


}

bool MenuItem::isSelected()
{

    return selected;
}

void MenuItem::mousePressEvent(QMouseEvent *event)
{

    if(selected){

        selected = false;
    }else{

        selected = true;

    }
    QWidget::mousePressEvent(event);
}

void MenuItem::mouseReleaseEvent(QMouseEvent *event)
{



}

int MenuItem::getID()
{

    return ID;

}


void MenuItem::setCurrentlySelectedMenuItem()
{

    currentlySelectedMenuItem = true;

}

void MenuItem::setNotCurrentlySelectedMenuItem()
{

    currentlySelectedMenuItem = false;

}

void MenuItem::setNotSelected()
{

    selected = false;
}

void MenuItem::drawBox()
{
    if(currentlySelectedMenuItem){
        // setStyleSheet("border: 3px solid red");
        setFrameShadow(Raised);
    }else{

        //etStyleSheet("border: 1px solid red");
        setFrameShadow(Sunken);


    }

}

ScriptedAutonomous::JsonCommandBlock* MenuItem::getRealtiveCommand()
{

    return relativeCommand;
}

