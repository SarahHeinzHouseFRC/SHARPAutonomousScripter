#include "constantconnector.h"

ConstantConnector::ConstantConnector(string name, double defaultValue, Location location)
    :Connector(name, location)
{
    //this->required = required;
    this->value = defaultValue;


}

void ConstantConnector::setValue(double value)
{
    this->value = value;
}
