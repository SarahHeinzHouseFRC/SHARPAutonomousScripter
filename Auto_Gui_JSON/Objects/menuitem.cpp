#include "menuitem.h"

MenuItem::MenuItem(ScriptedAutonomous::CommandType type, QWidget *parent): QLabel(parent)
{

    switch(type){

    case ScriptedAutonomous::ScriptedAutonomous::AUTOSTART:
        pixmap.load(QString::fromStdString(":/Icons/Resources/startAuto.png"));
        break;
    case ScriptedAutonomous::DRIVEFORWARD:
        pixmap.load(QString::fromStdString(":/Icons/Resources/Drive GUI.png"));
        break;
    case ScriptedAutonomous::DRIVEBACKWARD:
        pixmap.load(QString::fromStdString(":/Icons/Resources/driveBack.png"));
        break;
    case ScriptedAutonomous::ROTATENEGATIVE:;
        pixmap.load(QString::fromStdString(":/Icons/Resources/rotateNegative.png"));
        break;
    case ScriptedAutonomous::ROTATEPOSITIVE:
        pixmap.load(QString::fromStdString(":/Icons/Resources/rotatePositive.png"));
        break;
    case ScriptedAutonomous::TIMEOUT:
        pixmap.load(QString::fromStdString(":/Icons/Resources/Timeout.png"));
        break;
    case ScriptedAutonomous::GRABTOTE:
        pixmap.load(QString::fromStdString(":/Icons/Resources/Arm.png"));
        break;
    case ScriptedAutonomous::RELEASETOTE:
        pixmap.load(QString::fromStdString(":/Icons/Resources/releaseArm.png"));
        break;
    case ScriptedAutonomous::ELEVATORUP:
        pixmap.load(QString::fromStdString(":/Icons/Resources/elevatorUp.png"));;
        break;
    case ScriptedAutonomous::ELEVATORDOWN:
        pixmap.load(QString::fromStdString(":/Icons/Resources/elevatorDown.png"));
        break;
    case ScriptedAutonomous::NAVX:
        pixmap.load(QString::fromStdString(":/Icons/Resources/navX.png"));
        break;
    }
    setPixmap(pixmap);
    this->itemType = type;
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

ScriptedAutonomous::CommandType MenuItem::getType()
{

    return itemType;

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

