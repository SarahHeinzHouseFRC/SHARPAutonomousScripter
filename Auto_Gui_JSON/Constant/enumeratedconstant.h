#ifndef ENUMERATEDCONSTANT_H
#define ENUMERATEDCONSTANT_H
#include <QComboBox>
#include "jsoncpp/json/json.h"

class EnumeratedConstant: public QComboBox
{

struct JsonEnum{
    int index;
    std::string stringName;
};

public:
    EnumeratedConstant(Json::Value enums, QWidget parent);

private:
    Json::Value enums;
};

#endif // ENUMERATEDCONSTANT_H
