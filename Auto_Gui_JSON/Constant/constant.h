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
        STATE
    };
    enum Location{
        TOP,
        LEFT
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
};

#endif // CONSTANT_H
