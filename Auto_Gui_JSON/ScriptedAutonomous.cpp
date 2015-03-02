#include "ScriptedAutonomous.h"
#include <fstream>;


unordered_multimap<int,ScriptedAutonomous::JsonCommandBlock*> ScriptedAutonomous::loadedCommandBlocks;
unordered_multimap<string, ScriptedAutonomous::JsonMenuGroup*> ScriptedAutonomous::loadedMenus;

string ScriptedAutonomous::ftpAddress;
string ScriptedAutonomous::localPath;
string ScriptedAutonomous::usbPath;


ScriptedAutonomous::ScriptedAutonomous()
{



}
void ScriptedAutonomous::loadJsonCommands(){
    root.clear();
    Json::Reader reader;
    Json::Value autonomousIn(Json::arrayValue);
    std::ifstream fileAsString("/home/lucas/Desktop/commands.json", std::ifstream::binary);




    bool suc = reader.parse(fileAsString,root);

    if(!suc)
    {
        printf(reader.getFormatedErrorMessages().c_str());

    }

     autonomousIn= root["Commands"];

     //Load Commands

    for(Json::Value currentCommand: autonomousIn){
        JsonCommandBlock* commandBlock = new JsonCommandBlock();
        commandBlock->ID = currentCommand["ID"].asInt();
        commandBlock->pathToPixmap = currentCommand["Path To Pixmap"].asString();
        commandBlock->relativeRobotClass = currentCommand["Robot Class"].asString();

        Json::Value connectors = new Json::Value(Json::arrayValue);
        connectors = currentCommand["Connectors"];

        for(Json::Value currentConnector : connectors)
        {
            JsonConnector* connector = new JsonConnector();
            connector->name = currentConnector["Name"].asString();
            connector->type = currentConnector["Type"].asInt();
            connector->location = currentConnector["Location"].asInt();
            connector->pathToPixmap = currentConnector["Path To Pixmap"].asString();
            commandBlock->connectors->push_back(connector);

        }
        ScriptedAutonomous::loadedCommandBlocks.insert(std::make_pair<int, JsonCommandBlock*>(int(commandBlock->ID),dynamic_cast<JsonCommandBlock*>(commandBlock)));
      }

    //Load Menues

    autonomousIn = root["Menus"];

    for(Json::Value currentMenu : autonomousIn)
    {
        Json::Value menuItemIds = new Json::Value(Json::arrayValue);
        JsonMenuGroup* menu = new JsonMenuGroup();
        menu->name = currentMenu["Name"].asString();
        menuItemIds = currentMenu["Children"];

        for(Json::Value currentItem: menuItemIds) menu->menuGroupIDs->push_back(currentItem["ID"].asInt());
        loadedMenus.insert(std::make_pair<string, JsonMenuGroup*>(string(menu->name),dynamic_cast<JsonMenuGroup*>(menu)));

    }

    setSettings();
    loadJsonPreferences();

}

void ScriptedAutonomous::loadJsonPreferences(){

    Json::Reader reader;

    std::ifstream fileAsString("/home/lucas/Desktop/settings.json", std::ifstream::binary);
    root.clear();

    bool suc = reader.parse(fileAsString,root);

    ScriptedAutonomous::ftpAddress = Json::Value(root["FTP Address"]).asString();
    ScriptedAutonomous::localPath = Json::Value(root["Local Path"]).asString();
    ScriptedAutonomous::usbPath = Json::Value(root["USB Path"]).asString();


}

void ScriptedAutonomous::setSettings(){

    Json::Reader reader;

    std::ifstream fileAsString("/home/lucas/Desktop/settings.json", std::ifstream::binary);
    root.clear();

    bool suc = reader.parse(fileAsString,root);

    root["FTP Address"] =  ScriptedAutonomous::ftpAddress;
    root["Local Path"] =  ScriptedAutonomous::localPath;
    root["USB Path"] = ScriptedAutonomous::usbPath;
    ofstream out ("/home/lucas/Desktop/settings.json");

    out << root;
    out.close();
}
