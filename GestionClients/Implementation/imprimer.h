#ifndef IMPRIMER_H
#define IMPRIMER_H
#include<client.h>
#include <QDialog>

namespace Ui {
class imprimer;
}

class imprimer : public QDialog
{
    Q_OBJECT

public:
    explicit imprimer(QWidget *parent = nullptr);
    void setclient(Client cl);
    ~imprimer();

private slots:
    void on_pushButton_clicked();

private:
    Ui::imprimer *ui;
};

#endif // IMPRIMER_H
