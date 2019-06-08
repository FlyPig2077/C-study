#include "add.h"
#include "ui_add.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QButtonGroup>
#include <QFile>
#include <QIODevice>
#include <QTextStream>


add::add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add)
{
    ui->setupUi(this);
}

add::~add()
{
    delete ui;
}

void add::on_pbtn_ok_clicked()
{
    QString id=this->ui->le_id->text();
    QString name=this->ui->le_name->text();
    QString phonenum=this->ui->le_phonenum->text();
    QString email=this->ui->le_mail->text();
    QString category=this->ui->cbb_leibie->currentText();
    char sex[10];
    if(ui->rbtn_male->isChecked())
    {
        strcpy(sex,"男");
    }
    else if(ui->rbtn_fmale->isChecked())
    {
        strcpy(sex,"女");
    }
    QString content ="编号:"+id+'\n'+"姓名:"+name +'\n'+"类别:"+category +'\n'+"性别:"+sex +'\n'+"电话号码:"+phonenum+'\n'+"电子邮箱:"+email;//定义一个字符串
    QString cnt=id+" "+name+" "+category+" "+sex+" "+phonenum+" "+email+"\n";


    if(name.length()<1||id.length()<1||phonenum.length()<1||email.length()<1)
    {
        QMessageBox::critical(this,"错误","信息填写不完整,请填写完整信息");
    }
    else
    {
        int ret=QMessageBox::question(this,"确认信息",content,"确认","取消");
        if(ret==0)
        {
            clearUserInterface();
            writeToFile(cnt);
        }

        //qDebug()<<ret;
    }


}

void add::clearUserInterface()
{
    this->ui->le_id->clear();
    this->ui->le_name->clear();
    this->ui->le_phonenum->clear();
    this->ui->le_mail->clear();
    this->ui->rbtn_male->setChecked(true);
    this->ui->cbb_leibie->setCurrentIndex(0);
    this->ui->le_id->setFocus();
}

void add:: writeToFile(QString cnt)
{
    QFile file("information.txt");
    if(!file.open(QIODevice::Append | QIODevice::Text)) //以文本的形式写入Text
    {
        QMessageBox::critical(this,"错误","文件打开失败，信息没有保存！","确定");
        return ;
    }

    QTextStream out(&file);
    out<<cnt;
    file.close();
}

void add::on_pbtn_cancle_clicked()  //点击取消按钮关闭页面
{
    this->close();
}

//自己声明函数关闭函数
//void add::on_pbtn_cancle_pressed()
//{

//}
