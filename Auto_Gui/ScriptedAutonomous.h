#ifndef SCRIPTEDAUTONOMOUS_H
#define SCRIPTEDAUTONOMOUS_H
#include <QPen>




class ScriptedAutonomous{

public:

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
