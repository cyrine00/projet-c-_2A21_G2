#include "client.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QSqlQueryModel>
#include<QString>
#include<iostream>
#include<QVector>
#include<c++/istream>
using namespace std;

Client::Client()
{
CIN=0; age=0;
nb_visite=0;
mobile=0;
nom=" "; prenom=" ";  fidelite=" "; ville=" ";
}

Client::Client(int CIN,int age,int mobile ,int nb_visite,QString nom, QString prenom,QString ville,QString fidelite)
{
     this->CIN=CIN;
     this->age=age;
     this->mobile=mobile;
     this->nom=nom;
     this->prenom=prenom;
         this->ville=ville;
   this->fidelite=fidelite;
      this->nb_visite=nb_visite;
}

int Client::getCIN(){return CIN;}
int Client::getage(){return age;}
int Client::getmobile(){return mobile;}
int Client::getnb_visite(){return nb_visite;}
QString Client::getnom(){return nom;}
QString Client::getprenom(){return prenom;}
QString Client::getville(){return ville;}
QString Client::getfidelite(){return fidelite;}

void Client::setCIN(int CIN){ this->CIN=CIN;}
void Client::setage(int age){this->age=age;}
void Client::setmobile(int mobile){this->mobile=mobile;}
void Client::setnb_visite(int nb_visite){this->nb_visite=nb_visite;}
void Client::setnom(QString nom){  this->nom=nom;}
void Client::setprenom(QString prenom){this->prenom=prenom;}
void Client::setville(QString ville){ this->ville=ville;}
void Client::setfidelite(QString fidelite){this->fidelite=fidelite;}

bool Client::ajouter()
{
    QString CIN_string=QString::number(CIN);
    QString age_string=QString::number(age);
    QString mobile_string=QString::number(mobile);
       QString nb_visite_string=QString::number(nb_visite);
       QSqlQuery query;
          query.prepare("INSERT INTO CLIENT (CIN, nom, prenom,age,ville,mobile,nb_visite,fidelite) "
                        "VALUES (:CIN, :nom, :prenom, :age, :ville, :mobile, :nb_visite, :fidelite)");
          query.bindValue(0, CIN_string);
          query.bindValue(1, nom);
          query.bindValue(2, prenom);
          query.bindValue(3, age_string);
          query.bindValue(4, ville);
          query.bindValue(5, mobile_string);
          query.bindValue(6, nb_visite_string);
          query.bindValue(7, fidelite);

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
model->setHeaderData(6, Qt::Horizontal, QObject::tr("nb_visite"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("fidelite"));

return model;
}

bool Client::modifier()
{
    QSqlQuery query;
       query.prepare("update CLIENT SET NOM=?,PRENOM=?,AGE=?,VILLE=?,MOBILE=?, NB_VISITE=?, FIDELITE=? where CIN=?");
       query.addBindValue(nom);
       query.addBindValue(prenom);
       query.addBindValue(age);
       query.addBindValue(ville);
       query.addBindValue(mobile);
        query.addBindValue(nb_visite);
        query.addBindValue(fidelite);
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

QSqlQueryModel * Client::rechercher(QString c)
{
    QString CIN_string=QString::number(CIN);
    QString age_string=QString::number(age);
    QString mobile_string=QString::number(mobile);
     QSqlQueryModel *model=new QSqlQueryModel();
      model->setQuery("SELECT * FROM client  WHERE CIN LIKE '%"+c+"%' OR NOM LIKE '%"+c+"%' OR PRENOM LIKE '%"+c+"%' OR AGE LIKE '%"+c+"%' OR VILLE LIKE '%"+c+"%' OR MOBILE LIKE '%"+c+"%' OR NB_VISITE LIKE '%"+c+"%' OR FIDELITE LIKE '%"+c+"%'");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("ville"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("mobile"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("nb_visite"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("fidelite"));

      return model;
}


QSqlQueryModel *Client::trie_clnom()
{
    QSqlQueryModel *model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM Client ORDER BY NOM ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("ville"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("mobile"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("nb_visite"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("fidelite"));


     return model;
}

QSqlQueryModel *Client::trie_clage()
{
    QSqlQueryModel *model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM Client ORDER BY AGE ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("ville"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("mobile"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("nb_visite"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("fidelite"));

     return model;
}

QSqlQueryModel *Client::trie_clnbvis()
{
    QSqlQueryModel *model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM Client ORDER BY NB_VISITE DESC ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("ville"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("mobile"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("nb_visite"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("fidelite"));

     return model;
}

bool  Client::remise_fidelite()
{
    QString CIN_string=QString::number(CIN);
    QString age_string=QString::number(age);
    QString mobile_string=QString::number(mobile);
       QString nb_visite_string=QString::number(nb_visite);
    QSqlQuery query;
                   query.prepare(" INSERT INTO CLIENT (fidelite) WHERE (NB_VISITE>=12 AND CIN=?)  "
                             "VALUES (fidele)");
                   query.bindValue(0, CIN_string);
                   query.bindValue(1, nom);
                   query.bindValue(2, prenom);
                   query.bindValue(3, age_string);
                   query.bindValue(4, ville);
                   query.bindValue(5, mobile_string);
                   query.bindValue(6, nb_visite_string);
                   query.bindValue(7, fidelite);


               return query.exec();
               query.prepare(" INSERT INTO CLIENT (fidelite) WHERE (NB_VISITE<=12)  "
                         "VALUES (pas fidele)");
               query.bindValue(0, CIN_string);
               query.bindValue(1, nom);
               query.bindValue(2, prenom);
               query.bindValue(3, age_string);
               query.bindValue(4, ville);
               query.bindValue(5, mobile_string);
               query.bindValue(6, nb_visite_string);
               query.bindValue(7, fidelite);


           return query.exec();
           /*QSqlQueryModel *model = new QSqlQueryModel;

           model->setQuery("SELECT*  FROM client");
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("ville"));
           model->setHeaderData(5, Qt::Horizontal, QObject::tr("mobile"));
           model->setHeaderData(6, Qt::Horizontal, QObject::tr("nb_visite"));
           model->setHeaderData(7, Qt::Horizontal, QObject::tr("fidelite"));

           return model;*/


if (getfidelite()=="fidele" )
{
    cout <<"client jouit d'un remise de 20%"<<endl;
}

}


/* QVector<Client> clvector;
 for (int i = 0; i < clvector.size(); ++i) {
      if (clvector.at(i).nb_visite >= 5)
         { QSqlQuery query;
          query.prepare("INSERT INTO CLIENT (fidelite) WHERE NB_VISITE>=5
                    "VALUES ("fideeele")");}
  }}*/
/* QSqlQuery q;
int i=0;
q.exec("select nb_visite from client");
while (q.next())
   {
   if (getnb_visite() >= 5)
       {*/
   /*if (getnb_visite() >= 5)
    {
         QSqlQuery query;
        query.prepare("INSERT INTO CLIENT (fidelite) "
                      "VALUES (fideeele)");

       return query.exec();
    }
    else if (getnb_visite()>=10)
    {
         QSqlQuery query;
        query.prepare("INSERT INTO CLIENT (fidelite) "
                      "VALUES (asseeeez fidele)");

       return query.exec();
    }
    else  if (getnb_visite()>=15)
    {
         QSqlQuery query;
        query.prepare("INSERT INTO CLIENT (fidelite) "
                      "VALUES (treees fidele)");

       return query.exec();
    }

}*/



void Client::statistique(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery q;
    int i=0;
    q.exec("select Age from client");
    while (q.next())
    {
        QString identifiant = q.value(0).toString();
       /* QString identifiant1 = q.value(1).toString();
        QString identifiant2 = q.value(2).toString();///********///*/

        i++;
        *ticks<<i;
        *labels <<identifiant/*<<identifiant1<<identifiant2*/;
    }
}


