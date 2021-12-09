#ifndef PARKING_H
#define PARKING_H


#include <QString>
#include <QSqlQuery>
#include <QTimer>
#include <QSqlQueryModel>
#include <QComboBox>

class parking
{
public:
    parking();
    parking(int,QString,QString,int,int);
    int get_code();
    QString get_nbh();
    QString get_prix();
    int get_cin_emp() ;
    int get_cin_cl();

    bool ajouter();
    bool modifier();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    QSqlQueryModel * tri() ;
    QSqlQueryModel * rechercher(int);
    QSqlQueryModel * afficher_tri();
private:
    int code,cin_emp,cin_cl;
    QString nbh,prix;

};
class parkingh
{
public:
       parkingh() ;
       parkingh(QString,QString,QString) ;
       QString get_nom();
       QString get_datee();
       QString get_fn();
       QSqlQueryModel * afficherhis() ;
       bool ajoutehis();
       bool modifierhis() ;
private:

    QString nom,datee,fn ;
};

#endif // PARKING_H
