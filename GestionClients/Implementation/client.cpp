#include "client.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QMessageBox>
#include <QApplication>
#include "connection.h"


Client::Client()
{
CIN=0; age=0;
/*nb_visite=0; nb_points=0;*/
mobile=0;
nom=" "; prenom=" ";  fidelite=" "; ville=" ";
}

Client::Client(int CIN,int age,int mobile ,/*QDate date_naissance,*/QString nom, QString prenom,QString ville)
{
     this->CIN=CIN;
     this->age=age;
     this->mobile=mobile;
    /* this->nb_visite=nb_visite;
     this->nb_points=nb_points;*/
     this->nom=nom;
     this->prenom=prenom;
  /*   this->date_naissance=date_naissance;*/
     /*this->fidelite=fidelite;*/
     this->ville=ville;

}
int Client::getCIN(){return CIN;}
int Client::getage(){return age;}
int Client::getmobile(){return mobile;}
QString Client::getnom(){return nom;}
QString Client::getprenom(){return prenom;}
QString Client::getville(){return ville;}
/*QDate Client::getdate_naissance(){return date_naissance;}*/
/*QString Client::getfidelite(){return fidelite;}*/
void Client::setCIN(int CIN){ this->CIN=CIN;}
void Client::setage(int age){this->age=age;}
void Client::setmobile(int mobile){this->mobile=mobile;}
/*void Client::setnb_visite(int nb_visite){this->nb_visite=nb_visite;}
void Client::setnb_points(int nb_points){ this->nb_points=nb_points;}*/
void Client::setnom(QString nom){  this->nom=nom;}
void Client::setprenom(QString prenom){this->prenom=prenom;}
void Client::setville(QString ville){ this->ville=ville;}
/*void Client::setdate_naissance(QDate date_naissance){ this->date_naissance=date_naissance;}*/
/*void Client::setfidelite(QString fidelite){ this->fidelite=fidelite;}*/

bool Client::ajouter()
{

    QString CIN_string=QString::number(CIN);
    QString age_string=QString::number(age);
    QString mobile_string=QString::number(mobile);
       QSqlQuery query;
          query.prepare("INSERT INTO client (CIN, nom, prenom,age,ville,mobile) "
                        "VALUES (:CIN, :nom, :prenom, :age, :ville, :mobile)");
          query.bindValue(0, CIN_string);
          query.bindValue(1, nom);
          query.bindValue(2, prenom);
          query.bindValue(3, age_string);
          query.bindValue(4, ville);
          query.bindValue(5, mobile_string);
         return query.exec();
}

bool Client::supprimer(int)
{

    QSqlQuery query;
       query.prepare("Delete from client where CIN=:CIN ");
       query.bindValue(0, CIN);
      return query.exec();
}

QSqlQueryModel * Client::afficher()
{
QSqlQueryModel *model = new QSqlQueryModel;
model->setQuery("SELECT*  FROM gestion_cl");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ville"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("mobile"));
}

