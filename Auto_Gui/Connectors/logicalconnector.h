#ifndef LOGICALCONNECTOR_H
#define LOGICALCONNECTOR_H
#include <Objects/connector.h>

class LogicalConnector : public Connector
{
public:
    LogicalConnector(string name, Connector::Location location);
};

#endif // LOGICALCONNECTOR_H
