#ifndef BASICCONSTANT_H
#define BASICCONSTANT_H

#include "constant.h"

class BasicConstant : public Constant, public QTextEdit
{
public:

    enum Type{
        INT,
        DOUBLE
    };

    BasicConstant(AutonomousGuiObject *parent, Location location, Type type);
    std::string getValue();
private:
    Type type;
};

#endif // BASICCONSTANT_H
