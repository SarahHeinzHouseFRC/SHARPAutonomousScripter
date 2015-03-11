#ifndef CONSTANT_H
#define CONSTANT_H
#include <QTextEdit>
#include "Objects/autonomousguiobject.h"
class Constant : public QTextEdit
{
public:
    enum Type{
        INT,
        DOUBLE,
        STATE,
        BOOL
    };
    enum Location{
        TOP,
        LEFT,
        BOTTOM
    };

    Constant(AutonomousGuiObject *parent, Type type, Location location);
    bool canBeAdded();
    std::string getValue();
    void setLine(QGraphicsLineItem* line);
    QGraphicsLineItem* getLine();
    void setValue(std::string value);

private:
    QGraphicsLineItem * line;
    Type type;
    std::string value;
protected:
    void mousePressEvent(QMouseEvent *e);
};

#endif // CONSTANT_H
