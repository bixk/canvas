#ifndef LINEOBJECT_H
#define LINEOBJECT_H
#include "QPushButton"
#include <QLineF>
#include <QPainter>
#include "qautonode.h"
class LineObject
{
public:
    LineObject();
    LineObject(TaskNode *begin,TaskNode *end)
    {
        this->_begin=begin;
        this->_end=end;
    }
    bool isExist(TaskNode *begin,TaskNode *end)
    {
        if(begin==this->_begin&&end==this->_end)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void doDraw(QPainter &painter)
    {
        if(this->_begin!=0||this->_end!=0)
        {
           int x=this->_begin->btn->x();
           int w=this->_begin->btn->width()/2;
           int x1=x+w;
           int y1=this->_begin->btn->y()+this->_begin->btn->height()/2;

           int x2=this->_end->btn->x()+this->_end->btn->width()/2;
           int y2=this->_end->btn->y()+this->_end->btn->height()/2;
           QLineF *line=new QLineF(x1,y1,x2,y2);
           painter.drawLine(*line);
        }
    }

private:
    TaskNode* _begin;
    TaskNode* _end;
};

#endif // LINEOBJECT_H
