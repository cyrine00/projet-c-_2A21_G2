#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include <QSqlQuery>
#include<QSqlQueryModel>

class Client
{
public:
    Client();
    Client(int,int,int,QString,QString,QString);
int getCIN();
int getage();
int getmobile();
QString getnom();
QString getprenom();
QString getville();
/*QDate getdate_naissance();*/
/*QString getfidelite();*/
void setCIN(int);
void setage(int);
void setmobile(int);
void setnom(QString);
void setprenom(QString);
void setville(QString);
/*void setdate_naissance(QDate);*/
/*void setnb_visite(int);
void setnb_points(int);
void setfidelite(QString);*/

bool ajouter();
QSqlQueryModel * afficher();
bool supprimer(int);


private:
    int CIN,age,mobile,nb_visite,nb_points;
    QString nom,prenom,ville,fidelite;
};

#endif // CLIENT_H
