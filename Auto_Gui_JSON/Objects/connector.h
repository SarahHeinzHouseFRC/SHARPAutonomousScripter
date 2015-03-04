#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "autonomousguiobject.h"
#include <string>
#include <QMouseEvent>
#include "Constant/constant.h"
#include "ScriptedAutonomous.h"
using namespace std;
class Connector : public AutonomousGuiObject
{




public:

    enum Location{
      TOP,
      BOTTOM,
      LEFT,
      RIGHT
    };
    enum Type{
        BOOL,
        INT,
        DOUBLE,
        STRING,
        SEQUNTIAL,
        ENUM
    };

    Connector(ScriptedAutonomous::JsonConnector* connectorFromJson);
    Connector(Type,Location);
    string getName();
    string getValue();
    Connector::Location getLocation();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    Constant *getConstant();
    bool constantIsReady();
    void setInConnection();
    bool isPartOfConnection();
    bool setConstantDone();
    Type getType();
    bool shouldDeleteConnection();
    void setConstantReady();
    Json::Value toJson();




    ~Connector();
    void updatePixmapByLocation(Location location);
    void setConnectionDeleted();

private:
    //AutonomousGuiObject parent;
    string pathToPixmap;
    string value;
    Connector::Location location;
    Constant *constant;
    bool constantReady;
    bool partOfConnection;
    Type type;
    string name;
    bool deleteConnection;
    void createConstant();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);

};

#endif // CONNECTOR_H
