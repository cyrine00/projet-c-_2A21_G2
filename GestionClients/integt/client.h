#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include<QVector>

class Client
{
public:
    Client();
    Client(int,int,int,int,int,QString,QString,QString);
    int getCIN();
    int getage();
    int getmobile();
    int  getnb_visite();
    int getcodep();
    QString getnom();
    QString getprenom();
    QString getville();
    void setCIN(int);
    void setage(int);
    void setmobile(int);
    void setnom(QString);
    void setprenom(QString);
    void setville(QString);
    void setnb_visite(int);
    void setcodep(int);

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * rechercher(QString c);
    QSqlQueryModel * trie_clnom();
    QSqlQueryModel * trie_clage();
    QSqlQueryModel * trie_clnbvis();
    void statistique(QVector<double>* ticks,QVector<QString> *labels);
    QSqlQueryModel * client_mois();

private:
    int CIN,age,mobile,nb_visite,codep;
    QString nom,prenom,ville;

};
#endif // CLIENT_H
