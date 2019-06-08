#include "adminmanage.h"
#include "ui_adminmanage.h"
#include <QTimer>
#include <QDateTime>
#include <QStringList>
#include <QCompleter>
#include <stdio.h>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "classnum.h"

QString connectclass;
extern QString user;
extern int num;

QSqlQueryModel *model=new QSqlQueryModel;

adminmanage::adminmanage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminmanage)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeUpdate()));
    timer->start(1000);

}


void adminmanage::timeUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString time_show = time.toString("hh:mm:ss");
    QString date_show = time.toString("yyyy-MM-dd");
    QString week_show= time.toString("dddd");
    this->ui->time1->setText(time_show);
    this->ui->date1->setText(date_show);
    this->ui->week1->setText(week_show);
    this->ui->userid->setText(user);
}


adminmanage::~adminmanage()
{
    delete ui;
}


//注销，修改密码
void adminmanage::on_pbtn_ok_2_clicked()
{
    QSqlQueryModel *model1=new QSqlQueryModel;
    QSqlQuery query;
    QString password=this->ui->le_passwd->text();
    QString confirm=this->ui->le_confirm->text();
    QString sqlPassword="select userPassword from login where userName='"+user+"'";
    model1->setQuery(sqlPassword);
    QModelIndex index1=model1->index(0,0);
    qDebug()<<index1.data();
    qDebug()<<password;
    if(password.length()<1||confirm.length()<1)
    {
        QMessageBox::critical(this,"错误","信息填写不完整，无法注销");
    }
    else if(password!=confirm)
    {
        QMessageBox::critical(this,"错误","前后密码不一致，请重新输入");
        clearUserInterface();
    }
    else if(index1.data()!=password&&password==confirm)
    {
        QMessageBox::critical(this,"错误","密码输入错误，请重新输入");
        clearUserInterface();
    }
    else if(index1.data()==password&&password==confirm)
    {
        int ret=QMessageBox::information(this,"注销","是否注销用户"+user,"确认","取消");
        //删除所有联系人，即删除对应的表
        if(ret==0)
        {
            query.exec("DROP TABLE "+user+"");
        //删除联系人类别表
            query.exec("DROP TABLE "+user+"contactclass""");
        //删除用户表中对应用户的账号和密码
            query.exec("delete from login where userName='"+user+"'");
            QMessageBox::about(this,"提示","该用户已经注销");
            clearUserInterface();
            user="未登录";
            this->close();
        }
        else if(ret==1)
        {
            clearUserInterface();
        }
    }
}

void adminmanage::on_pbtn_cancle_2_clicked()
{
    clearUserInterface();
}

void adminmanage::clearUserInterface()
{
    this->ui->le_passwd->clear();
    this->ui->le_confirm->clear();
    this->ui->le_passwd->setFocus();
}

//修改密码
void adminmanage::on_pbtn_ok_clicked()
{
    QString oldpasswd=this->ui->le_oldpasswd->text();
    QString newpasswd=this->ui->le_newpasswd->text();
    QString confirm=this->ui->le_newconfirm->text();
    QSqlQuery query;
    QSqlQueryModel *model1=new QSqlQueryModel;
    QString sqlPassword="select userPassword from login where userName='"+user+"'";
    model1->setQuery(sqlPassword);
    QModelIndex index1=model1->index(0,0);
    if(index1.data()!=oldpasswd)
    {
        QMessageBox::critical(this,"错误","密码输入错误请重新输入");
        clearUserInterface1();
    }
    else if(index1.data()==oldpasswd&&newpasswd!=confirm)
    {
        QMessageBox::critical(this,"错误","新密码前后输入不一致，请重新输入");
        this->ui->le_newpasswd->clear();
        this->ui->le_newconfirm->clear();
        this->ui->le_newpasswd->setFocus();
    }
    else if(index1.data()==oldpasswd&&newpasswd==oldpasswd)
    {
        QMessageBox::critical(this,"错误","新旧密码不能一致，请重新输入");
        this->ui->le_newpasswd->clear();
        this->ui->le_newconfirm->clear();
        this->ui->le_newpasswd->setFocus();
    }
    else if(newpasswd.length()<6)
    {
        QMessageBox::critical(this,"警告","新密码不可低于6位");
        this->ui->le_newpasswd->clear();
        this->ui->le_newconfirm->clear();
        this->ui->le_newpasswd->setFocus();
    }
    else if(index1.data()==oldpasswd&&newpasswd!=oldpasswd&&newpasswd==confirm&&newpasswd.length()>5)
    {
        int ret=QMessageBox::information(this,"修改密码","是否修改密码","确认","取消");
        if(ret==0)
        {
            //将旧密码改成新密码
            query.exec("update login set userPassword='"+newpasswd+"' where userName='"+user+"'");
            clearUserInterface1();
            QMessageBox::about(this,"提示","密码已经修改,请重新登录");
            this->close();
        }
        else if(ret==1)
        {
            clearUserInterface1();
        }
    }
}

void adminmanage::on_pbtn_cancle_clicked()
{
    clearUserInterface1();
}

void adminmanage::clearUserInterface1()
{
    this->ui->le_oldpasswd->clear();
    this->ui->le_newpasswd->clear();
    this->ui->le_newconfirm->clear();
    this->ui->le_oldpasswd->setFocus();
}

/********************************/
//新建、修改、删除联系人类别的管理

void adminmanage::on_pushButton_2_clicked()  //刷新
{
//    QString classnum2;
//    classnum2="select count(*) from "+user+"contactclass"" ";
//    model->setQuery(classnum2);
//    QModelIndex index4=model->index(0,0);
//    int num1=index4.data().toInt();
//    int classnum=num1+1;
//    QString classnum1=QString::number(classnum);
//    if(this->ui->rbtn_new->isChecked())
//        this->ui->lb_classnum_2->setText(classnum1);
//    else {
//        this->ui->lb_classnum_2->setText("");
//    }
    classnumnew->show();
}

void adminmanage::on_pbtn_classok_clicked()
{
    QString classnum2;
    classnum2="select count(*) from "+user+"contactclass"" ";
    model->setQuery(classnum2);
    QModelIndex index4=model->index(0,0);
    int num1=index4.data().toInt();
    //qDebug()<<num1;
    //新建
    QString nowlabel=this->ui->lb_classnum_2->text();
    connectclass=this->ui->le_connectclass->text();
    QString remarks=this->ui->le_remark->text();
    QSqlQuery query;
    QSqlQueryModel *model2=new QSqlQueryModel;
    //model2->setQuery(connectclass);
    
    //设置新类别的编号
    int classnum=num1+1;
    QString classnum1=QString::number(classnum);
    qDebug()<<connectclass;
    QString checkclass1="select COUNT(*) from "+user+"contactclass"" where className='"+connectclass+"'";
    model2->setQuery(checkclass1);
    QModelIndex index1=model2->index(0,0);
    QString nowlabel1="select count(*) from "+user+"contactclass"" where classNum='"+nowlabel+"'";
    model->setQuery(nowlabel1);
    QModelIndex index3=model->index(0,0);
    if(this->ui->rbtn_new->isChecked())
    {

        qDebug()<<index1.data();//种类名称
        qDebug()<<nowlabel;
        qDebug()<<index3.data();//编号

        if(connectclass==""||nowlabel=="")
            QMessageBox::critical(this,"错误","编号和类别名称不能为空");
        else
        {
            if(index3.data()==0&&index1.data()==0)
            {
                if(index1.data()==0)
                {
                   int ret=QMessageBox::information(this,"添加","确认添加","确定","取消");
                    if(ret==0)
                    {
                        query.exec("insert into "+user+"contactclass"" (classNum,className,remarks) values ('"+nowlabel+"','"+connectclass+"','"+remarks+"')");
                        clearUserInterface2();
                        QMessageBox::information(this,"提示","添加成功");

                    }
                    else if(ret==1)
                    {
                        clearUserInterface2();
                    }
                }

             }
            else if(index1.data()!=0)
            {

                  QMessageBox::critical(this,"错误","已存在该类别","确定");
            }

            else if(index3.data()!=0)
                {
                  QMessageBox::critical(this,"错误","已存在该编号","确定");
                 }
        }




    }
    //修改
    else if(this->ui->rbtn_change->isChecked())
    {
        if(index1.data()==0)
        {
            QMessageBox::critical(this,"错误","该类别不存在，无法进行修改");
        }
        else if(index1.data()!=0)
        {
            int ret1=QMessageBox::information(this,"提示","是否进行修改","是","否");
            if(ret1==0)
            {
                changeclass1->show();
            }
            else if(ret1==1)
            {
                this->ui->le_connectclass->clear();
                this->ui->le_remark->clear();
                this->ui->le_connectclass->setFocus();
            }
        }
    }
    //删除
    else if(this->ui->rbtn_delete->isChecked())
    {
        if(index1.data()==0)//不存在
        {
             QMessageBox::critical(this,"错误","该类别不存在，无法进行删除");
        }
        else if(index1.data()!=0)//存在
        {
            int ret1=QMessageBox::information(this,"提示","是否进行删除","是","否");
            if(ret1==0)
            {
                query.exec("delete from "+user+"contactclass"" where className='"+connectclass+"'");
                this->ui->le_connectclass->clear();
                this->ui->le_remark->clear();
                this->ui->le_connectclass->setFocus();
                QMessageBox::information(this,"提示","删除成功");
            }
            else if(ret1==1)
            {
                this->ui->le_connectclass->clear();
                this->ui->le_remark->clear();
                this->ui->le_connectclass->setFocus();
            }
        }
    }
    else {
        QMessageBox::critical(this,"错误","请选择需要进行的操作");
    }
}

void adminmanage::on_pbtn_cancle_3_clicked()
{
    clearUserInterface2();
}
void adminmanage::clearUserInterface2()
{
    this->ui->le_connectclass->clear();

    this->ui->le_remark->clear();
    this->ui->rbtn_new->setChecked(true);
    this->ui->le_connectclass->setFocus();
}

/********************************/

//类别刷新显示按钮
void adminmanage::on_refresh_clicked()
{
    qDebug()<<num;
    ui->comboBox->clear();
    QStringList strings;
//    int i=1;
    QSqlQuery query("select className from "+user+"contactclass");
    while(query.next()){
        QString x = query.value("className").toString().trimmed();
        this->ui->comboBox->addItem(x);
    }

    //以下为辣鸡代码
//    for (;i<=num;i++) {
//        QString j=QString::number(i,10);  //将int型转化为字符串
//        QString refresh="select className from "+user+"contactclass"" where classNum="+j+"";
//        model->setQuery(refresh);
//        QModelIndex index1=model->index(0,0);
////        if(index1.data()=="朋友")
////            QMessageBox::about(this,"1","朋友");
//        strings<<index1.data().toStringList();
//    }
//    ui->comboBox->addItems(strings);
//    ui->comboBox->setEditable(true);

}
/********************************/



/********************************/

//添加、修改联系人
void adminmanage::on_pbtn_addchange_clicked()
{
    QString connectnum=this->ui->le_connectnum->text();
    QString connectname=this->ui->le_connectname->text();
    QString connectclass=this->ui->comboBox->currentText();
    QString sex=this->ui->comboBox_sex->currentText();
    QString connectphone=this->ui->le_phonenum->text();
    QString connectmail=this->ui->le_connectmail->text();
    QString content="编号:"+connectnum+'\n'+"姓名:"+connectname+'\n'+"类别:"+connectclass+'\n'+"性别:"+sex+'\n'+"电话号码:"+connectphone+'\n'+"电子邮箱:"+connectmail+'\n';


    if(this->ui->rdbn_add->isChecked())//添加
    {

        int ret=QMessageBox::question(this,"确认信息",content,"确认","取消");
        if(ret==0)
        {
            QSqlQuery query;
            bool x=query.exec("insert into "+user+"(contactId,contactName,className,contactSex,contactPhone,contactmail) values('"+connectnum+"','"+connectname+"','"+connectclass+"','"+sex+"','"+connectphone+"','"+connectmail+"')");
            if(x==false)
            {
                QMessageBox::critical(this,"错误","已有此联系人");
            }
            else if(x==true)
            {
                QMessageBox::information(this,"提示","添加联系人成功");
            }
        }

    }
    else if(this->ui->rdbn_change->isChecked())  //修改
    {
        if(connectnum=="")//为空
        {
            QMessageBox::critical(this,"错误","请输入联系人编号");
        }
        else
        {
            int ret=QMessageBox::question(this,"确认信息",content,"确认","取消");
            if(ret==0)
            {
                QSqlQuery query("update "+user+" set contactId='"+connectnum+"',contactName='"+connectname+"',className='"+connectclass+"',contactSex='"+sex+"',contactPhone='"+connectphone+"',contactmail='"+connectmail+"' where contactId='"+connectnum+"'  ");
            }
        }
    }
    else {
        QMessageBox::critical(this,"错误","请选择要进行的操作");
    }

}

void adminmanage::on_pbtn_connectcancle_clicked()
{
    clearUserInterface3();
}

//刷新按钮
void adminmanage::on_refreshnum_clicked()
{
    //根据编号导入联系人信息
    if(this->ui->rdbn_change->isChecked())
    {
    QString connectnum=this->ui->le_connectnum->text();
    QSqlQueryModel *model=new QSqlQueryModel;
    //名字
    QString contactName="select contactName from "+user+" where contactId='"+connectnum+"'";
    model->setQuery(contactName);
    QModelIndex index=model->index(0,0);
    this->ui->le_connectname->setText(index.data().toString());
//    //类别
//    QString connectclass="select className from "+user+" where contactId='"+connectnum+"'";
//    model->setQuery(connectclass);
//    QModelIndex index1=model->index(0,0);
//    this->ui->comboBox->addItem(index1.data().toString());
//    //性别
//    QString sex="select contactSex from "+user+" where contactId='"+connectnum+"'";
//    model->setQuery(sex);
//    QModelIndex index2=model->index(0,0);
//    this->ui->comboBox_sex->addItem(index2.data().toString());
    //电话号码
    QString connectphone="select contactPhone from "+user+" where contactId='"+connectnum+"'";
    model->setQuery(connectphone);
    QModelIndex index3=model->index(0,0);
    this->ui->le_phonenum->setText(index3.data().toString());
    //电子邮箱
    QString connectmail="select contactmail from "+user+" where contactId='"+connectnum+"'";
    model->setQuery(connectmail);
    QModelIndex index4=model->index(0,0);
    this->ui->le_connectmail->setText(index4.data().toString());
    }
}

void adminmanage::clearUserInterface3()
{
    this->ui->le_connectnum->clear();
    this->ui->le_connectname->clear();
    this->ui->le_phonenum->clear();
    this->ui->le_connectmail->clear();
    this->ui->comboBox_sex->setCurrentIndex(0);
    this->ui->rdbn_add->setChecked(true);
    this->ui->comboBox->setCurrentIndex(0);
}

/********************************/

//查询联系人
void adminmanage::on_pbtn_search_clicked()
{
    bool a=this->ui->cb_name->isChecked();
    bool b=this->ui->cb_sex->isChecked();
    bool c=this->ui->cb_class->isChecked();
    qDebug()<<a;
    qDebug()<<b;
    qDebug()<<c;
    QString name=this->ui->le_findname->text();
    QString sex=this->ui->cbb_findsex->currentText();
    QString findclass=this->ui->le_findclass->text();
//    QString x = "select userName as 用户名,userPassword as 密码 from login";

//    model->setQuery(x);
//    this->ui->tableView->setModel(model);
    //1、按姓名进行查询
    if(a==true)
    {
        QString name1="select contactId as '联系人编号',contactName as '联系人姓名',className as '类别名称',contactSex as '联系人性别',contactPhone as '电话号码',contactmail as '电子邮箱' from "+user+" where contactName like '""%"+name+"%""' ";
        model->setQuery(name1);
        this->ui->tableView->setModel(model);
    }
    //2、按性别进行查询
    if(b==true)
    {
        QString sex1="select contactId as '联系人编号',contactName as '联系人姓名',className as '类别名称',contactSex as '联系人性别',contactPhone as '电话号码',contactmail as '电子邮箱' from "+user+" where contactSex='"+sex+"' ";
        model->setQuery(sex1);
        this->ui->tableView->setModel(model);
    }
    //3、按类别进行查询
    if(c==true)
    {
        QString class1="select contactId as '联系人编号',contactName as '联系人姓名',className as '类别名称',contactSex as '联系人性别',contactPhone as '电话号码',contactmail as '电子邮箱' from "+user+" where className like '""%"+findclass+"%""' ";
        model->setQuery(class1);
        this->ui->tableView->setModel(model);
    }


    //4、按姓名、性别查询
    if(a==true&&b==true&&c==false)
    {
        QString group1="select contactId as '联系人编号',contactName as '联系人姓名',className as '类别名称',contactSex as '联系人性别',contactPhone as '电话号码',contactmail as '电子邮箱' from "+user+" where contactName like '""%"+name+"%""' and contactSex='"+sex+"' ";
        model->setQuery(group1);
        this->ui->tableView->setModel(model);
    }
    //5、按姓名、类别进行查询
    if(a==true&&c==true&&b==false)
    {
        QString group2="select contactId as '联系人编号',contactName as '联系人姓名',className as '类别名称',contactSex as '联系人性别',contactPhone as '电话号码',contactmail as '电子邮箱' from "+user+" where contactName like '""%"+name+"%""' and className like '""%"+findclass+"%""' ";
        model->setQuery(group2);
        this->ui->tableView->setModel(model);
    }
    //6、按性别、类别进行查询
    if(b==true&&c==true&&a==false)
    {
        QString group3="select contactId as '联系人编号',contactName as '联系人姓名',className as '类别名称',contactSex as '联系人性别',contactPhone as '电话号码',contactmail as '电子邮箱' from "+user+" where contactSex='"+sex+"' and className like '""%"+findclass+"%""' ";
        model->setQuery(group3);
        this->ui->tableView->setModel(model);
    }
    //7、按姓名、性别、类别进行查询
    if(a==true&&b==true&&c==true)
    {
        QString group4="select contactId as '联系人编号',contactName as '联系人姓名',className as '类别名称',contactSex as '联系人性别',contactPhone as '电话号码',contactmail as '电子邮箱' from "+user+" where contactName like '""%"+name+"%""' and contactSex='"+sex+"' and className like '""%"+findclass+"%""' ";
        model->setQuery(group4);
        this->ui->tableView->setModel(model);
    }
    else if(a==false&&b==false&&c==false)
    {
        QString group5="select contactId as '联系人编号',contactName as '联系人姓名',className as '类别名称',contactSex as '联系人性别',contactPhone as '电话号码',contactmail as '电子邮箱' from "+user+" ";
        model->setQuery(group5);
        this->ui->tableView->setModel(model);
    }
}

/********************************/
//删除联系人
void adminmanage::on_pbtn_delete_clicked()
{
    QSqlQuery query;
    QString deletenum=this->ui->le_delete->text();
    QString deletenum1="select contactName from "+user+" where contactId='"+deletenum+"' ";
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(deletenum1);
    QModelIndex index=model->index(0,0);
    QString a=index.data().toString();
    qDebug()<<a;
    if(deletenum=="")
    {
        QMessageBox::critical(this,"错误","请输入需要删除的联系人编号");
    }
    else
    {

        QString deleteID="select count(*) from "+user+" where contactId='"+deletenum+"'  ";
        model->setQuery(deleteID);
        QModelIndex index1=model->index(0,0);
        if(index1.data()==0)
            QMessageBox::critical(this,"错误","没有此联系人，无法进行删除");
        else
        {
            int ret=QMessageBox::information(this,"提示","是否删除"+a+"用户","确定","取消");
            if(ret==0)
            {


                    query.exec("delete from "+user+" where contactId='"+deletenum+"'");
                    QMessageBox::information(this,"提示","删除联系人成功");

    //            if(x==false)
    //            {
    //                QMessageBox::critical(this,"错误","没有此联系人，无法进行删除");
    //            }
    //            else if(x==true)
    //            {
    //                QMessageBox::information(this,"提示","删除联系人成功");
    //            }
                clearUserInterface4();
            }
            else if(ret==1)
            {
                clearUserInterface4();
            }
        }
    }
}

void adminmanage::on_pbtn_deletecancle_clicked()
{
    clearUserInterface4();
}

void adminmanage::clearUserInterface4()
{
    this->ui->le_delete->clear();
}
/********************************/

//退出登录界面
void adminmanage::on_pushButton_clicked()
{
    clearUserInterface();
    clearUserInterface1();
    clearUserInterface2();
    clearUserInterface3();
    clearUserInterface4();
    this->ui->lb_classnum_2->setText("");
    //this->ui->tableView->clearSpans();
    QString group5="select contactId as '联系人编号',contactName as '联系人姓名',className as '类别名称',contactSex as '联系人性别',contactPhone as '电话号码',contactmail as '电子邮箱' from "+user+" where contactId='""' contactName='""' and contactSex='""' and className ='""'";
    model->setQuery(group5);
    this->ui->tableView->setModel(model);
    this->close();
}


