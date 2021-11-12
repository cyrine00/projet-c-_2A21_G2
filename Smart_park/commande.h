#ifndef COMMANDE_H
#define COMMANDE_H
#include <QDialog>
#include <QString>
#include <QSqlQueryModel>
#include <QDate>
namespace Ui
{
class Commande;
}

class Commande : public QDialog
{
    Q_OBJECT

public:
    //explicit Commande(QWidget *parent = nullptr);
    Commande();
    Commande(int , QString ,int ,int,QDate);
    int getnum_commande();
    QString getformule();
    int getcin_emp();
    int getcin_cl();
    QDate getdate_com();
    void setnum_commande(int);
    void setformule(QString);
    void setcin_emp(int);
    void setcin_cl(int);
    void setdate_com(QDate);
    bool ajouter();
     QSqlQueryModel* afficher();
     bool supprimer (int);
     bool update(int , QString ,int ,int,QDate);

private slots:

    void on_pb_ajouter_clicked();

private:
    Ui::Commande *ui;
    int num_commande;
    QString formule;
    int cin_emp,cin_cl;
    QDate date_com ;


};

#endif // COMMANDE_H
