#ifndef SCRIPTEDAUTONOMOUS_H
#define SCRIPTEDAUTONOMOUS_H
#include <jsoncpp/json/json.h>
#include <unordered_map>


using namespace std;


class ScriptedAutonomous{

      struct JsonCommandBlock{
      int ID;
      string relativeRobotClass;
      string pathToPixmap;
      string menuGroup;
      vector<jsonConnector> connectors;
    };
    struct JsonConnector{
        int type;
        int location;
        string pathToPixmap;
    };
    struct jsonMenuItem{
        string name;
        string order;
        int relativeID;
    };

public:

    ScriptedAutonomous();
    void loadJsonCommands();
    void loadJsonPreferences();
    unordered_multimap<int,JsonCommandBlock *> loadedCommandBlocks;



    enum CommandType{
        DRIVEFORWARD,
        DRIVEBACKWARD,
        DRIVELEFT,
        DRIVERIGHT,
        AUTOSTART,
        TIMEOUT,
        ELEVATORUP,
        ELEVATORDOWN,
        GRABTOTE,
        RELEASETOTE,
        ROTATEPOSITIVE,
        ROTATENEGATIVE,
        NAVX
    };


};






#endif // SCRIPTEDAUTONOMOUS_H
