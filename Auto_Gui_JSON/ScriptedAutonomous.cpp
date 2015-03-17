#include "ScriptedAutonomous.h"
#include <fstream>;


unordered_multimap<int,ScriptedAutonomous::JsonCommandBlock*> ScriptedAutonomous::loadedCommandBlocks;
unordered_multimap<string,ScriptedAutonomous::JsonCommandBlock*> ScriptedAutonomous::loadedCommandBlocksByName;
unordered_multimap<string, ScriptedAutonomous::JsonMenuGroup*> ScriptedAutonomous::loadedMenus;

string ScriptedAutonomous::ftpAddress;
string ScriptedAutonomous::localPath;
string ScriptedAutonomous::usbPath;
bool ScriptedAutonomous::needsUpdate;


ScriptedAutonomous::ScriptedAutonomous()
{

    needsUpdate = false;


}
void ScriptedAutonomous::loadJsonCommands(){

    needsUpdate = false;

    loadedCommandBlocks.clear();
    loadedCommandBlocksByName.clear();
    loadedMenus.clear();
    root.clear();
    Json::Reader reader;
    Json::Value autonomousIn(Json::arrayValue);
    std::ifstream fileAsString(pathToCommandsFile, std::ifstream::binary);

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
        ScriptedAutonomous::loadedCommandBlocksByName.insert(std::make_pair<string, JsonCommandBlock*>(string(commandBlock->relativeRobotClass),dynamic_cast<JsonCommandBlock*>(commandBlock)));
    }

    //Load Menues

    root.clear();
    std::ifstream menufileAsString(pathToMenusFile, std::ifstream::binary);
    reader.parse(menufileAsString,root);

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
    //setSettings();
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

    ofstream out ("/home/lucas/Desktop/settings.json");
    std::ifstream fileAsString("/home/lucas/Desktop/settings.json", std::ifstream::binary);
    root.clear();

    out << root;
    out.close();


    bool suc = reader.parse(fileAsString,root);

    root["FTP Address"] =  ScriptedAutonomous::ftpAddress;
    root["Local Path"] =  ScriptedAutonomous::localPath;
    root["USB Path"] = ScriptedAutonomous::usbPath;


    out << root;
    out.close();
}

void ScriptedAutonomous::exportCommands()
{

    ofstream out("/home/lucas/Desktop/commands.json", ofstream::out);



    Json::Value root;
    Json::Value commandsToExport(Json::arrayValue);
    typedef unordered_multimap<int, ScriptedAutonomous::JsonCommandBlock*>::iterator it;
    for(it iterator= loadedCommandBlocks.begin(); iterator != loadedCommandBlocks.end(); iterator++)
    {
        JsonCommandBlock *commandBlock = iterator->second;
        Json::Value commandToExport;

        commandToExport["ID"] = commandBlock->ID;
        commandToExport["Robot Class"] = commandBlock->relativeRobotClass;
        commandToExport["Path To Pixmap"] = commandBlock->pathToPixmap;

        Json::Value parameters(Json::arrayValue);

        for(JsonConnector* connector : *commandBlock->connectors)
        {
            Json::Value parameter;
            parameter["Name"] = connector->name;
            parameter["Location"] = connector->location;
            parameter["Type"] = connector->type;
            parameter["Path To Pixmap"] = connector->pathToPixmap;

            parameters.append(parameter);
        }
        commandToExport["Connectors"] = parameters;
        commandsToExport.append(commandToExport);
    }
    root["Commands"] = commandsToExport;
    out << root;
    out.close();


}

void ScriptedAutonomous::updateItemChanges()
{
    needsUpdate = true;
}

void ScriptedAutonomous::exportMenus()
{
    ofstream out("/home/lucas/Desktop/menus.json", ofstream::out);

    Json::Value root;
    Json::Value menuToExport;
     Json::Value menus;

    typedef unordered_multimap<string, ScriptedAutonomous::JsonMenuGroup*>::iterator it;
    for(it iterator= loadedMenus.begin(); iterator != loadedMenus.end(); iterator++)
    {
        JsonMenuGroup *menu = iterator->second;
        menuToExport["Name"] = menu->name;
        Json::Value children(Json::arrayValue);

        for(int ID : *menu->menuGroupIDs)
        {
            Json::Value child;
            child["ID"] = ID;
            children.append(child);
        }
        menuToExport["Children"] = children;
        menus.append(menuToExport);
    }
    root["Menus"] = menus;
    out << root;
    out.close();

    needsUpdate = true;
}

bool ScriptedAutonomous::needsUpdated()
{
    return needsUpdate;
}
