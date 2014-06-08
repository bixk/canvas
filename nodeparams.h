#ifndef NODEPARAMS_H
#define NODEPARAMS_H
#include <QString>
class NodeParams
{
public:
    NodeParams();
    QString *bindVarName;
    QString *varName;
    QString *varType;
    QString *varDataType;
};

#endif // NODEPARAMS_H
