#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
        ui->setupUi(this);
        isDrag=false;
        lineList=new QList<LineObject* >();
        lst=new QList<TaskNode* >();
        this->objectType=0;
        this->shouldLink=false;
        this->curNode=NULL;
        this->lastNode=NULL;
        selectedNode=NULL;

        this->ui->btnAuto->setStyleSheet("background-color: rgb(33, 224, 255)");
        this->ui->btnCondition->setStyleSheet("background-color:rgb(255, 241, 42)");
        this->ui->btnManul->setStyleSheet("background-color: rgb(84, 255, 160)");
        this->ui->btnEndMark->setStyleSheet("background-color: rgb(255, 74, 19)");
        this->ui->btnStartMark->setStyleSheet("background-color: rgb(255, 74, 19)");

}

Dialog::~Dialog()
{
    delete ui;
}

 void Dialog::paintEvent(QPaintEvent *)
 {


      QPainter painter(this);
    // if(this->shouldLink==true)
     {

             for(int i=0;i<lineList->count();++i)
             {
                 LineObject *lineInList=this->lineList->at(i);
                 lineInList->doDraw(painter);
             }
                //painter.drawLine(startMousePoint.x(),startMousePoint.y(),curMousePoint.x(),curMousePoint.y());
         }

 }
 void Dialog::mouseMoveEvent(QMouseEvent *e)
 {



       curMousePoint.setX(e->x());
       curMousePoint.setY(e->y());
      //   repaint();


 }

 void Dialog::mousePressEvent(QMouseEvent* e)
 {
     if(e->button()==Qt::LeftButton)
     {
        this->isDrag=true;
     }
     QString *color;
     QString *title;
     switch (this->objectType) {
     case 1:
         color=new QString("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color: rgb(255, 74, 19)");
         title=new QString("开始");
         break;
     case 2:
          color=new QString("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color: rgb(255, 74, 19)");
          title=new QString("结束");
          break;
     case 3:
          color=new QString("background-color: rgb(33, 224, 255)");
          title=new QString("自动");
          break;
     case 4:
          color=new QString("background-color: rgb(84, 255, 160) ");
          title=new QString("人工");
          break;
     case 5:
          color=new QString("background-color:rgb(255, 241, 42)");
          title=new QString("条件");
          break;
     default:
         QMessageBox::information(this, tr("Information"), "请选择节点类型");
         return ;
     }

        QPushButton *btn=new QPushButton(this);
        title->append(QString(":%1").arg(this->lst->count(),this->objectType));
        btn->setText(*title);
        btn->setGeometry(QRect(e->x()-50, e->y()-10, 100, 20));

         btn->setStyleSheet(*color);
        btn->show();
        btn->setObjectName(QString("btn%1").arg(this->lst->count()));
        connect(btn, SIGNAL(clicked()), this, SLOT(OnClicked()));
        connect(btn,SIGNAL(pressed()),this,SLOT(OnPress()));
        connect(btn,SIGNAL(released()),this,SLOT(OnRelease()));
        TaskNode *node=new TaskNode(btn,this->objectType);
        node->params=NULL;
        node->postTask=NULL;
        node->prevTask=NULL;
        node->majorTask=NULL;
        this->lst->append(node);
        //this->ui->txtLog->setText(QString(":%1").arg(this->lst->count()));
 }

 void Dialog::mouseReleaseEvent(QMouseEvent *e)
 {
    this->isDrag=false;
    e->x();
 }



void Dialog::on_btnStartMark_clicked()
{
    this->objectType=1;
}


void Dialog::on_btnEndMark_clicked()
{
   this->objectType=2;
}

void Dialog::on_btnAuto_clicked()
{
    this->objectType=3;
}

void Dialog::on_btnManul_clicked()
{
    this->objectType=4;
}

void Dialog::on_btnCondition_clicked()
{
    this->objectType=5;
}

void Dialog::on_btnLine_clicked()
{
    this->objectType=6;
    if(this->shouldLink==true)
    {
        this->shouldLink=false;
         this->ui->btnLine->setText(QString("连线[%1]").arg(this->lineList->count()));

    }
    else
    {
        this->shouldLink=true;
        ;
         this->ui->btnLine->setText(QString("取消连线[%1]").arg(this->lineList->count()));

    }
    this->curNode=NULL;
    this->lastNode=NULL;
     repaint();
    // repaint();
}

void Dialog::on_btnSavePrevTask_clicked()
{
    if(this->selectedNode!=NULL)
    {

        QString *sv=new QString(this->ui->txtPreTaskSV->text());
        QString *func=new QString(this->ui->txtPreTaskFunc->text());
        QString *params=new QString(this->ui->txtPreTaskParams->text());
        TaskInfo *preTaskInfo=new TaskInfo(sv,func,params);


        this->selectedNode->setPrevTask(preTaskInfo);
         QMessageBox::warning(this,"Warnning","前置任务设置完成!");
    }
    else
    {
        QMessageBox::warning(this,"Warnning","Please select a node!");
    }
}
void Dialog::setUIInfo(TaskNode* node)
{
    this->ui->txtPreTaskFunc->setText("");
    this->ui->txtPreTaskParams->setText("");
    this->ui->txtPreTaskSV->setText("");
    if(node!=NULL&&node->prevTask!=NULL)
    {
        if(node->prevTask->taskMechod!=NULL)
        {
        this->ui->txtPreTaskFunc->setText(*(node->prevTask->taskMechod));
        }

        if(node->prevTask->params!=NULL)
        {
             this->ui->txtPreTaskParams->setText(*(node->prevTask->params));
        }

        if(node->prevTask->taskSV!=NULL)
        {
             this->ui->txtPreTaskSV->setText(*(node->prevTask->taskSV));
        }
    }


    this->ui->txtNodeFunc->setText("");
    this->ui->txtNodeParams->setText("");
    this->ui->txtNodeSV->setText("");
    if(node!=NULL&&node->majorTask!=NULL)
    {
        if(node->majorTask->taskMechod!=NULL)
        {
        this->ui->txtNodeFunc->setText(*(node->majorTask->taskMechod));
        }

        if(node->majorTask->params!=NULL)
        {
             this->ui->txtNodeParams->setText(*(node->majorTask->params));
        }

        if(node->majorTask->taskSV!=NULL)
        {
             this->ui->txtNodeSV->setText(*(node->majorTask->taskSV));
        }
    }


    this->ui->txtNodePastTaskFunc->setText("");
    this->ui->txtNodePostTaskParams->setText("");
    this->ui->txtNodePostTaskSV->setText("");

    if(node!=NULL&&node->postTask!=NULL)
    {
        if(node->postTask->taskMechod!=NULL)
        {
        this->ui->txtNodePastTaskFunc->setText(*(node->postTask->taskMechod));
        }

        if(node->postTask->params!=NULL)
        {
             this->ui->txtNodePostTaskParams->setText(*(node->postTask->params));
        }

        if(node->postTask->taskSV!=NULL)
        {
             this->ui->txtNodePostTaskSV->setText(*(node->postTask->taskSV));
        }
    }
    QTableWidget *grid=this->ui->tableWidget;
    int rows=grid->rowCount();
    for(int i=0;i<rows;++i)
    {
        grid->removeRow(0);
    }
    int rowCount=this->selectedNode->paramList->count();
    grid->setRowCount(rowCount);
    for(int i=0;i<rowCount;++i)
    {
        grid->setRowHeight(i,25);
        QComboBox *dataType = new QComboBox();
        dataType->addItem("STRING");
        QComboBox *inOutType = new QComboBox();
        inOutType->addItem("PUBLIC");
        inOutType->addItem("PRIVATE");
        grid->setItem(i,0,new QTableWidgetItem(*(this->selectedNode->paramList->at(i)->varName)));
        grid->setItem(i,1,new QTableWidgetItem(*(this->selectedNode->paramList->at(i)->bindVarName)));
        grid->setCellWidget(i,2,dataType);
        grid->setCellWidget(i,3,inOutType);
    }

}

void Dialog::on_btnClear_clicked()
{
    for(int i=0;i<this->lst->count();++i)
    {
        TaskNode *node=lst->at(i);
        delete node->btn;
        delete node;
    }
    lst->clear();
    for(int i=0;i<this->lineList->count();++i)
    {
        LineObject *line=this->lineList->at(i);
        delete line;
    }
    this->lineList->clear();;
    repaint();

}

void Dialog::on_btnSaveNodeDetail_clicked()
{
    if(this->ui->txtNodeName->text()!=NULL)
    {
        QString *str=new QString(this->ui->txtNodeName->text());
        this->selectedNode->btn->setText(*str);
    }
}

void Dialog::on_btnSaveNodeSV_clicked()
{
    if(this->selectedNode!=NULL)
    {

        QString *sv=new QString(this->ui->txtNodeSV->text());
        QString *func=new QString(this->ui->txtNodeFunc->text());
        QString *params=new QString(this->ui->txtNodeParams->text());
        TaskInfo *taskInfo=new TaskInfo(sv,func,params);

        this->selectedNode->setMajorTask(taskInfo);
         QMessageBox::warning(this,"Warnning","设置完成!");
    }
    else
    {
        QMessageBox::warning(this,"Warnning","Please select a node!");
    }
}

void Dialog::on_btnSavePostSV_clicked()
{
    if(this->selectedNode!=NULL)
    {

        QString *sv=new QString(this->ui->txtNodePostTaskSV->text());
        QString *func=new QString(this->ui->txtNodePastTaskFunc->text());
        QString *params=new QString(this->ui->txtNodePostTaskParams->text());
        TaskInfo *taskInfo=new TaskInfo(sv,func,params);

        this->selectedNode->setPostTask(taskInfo);
         QMessageBox::warning(this,"Warnning","设置完成!");
    }
    else
    {
        QMessageBox::warning(this,"Warnning","Please select a node!");
    }
}

void Dialog::on_btnAddRow_clicked()
{
    QTableWidget *grid=this->ui->tableWidget;

    grid->setRowCount(grid->rowCount()+1);
    grid->setRowHeight(grid->rowCount()-1,25);
    QComboBox *dataType = new QComboBox();
    dataType->addItem("STRING");
    QComboBox *inOutType = new QComboBox();
    inOutType->addItem("PUBLIC");
    inOutType->addItem("PRIVATE");

    grid->setCellWidget(grid->rowCount()-1,2,dataType);
    grid->setCellWidget(grid->rowCount()-1,3,inOutType);
}

void Dialog::on_pushButton_3_clicked()
{
    QTableWidget *grid=this->ui->tableWidget;
    int i = grid->currentRow();
    grid->removeRow(i);
}

void Dialog::on_pushButton_clicked()
{
     QTableWidget *grid=this->ui->tableWidget;
     int rowCount=grid->rowCount();
     for(int i=0;i<rowCount;++i)
     {
        NodeParams *param=new NodeParams();
        param->bindVarName=new QString(grid->item(i,0)->text());
        param->varName=new QString(grid->item(i,1)->text());
        QWidget * widget=grid->cellWidget(i,2);//获得widget
        QComboBox *combox=(QComboBox*)widget;//强制转化为QComboBox
        QString string=combox->currentText();
        param->varDataType=new QString(string);
        widget=grid->cellWidget(i,3);
        combox=(QComboBox*)widget;
        string=combox->currentText();
        param->varType=new QString(string);
        this->selectedNode->paramList->append(param);
     }
      QMessageBox::warning(this,"Warnning","设置完成!");
}
