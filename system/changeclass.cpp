#include "changeclass.h"
#include "ui_changeclass.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
extern QString user;
extern int num;
extern QString connectclass;
changeclass::changeclass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeclass)
{
    ui->setupUi(this);
}

changeclass::~changeclass()
{
    delete ui;
}

void changeclass::on_pbtn_yes_clicked()
{
    QString newclass=this->ui->le_newclass->text();
    QSqlQuery query;
    QSqlQueryModel *model2=new QSqlQueryModel;
    QString checkclass1="select COUNT(*) from "+user+"contactclass"" where className='"+newclass+"'";
    model2->setQuery(checkclass1);
    QModelIndex index1=model2->index(0,0);
    if(index1.data()==0)
    {
        int ret=QMessageBox::information(this,"提示","是否修改此类别","是","否");
        if(ret==0)
        {
            query.exec("update "+user+"contactclass"" set className='"+newclass+"' where className='"+connectclass+"'");
            QMessageBox::information(this,"提示","修改成功");
            query.exec("update "+user+" set className='"+newclass+"' where className='"+connectclass+"'");
            clearUserInterface();
            this->close();
        }
        else if(ret==1)
        {
            clearUserInterface();
        }
    }
    else if(index1.data()==1)
    {
        QMessageBox::critical(this,"错误","此类别已存在");
        clearUserInterface();
    }
}

void changeclass::on_pbtn_no_clicked()
{
    this->close();
}


void changeclass::clearUserInterface()
{
    this->ui->le_newclass->clear();
    this->ui->le_newclass->setFocus();
}
