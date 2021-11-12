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
/*QString getfidelite();*/
void setCIN(int);
void setage(int);
void setmobile(int);
void setnom(QString);
void setprenom(QString);
void setville(QString);
/*void setnb_visite(int);
void setfidelite(QString);*/

bool ajouter();
QSqlQueryModel * afficher();
bool supprimer(int);
bool modifier();
QSqlQueryModel * rechercher(QString c);
QSqlQueryModel * trie_clnom();
QSqlQueryModel * trie_clage();
QSqlQueryModel * trie_clnbvis();

private:
    int CIN,age,mobile,nb_visite,nb_points;
    QString nom,prenom,ville,fidelite;
};
#endif // CLIENT_H
