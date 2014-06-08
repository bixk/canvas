#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPainter>
#include "qshape.h"
#include <QMouseEvent>
#include <QPushButton>
#include <QMessageBox>
#include <QString>
#include <QList>
#include <QColor>
#include <QPalette>
#include "lineobject.h"
#include "qautonode.h"
#include <QComboBox>
#include "nodeparams.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    TaskNode *curNode;
    TaskNode *lastNode;
    TaskNode *selectedNode;
private:
    Ui::Dialog *ui;
    bool isDrag;
    QPoint curMousePoint;
     QPoint startMousePoint;
    bool shouldLink;
    int objectType;
    QList<TaskNode*> *lst;
     QList<LineObject*> *lineList;
    QString *curBtnName;
    void setUIInfo(TaskNode* node);
    void changeBtnColor(TaskNode *node)
    {
        QString *color=NULL;
        switch (node->nodeType) {
        case 1:
            color=new QString("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color: rgb(255, 74, 19)");

            break;
        case 2:
             color=new QString("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color: rgb(255, 74, 19)");

             break;
        case 3:
             color=new QString("background-color: rgb(33, 224, 255)");

             break;
        case 4:
             color=new QString("background-color: rgb(84, 255, 160) ");

             break;
        case 5:
             color=new QString("background-color:rgb(255, 241, 42)");

             break;
        default:

            return ;
        }
        node->btn->setStyleSheet(*color);
    }

public slots:

    void OnClicked()
    {

        QPushButton *btn=qobject_cast<QPushButton*>(sender());

        this->startMousePoint.setX(btn->x());
         this->startMousePoint.setY(btn->y());
        TaskNode *tmpNode=NULL;
        for(int i=0;i<this->lst->count();++i)
        {
              changeBtnColor(this->lst->at(i));
        }
        for(int i=0;i<this->lst->count();++i)
        {
            if(btn==this->lst->at(i)->btn)
            {
               tmpNode=this->lst->at(i);
                break;
            }

        }
         this->selectedNode=tmpNode;
        tmpNode->btn->setStyleSheet("background-color: rgb(255, 255, 243)");
        if(tmpNode!=NULL)
        {
        this->setUIInfo(tmpNode);
        }

//        if(this->curNode==NULL)
//        {
//            ((Dialog*)this)->curNode=tmpNode;
//        }
//        else
//        {
//            ((Dialog*)this)->lastNode=this->curNode;
//            ((Dialog*)this)->curNode=tmpNode;

//        }
        if(this->shouldLink==true)
        {
                if(this->curNode==NULL&&this->lastNode==NULL)
                {
                    this->curNode=tmpNode;
                    this->lastNode=NULL;
                }
                else if(this->curNode==NULL&&lastNode!=NULL)
                {
                    this->curNode=tmpNode;
                }
                else if(this->curNode!=NULL&&this->lastNode==NULL)
                {
                    this->lastNode=tmpNode;
                }

        }
        if(this->curNode!=NULL&&this->lastNode!=NULL)
        {
             LineObject  *line;
             line=new LineObject(curNode,lastNode);
             this->lineList->append(line);
             this->curNode=NULL;
             this->lastNode=this->curNode;
         }
        repaint();
    }
    void OnPress()
    {


    }
    void OnRelease()
    {
//        QString str;
//        str = "You release THE BUTTON " ;
//        QMessageBox::information(this, tr("Information"), str);
    }

    void on_btnStartMark_clicked();
    void on_btnEndMark_clicked();
    void on_btnAuto_clicked();
    void on_btnManul_clicked();
    void on_btnCondition_clicked();
    void on_btnLine_clicked();
private slots:
    void on_btnSavePrevTask_clicked();
    void on_btnClear_clicked();
    void on_btnSaveNodeDetail_clicked();
    void on_btnSaveNodeSV_clicked();
    void on_btnSavePostSV_clicked();
    void on_btnAddRow_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
};

#endif // DIALOG_H
