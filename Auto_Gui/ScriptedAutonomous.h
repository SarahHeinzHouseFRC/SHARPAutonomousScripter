#ifndef SCRIPTEDAUTONOMOUS_H
#define SCRIPTEDAUTONOMOUS_H




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
        ROTATERIGHT,
        ROTATELEFT,
        NAVX
    };

};


#endif // SCRIPTEDAUTONOMOUS_H
