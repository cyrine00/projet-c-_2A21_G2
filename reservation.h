#ifndef RESERVATION_H
#define RESERVATION_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include<QTime>
#include<QCheckBox>
#include<QDate>
class Reservation
{
private:
    int code_r,nb_per,nb_table;
    QString type_r,email;
  QDate date  ;
QTime heure_a,heure_d;
/*QCheckBox terrain_f,terrain_b,resto;*/

public:
    Reservation();
    Reservation(int,int,int,QTime,QTime,QString,QString,QDate);
    int getcode_r();
    int getnb_per();
    int getnb_table();
    QTime getheure_a();
    QTime getheure_d();
    QString gettype_r();
    QString getemail();
    QDate getdate();


void setcode_r(int );
void setnb_per(int );
void setnb_table(int);
void setheure_a(QTime);
void setheure_d(QTime);
void settype_r (QString);
void setemail(QString);
void setdate(QDate);






bool ajouter();
QSqlQueryModel* afficher();
bool supprimer(int);
bool modifier();
QSqlQueryModel *afficher_tri_type();
QSqlQueryModel *afficher_tri_heure();
QSqlQueryModel* chercher(QString text);
int calcul_type(int,int);
};

#endif // RESERVATION_H
