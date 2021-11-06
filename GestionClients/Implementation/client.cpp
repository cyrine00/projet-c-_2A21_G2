#include "client.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QSqlQueryModel>
#include<QString>

Client::Client()
{
CIN=0; age=0;
/*nb_visite=0;*/
mobile=0;
nom=" "; prenom=" "; /* fidelite=" "*/; ville=" ";
}

Client::Client(int CIN,int age,int mobile ,QString nom, QString prenom,QString ville)
{
     this->CIN=CIN;
     this->age=age;
     this->mobile=mobile;
     this->nom=nom;
     this->prenom=prenom;
         this->ville=ville;
  /* this->fidelite=fidelite;
      this->nb_visite=nb_visite;*/


}
int Client::getCIN(){return CIN;}
int Client::getage(){return age;}
int Client::getmobile(){return mobile;}
QString Client::getnom(){return nom;}
QString Client::getprenom(){return prenom;}
QString Client::getville(){return ville;}


void Client::setCIN(int CIN){ this->CIN=CIN;}
void Client::setage(int age){this->age=age;}
void Client::setmobile(int mobile){this->mobile=mobile;}
void Client::setnom(QString nom){  this->nom=nom;}
void Client::setprenom(QString prenom){this->prenom=prenom;}
void Client::setville(QString ville){ this->ville=ville;}

bool Client::ajouter()
{
    QString CIN_string=QString::number(CIN);
    QString age_string=QString::number(age);
    QString mobile_string=QString::number(mobile);
       QSqlQuery query;
          query.prepare("INSERT INTO CLIENT (CIN, nom, prenom,age,ville,mobile) "
                        "VALUES (:CIN, :nom, :prenom, :age, :ville, :mobile)");
          query.bindValue(0, CIN_string);
          query.bindValue(1, nom);
          query.bindValue(2, prenom);
          query.bindValue(3, age_string);
          query.bindValue(4, ville);
          query.bindValue(5, mobile_string);
         return query.exec();
}



QSqlQueryModel * Client::afficher()
{
QSqlQueryModel *model = new QSqlQueryModel;

model->setQuery("SELECT*  FROM client");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ville"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("mobile"));

return model;
}

bool Client::modifier()
{
    QSqlQuery query;
       query.prepare("update CLIENT SET NOM=?,PRENOM=?,AGE=?,VILLE=?,MOBILE=? where CIN=?");
       query.addBindValue(nom);
       query.addBindValue(prenom);
       query.addBindValue(age);
       query.addBindValue(ville);
       query.addBindValue(mobile);
       query.addBindValue(CIN);
      return query.exec();

}
bool Client::supprimer(int CIN)
{

    QSqlQuery query;
       query.prepare("Delete from client where CIN=:CIN ");
       query.bindValue(0, CIN);
      return query.exec();
}
