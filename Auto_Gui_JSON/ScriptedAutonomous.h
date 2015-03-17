#ifndef SCRIPTEDAUTONOMOUS_H
#define SCRIPTEDAUTONOMOUS_H
#include <jsoncpp/json/json.h>
#include <unordered_map>


using namespace std;


class ScriptedAutonomous{



public:


    struct JsonConnector{
        int type;
        int location;
        string name;
        string pathToPixmap;
    };

    struct JsonCommandBlock{
    int ID;
    string relativeRobotClass;
    string pathToPixmap;
    vector<JsonConnector*> * connectors = new vector<JsonConnector*>();
    };
    struct JsonMenuGroup{
        string name;
        vector<int> *menuGroupIDs = new vector<int>();
    };

    ScriptedAutonomous();
    void loadJsonCommands();
    void loadJsonPreferences();
    void setSettings();
    void exportCommands();
    void reloadCommands();
    void updateItemChanges();
    void exportMenus();
    void loadMenus();

    bool needsUpdated();



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
    static unordered_multimap<int,JsonCommandBlock*> loadedCommandBlocks;

    static unordered_multimap<string,JsonCommandBlock*> loadedCommandBlocksByName;

    static unordered_multimap<string, JsonMenuGroup*> loadedMenus;
    static string ftpAddress;
    static string localPath;
    static string usbPath;




private:
     Json::Value root;
     string pathToCommandsFile = "/home/lucas/Desktop/commands.json";
     string pathToMenusFile = "/home/lucas/Desktop/menus.json";
     static bool needsUpdate;

};






#endif // SCRIPTEDAUTONOMOUS_H
