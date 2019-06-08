#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

//定义全局变量，用户的名称
QString user;
int num;

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
   // connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(close()));
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    QSqlQuery query;
    QString userid=this->ui->le_id->text();
    QString password=this->ui->le_password->text();
    QString sqlName,sqlPassword;
    QSqlQueryModel *model=new QSqlQueryModel;
    sqlName="select count(*) from login where userName='"+userid+"'";
    model->setQuery(sqlName);
    QModelIndex index1=model->index(0,0);
    sqlPassword="select userPassword from login where userName='"+userid+"'";
    model->setQuery(sqlPassword);
    QModelIndex index2=model->index(0,0);
    if(userid.length()<1||password.length()<1)
    {
        QMessageBox::critical(this,"错误","信息填写不完整，请重新填写账号信息！");
    }
    else if(index1.data()==0||index2.data()!=password)
    {
        clearLoginInterface();
        QMessageBox::about(this,"提示","用户名或密码错误！");

    }
    else if(index1.data()!=0&&index2.data()==password)
    {
        QMessageBox::about(this,"提示","登录成功！");
        //QSqlQueryModel *table=new QSqlQueryModel;
        user=this->ui->le_id->text();

        QString table1="select COUNT(*) from sysobjects where name='"+user+"'";
        model->setQuery(table1);
        QModelIndex index3=model->index(0,0);
        //qDebug()<<index3.data();
        //判断对应用户的表是否存在，没有则建立相应的表
        if(index3.data()==1)
        {
            QString classnum;
            classnum="select count(*) from "+user+"contactclass"" ";
            model->setQuery(classnum);
            QModelIndex index4=model->index(0,0);
//            if(index4.data()==3)
//            {
//                qDebug()<<3;
//                num=index4.data().toInt();
//                qDebug()<<index4.data();
//                qDebug()<<num;
//                QMessageBox::about(this,"提示","长度为3");
//            }
            num=index4.data().toInt();
            qDebug()<<index4.data();
            qDebug()<<num;
            //QMessageBox::about(this,"提示","表已经建立");
        }
        else if(index3.data()==0)
        {
            //QString createtable="create table '"+user+"' ( contactId varchar(50) primary key,contactName varchar(50) NOT NULL,className varchar(50) NOT NULL,contactSex varchar(50) NOT NULL,contactPhone varchar(50) NOT NULL,contactmail varchar(50) NOT NULL)";
            //model->setQuery(createtable);
//            QString createtable="CREATE TABLE '"+user+"' ( "
//                                             "contactId varchar(50) NOT NULL,"
//                                             "contactName varchar(50) NOT NULL,"
//                                             "className varchar(50) NOT NULL,"
//                                             "contactSex varchar(50) NOT NULL,"
//                                             "contactPhone varchar(50) NOT NULL,"
//                                             "contactmail varchar(50) NOT NULL);";

        }
        qDebug()<<user;
//        if(a==0)
//        {
//            QString createtable="create table '"+user+" ( contactId varchar(50) NOT NULL,contactName varchar(50) NOT NULL,className varchar(50) NOT NULL,contactSex varchar(50) NOT NULL,contactPhone varchar(50) NOT NULL,contactmail varchar(50) NOT NULL)";
//        }

        this->hide();
        clearLoginInterface();
        adminmanage1->show();
        //if()
//        if(adminmanage1->exec())
//            this->show();
    }
}

void login::on_pushButton_2_clicked()
{
    this->close();
}

void login::clearLoginInterface()
{
    this->ui->le_id->clear();
    this->ui->le_password->clear();
    this->ui->le_id->setFocus();
}
