#ifndef COMMANDBLOCK_H
#define COMMANDBLOCK_H
#include "connector.h"
#include <unordered_map>
#include <QMenu>
#include "ScriptedAutonomous.h"

using namespace std;

class CommandBlock : public AutonomousGuiObject
{
public:
    CommandBlock(ScriptedAutonomous::CommandType);
    void getInputs();
    unordered_multimap<string,string>* sendOutputs();
    void setUpConnectors(int x, int y);
    vector<Connector*>* getConnectors();
    std::string getName();
    Connector* getLeftSideSequential();
    Connector* getRightSideSequential();
    int getID();
    Connector* getConnectorByName(string name);
    ~CommandBlock();


private:
    Connector* leftSequential;
    Connector * rightSequential;
    int ID;
    double value;
    ScriptedAutonomous::CommandType type;
    //QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    QPointF movingPoint;

protected:
    unordered_multimap<string,string> commandIO;
    vector<Connector*> connectors;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // COMMANDBLOCK_H
