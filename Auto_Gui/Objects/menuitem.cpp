#include "menuitem.h"

MenuItem::MenuItem(std::string pathToPixmap, MenuItemType type, QWidget *parent): QLabel(parent)
{

this->itemType = type;
selected = false;
currentlySelectedMenuItem = false;
this->pixmap.load(QString::fromStdString(pathToPixmap));
this->setPixmap(pixmap);
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

MenuItem::MenuItemType MenuItem::getType()
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

