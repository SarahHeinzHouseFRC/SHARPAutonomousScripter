#ifndef CONNECTION_H
#define CONNECTION_H
#include "connector.h"
class Connection : public QLine
{
public:
    Connection(Connector *connectionTO, Connector *connectionFROM);
    bool isInScene();
    bool shouldBeRemoved();
    void setInScene();
    void update();
    bool toBeDeleted();
    void setToBeDeleted();
    void setGraphic(QGraphicsLineItem* graphic);
    Connector* getParentTO();
    Connector* getParentFROM();
    QGraphicsLineItem* getGraphic();
private:

    bool shouldRemove;
    bool inScene;
    Connector * connectorTO;
    Connector* connectorFROM;
    QGraphicsLineItem * graphic;



protected:
    void mousePressEvent();



};

#endif // CONNECTION_H
