#ifndef COMMANDBLOCK_H
#define COMMANDBLOCK_H
#include "connector.h"
#include <unordered_map>
#include <QMenu>
#include "ScriptedAutonomous.h"
#include <jsoncpp/json/json.h>

using namespace std;

class CommandBlock : public AutonomousGuiObject
{
public:
    CommandBlock(ScriptedAutonomous::JsonCommandBlock *commandFromJson);
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
    Json::Value toJson();


private:
    Connector* leftSequential;
    Connector * rightSequential;
    int ID;
    double value;
    ScriptedAutonomous::CommandType type;
    //QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    QPointF movingPoint;
    string relativeRobotClass;

protected:
    unordered_multimap<string,string> commandIO;
    vector<Connector*> connectors;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // COMMANDBLOCK_H
