#ifndef CONSTANTCONNECTOR_H
#define CONSTANTCONNECTOR_H
#include "connector.h"
class ConstantConnector:public Connector
{
public:
    ConstantConnector(string name, double defaultValue, Connector::Location location);
    void setValue(double value);

private:
    double value;
};

#endif // CONSTANTCONNECTOR_H
