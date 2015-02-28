#include "ScriptedAutonomous.h"

ScriptedAutonomous::ScriptedAutonomous()
{
    loadJsonPreferences();
    loadJsonCommands();

}
void ScriptedAutonomous::loadJsonCommands(){
    ifstream in("/home/lucas/desktop/test.json");
    Json::Value commandsIn;
    in >> commandsIn;

    for(Json::Value::iterator currentCommand = commandsIn["commands"].begin(); currentCommand != commandsIn["commands"].end(); ++currentCommand){
        JsonCommandBlock * commandBlock = new JsonCommandBlock();
        commandBlock->ID = currentCommand["ID"].asInt();
        commandBlock->pathToPixmap = currentCommand["pathToPixMap"].asString();
        printf("here");

        loadedCommandBlocks.insert(std::make_pair<int, JsonCommandBlock *>(commandBlock->ID,commandBlock));
    }










}
void ScriptedAutonomous::loadJsonPreferences(){









}
