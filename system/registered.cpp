#include "registered.h"
#include "ui_registered.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>

QString user1;

registered::registered(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registered)
{
    ui->setupUi(this);
}

registered::~registered()
{
    delete ui;
}

void registered::on_pbtn2_clicked()
{
    this->close();
    clearUserInterface();
}

void registered::on_pbtn1_clicked()
{
    QString sql1;
    QString userName=this->ui->le_name->text();
    user1=userName;
    QString userPassword=this->ui->le_password1->text();
    QString confirmpassword=this->ui->le_password2->text();
    QSqlQueryModel *model=new QSqlQueryModel;
    QString sqlName,sqlPassword;
    sqlName="select count(*) from login where userName='"+userName+"'";
    model->setQuery(sqlName);
    QModelIndex index1=model->index(0,0);

    if(userName.length()<1||userPassword.length()<1)
    {
        QMessageBox::critical(this,"错误","信息填写不完整，请重新填写账号信息！");
        clearUserInterface();
    }
    else if(index1.data()!=0)
    {
        QMessageBox::about(this,"提示","用户名已存在，请重新输入");
        clearUserInterface();
    }
    else if (index1.data()==0&&userPassword.length()>=6&&userPassword==confirmpassword)
    {
        QSqlQuery query;
        //创建用户表
        bool x = query.exec("create table "+user1+" ( contactId varchar(50) primary key,contactName varchar(50) NOT NULL,className varchar(50) NOT NULL,contactSex varchar(50) NOT NULL,contactPhone varchar(50) NOT NULL,contactmail varchar(50) NOT NULL)");
        query.exec("create table "+user1+"contactclass"" ( classNum INT primary key,className varchar(50) NOT NULL,remarks varchar(50) )");
        //model->setQuery(createtable);


        if(x)
        {
            //QMessageBox::about(this,"提示","表未建立，将为您创建新的表");
            QMessageBox::about(this,"提示","用户注册成功");
            sql1="insert into login(userName,userPassword) values ('"+userName+"','"+userPassword+"')";
            QSqlQueryModel *model1=new QSqlQueryModel;
            model1->setQuery(sql1);
            clearUserInterface();
            this->close();
        }
        else {
            QMessageBox::critical(this,"错误","用户名不能以数字开头");

        }

    }
    else if(userPassword!=confirmpassword)
    {
        QMessageBox::critical(this,"错误","两次输入的密码不同，请重新输入");
        this->ui->le_password1->clear();
        this->ui->le_password2->clear();
        this->ui->le_password1->setFocus();
        clearUserInterface();
    }
    else if(userPassword.length()<6)
    {
        QMessageBox::critical(this,"错误","密码长度不足六位，请重新输入");
        this->ui->le_password1->clear();
        this->ui->le_password2->clear();
        this->ui->le_password1->setFocus();
    }

}
void registered::clearUserInterface()
{
    this->ui->le_name->clear();
    this->ui->le_password1->clear();
    this->ui->le_password2->clear();
    this->ui->le_name->setFocus();
}
