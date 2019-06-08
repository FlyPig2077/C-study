#ifndef CLASSNUM_H
#define CLASSNUM_H

#include <QDialog>

namespace Ui {
class classnum;
}

class classnum : public QDialog
{
    Q_OBJECT

public:
    explicit classnum(QWidget *parent = nullptr);
    ~classnum();

private slots:
    void on_pushButton_clicked();

private:
    Ui::classnum *ui;
};

#endif // CLASSNUM_H
