#ifndef TASKINFO_H
#define TASKINFO_H
#include <QString>
class TaskInfo
{
public:
    TaskInfo();
    TaskInfo(QString *taskSV,QString *taskMechod,QString *params)
    {
        this->params=params;
        this->taskMechod=taskMechod;
        this->taskSV=taskSV;
    }
    QString *taskSV;
    QString *taskMechod;
    QString *params;
private:

};

#endif // TASKINFO_H
