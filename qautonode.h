#ifndef QAUTONODE_H
#define QAUTONODE_H

#include "qshape.h"
#include "taskinfo.h"
#include <QPushButton>
#include "nodeparams.h"
class TaskNode
{
public:
     QPushButton *btn;
     int nodeType;
     TaskInfo *prevTask;
     TaskInfo *majorTask;
     TaskInfo *postTask;
     QString *params;
     QList<NodeParams*> *paramList;
    TaskNode(QPushButton *btn,int nodeType)
    {
        this->btn=btn;
        this->nodeType=nodeType;
        this->paramList=new QList<NodeParams*>();
    }
    QString* toParamsString()
    {
//        <parameters>
//            <param var="" bingVar="" dataType="" type=""/>
//            <param var="" bingVar="" dataType="" type=""/>
//            <param var="" bingVar="" dataType="" type=""/>
//            <param var="" bingVar="" dataType="" type=""/>
//        </parameters>
        QString *parameters=new QString();
         QString *tmp=new QString("<param var=\":VAR\" bingVar=\":BINDVAR\" dataType=\":DATATYPE\" type=\":TYPE\"/> ");
         for(int i=0;i<paramList->count();++i)
         {
            QString *t=new QString(*tmp);
            t->replace(":VAR",*(paramList->at(i)->bindVarName));
            t->replace(":BINDVAR",*(paramList->at(i)->bindVarName));
            t->replace(":DATATYPE",*(paramList->at(i)->bindVarName));
            t->replace(":TYPE",*(paramList->at(i)->bindVarName));
         }
    }

    TaskNode()
    {

    }
    void setPrevTask(TaskInfo *task)
    {
        this->prevTask=task;
    }
    void setMajorTask(TaskInfo *task)
    {
        this->majorTask=task;
    }
    void setPostTask(TaskInfo *task)
    {
        this->postTask=task;
    }
    void setParams(QString *params)
    {
        this->params=params;
    }


private:

};

#endif // QAUTONODE_H
