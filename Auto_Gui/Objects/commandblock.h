#ifndef COMMANDBLOCK_H
#define COMMANDBLOCK_H
#include "connector.h"
#include <unordered_map>
#include <QMenu>

using namespace std;

class CommandBlock : public AutonomousGuiObject
{
public:
	enum Type
	{
		DRIVEFORWARD,
		DRIVEBACKWARD,
		DRIVELEFT,
		DRIVERIGHT,
		AUTOSTART,
		IDLE,
		ELEVATORUP,
		ELEVATORDOWN,
		GRABTOTE,
		RELEASETOTE,
		ROTATERIGHT,
		ROTATELEFT
	};

	CommandBlock(CommandBlock::Type type);
	void getInputs();
	unordered_multimap<string, string>* sendOutputs();
	void setUpConnectors(int x, int y);
	vector<Connector*>* getConnectors();
	Connector* getLeftSideSequential();
	Connector* getRightSideSequential();
	int getID();
	Connector* getConnectorByName(string name);

	~CommandBlock();
private:
	Connector* leftSequential;
	Connector* rightSequential;
	int ID;
	double value;
	Type type;

protected:
	unordered_multimap<string, string> commandIO;
	vector<Connector*> connectors;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // COMMANDBLOCK_H

