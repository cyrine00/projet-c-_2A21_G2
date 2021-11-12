#include "commande.h"
#include <QSqlQuery>
#include<QtDebug>
#include <QObject>
#include<QString>
#include <QSqlQueryModel>
Commande ::Commande()
{
    num_commande=0;
       formule="";
        cin_emp=0;
         cin_cl=0;

}
/*Commande::Commande(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Commande)
{
    ui->setupUi(this);
}*/
Commande::Commande (int num_commande, QString formule , int cin_emp , int cin_cl , QDate date_com )
{

    this->num_commande=num_commande;
    this->formule=formule;
    this->cin_emp=cin_emp;
    this->cin_cl=cin_cl;
    this->date_com=date_com;


}
int Commande::getnum_commande(){return num_commande;}
QString Commande:: getformule(){return formule;}
int  Commande:: getcin_emp() {return cin_emp;}
int  Commande:: getcin_cl(){return cin_cl;}
QDate Commande::getdate_com(){return date_com;}
void Commande:: setnum_commande(int num_commande){this->num_commande=num_commande;}
void Commande:: setformule(QString formule){this->formule=formule;}
void Commande:: setcin_emp(int cin_emp){ this ->cin_emp=cin_emp;}
void Commande:: setcin_cl(int cin_cl){this->cin_cl=cin_cl;}
void Commande:: setdate_com(QDate date_com){this->date_com=date_com;}

bool Commande :: ajouter()
{
   // bool test=false;
        QSqlQuery query;
        QString cin_cl_string= QString::number(cin_cl);
        QString cin_emp_string= QString::number(cin_emp);
         QString num_commande_string= QString::number(num_commande);

              query.prepare("INSERT INTO commande (cin_cl, cin_emp,num_commande,formule,date_com ) VALUES (:cin_cl, :cin_emp, :num_commande, :formule ,:date_com)");
              query.bindValue(":cin_cl", cin_cl_string);
              query.bindValue(":cin_emp", cin_emp_string);
              query.bindValue(":num_commande", num_commande);
              query.bindValue(":formule", formule);
              query.bindValue(":num_commande", num_commande);
              query.bindValue(":formule", formule);
              query.bindValue(":date_com", date_com);
            return query.exec();



     //  return test;
}
bool Commande::supprimer(int cin_cl)
{
    QSqlQuery query;
    QString cin_cl_string= QString::number(cin_cl);
        query.prepare("delete from commande where cin_cl=:cin_cl");
      query.bindValue(":cin_cl", cin_cl);
    return query.exec();

}
QSqlQueryModel* Commande::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
             model->setQuery("SELECT* FROM commande");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("Numero commande "));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("Forumle"));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("CIN employe"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN client"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date Commande"));



    return model;
}
bool Commande::update(int num_commande, QString formule,int cin_cl,int cin_emp,QDate date_com)
{
    QSqlQuery query;
    query.prepare("UPDATE commande SET num_commande= :num_commande,formule=:formule,cin_cl=:cin_cl,cin_emp=:cin_emp,, date_com=:date_com  WHERE cin_cl =:cin_cl");
    query.bindValue(":num_commande", num_commande);
    query.bindValue(":formule", formule);
    query.bindValue(":cin_cl", cin_cl);
    query.bindValue(":cin_emp", cin_emp);
    query.bindValue(":date_com", date_com);

    return    query.exec();
}

