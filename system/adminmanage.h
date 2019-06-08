#ifndef ADMINMANAGE_H
#define ADMINMANAGE_H

#include <QDialog>
#include <QSqlQuery>
#include "changeclass.h"
#include "classnum.h"
namespace Ui {
class adminmanage;
}

class adminmanage : public QDialog
{
    Q_OBJECT

public:
    explicit adminmanage(QWidget *parent = nullptr);
    ~adminmanage();
    void clearUserInterface();
    void clearUserInterface1();
    void clearUserInterface2();
    void clearUserInterface3();
    void clearUserInterface4();


private slots:
    void timeUpdate();

    void on_pbtn_ok_2_clicked();

    void on_pbtn_cancle_2_clicked();

    void on_pbtn_ok_clicked();

    void on_pbtn_cancle_clicked();

    void on_pbtn_classok_clicked();

    void on_pbtn_cancle_3_clicked();

    void on_refresh_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pbtn_search_clicked();

    void on_pbtn_addchange_clicked();

    void on_pbtn_connectcancle_clicked();

    void on_pbtn_delete_clicked();

    void on_pbtn_deletecancle_clicked();

    void on_refreshnum_clicked();

private:
    Ui::adminmanage *ui;
    changeclass *changeclass1=new changeclass;
    classnum *classnumnew=new classnum;
};

#endif // ADMINMANAGE_H
