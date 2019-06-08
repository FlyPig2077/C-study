#ifndef CHANGECLASS_H
#define CHANGECLASS_H

#include <QDialog>

namespace Ui {
class changeclass;
}

class changeclass : public QDialog
{
    Q_OBJECT

public:
    explicit changeclass(QWidget *parent = nullptr);
    ~changeclass();

private slots:
    void on_pbtn_yes_clicked();

    void on_pbtn_no_clicked();
    void clearUserInterface();

private:
    Ui::changeclass *ui;
};

#endif // CHANGECLASS_H
