#ifndef WFMAKER_H
#define WFMAKER_H
#include <QList>
#include "qautonode.h"
#include "lineobject.h"
#include <QString>
class WFMaker
{
public:
    WFMaker();
    QList<TaskNode*> *lst;
    QList<LineObject*> *lineList;
private:
    QList<QString* > *lines;
    QList<QString* > *nodes;
};

#endif // WFMAKER_H
