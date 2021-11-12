#ifndef PARKING_H
#define PARKING_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
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
private:
    int code,cin_emp,cin_cl;
    QString nbh,prix;

};

#endif // PARKING_H
