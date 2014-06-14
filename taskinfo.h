#ifndef TASKINFO_H
#define TASKINFO_H
#include <QString>
#include <QFile>
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
    QString* toString()
    {
        QFile *file=new QFile("/Users/bixk/Desktop/template/service.tpl");
        file->open(QIODevice::ReadOnly|QIODevice::Text);
        QString *data =new  QString(file->readAll());
        data->replace(":URI",*taskSV);
        data->replace(":FUNC",*taskMechod);
        data->replace(":PARM",*params);
        return data;
    }

private:

};

#endif // TASKINFO_H
