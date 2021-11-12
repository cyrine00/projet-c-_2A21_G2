#include "parking.h"
#include "connection.h"
parking::parking()
{
code=0;
nbh="";
prix="";
cin_emp=0;
cin_cl=0;
}
parking::parking(int code,QString nbh,QString prix,int cin_emp,int cin_cl)
{
  this->code=code;
  this->nbh=nbh;
  this->prix=prix;
  this->cin_emp=cin_emp;
  this->cin_cl = cin_cl;
}
int parking::get_code(){return  code;}
QString parking::get_nbh(){return  nbh;}
QString parking::get_prix(){return prix;}
int parking::get_cin_emp(){return cin_emp;}
int parking::get_cin_cl(){return cin_cl;}

bool parking::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(code);
    query.prepare("INSERT INTO PARKING (code, nobre_heure, prix, cin_emp,cin_cl) "
                        "VALUES (:code, :nbh, :prix, :cin_emp,:cin_cl)");
    query.bindValue(":code", res);
    query.bindValue(":nbh", nbh);
    query.bindValue(":prix", prix);
    query.bindValue(":cin_emp", cin_emp);
    query.bindValue(":cin_cl", cin_cl);
    return    query.exec();
}

bool parking::modifier()

{
    QSqlQuery query;
    QString res= QString::number(code);
     QString cin_emp1= QString::number(cin_emp);
      QString cin_cl2= QString::number(cin_cl);
    query.prepare("UPDATE PARKING SET nobre_heure='"+nbh+"',prix='"+prix+"',cin_emp='"+cin_emp1+"',cin_cl='"+cin_cl2+"' where code='"+res+"'  ;");
    query.bindValue(":code",code);
    query.bindValue(":nobre_heure", nbh);
    query.bindValue(":prix", prix);
    query.bindValue(":cin_emp", cin_emp1);
    query.bindValue(":cin_cl", cin_cl2);
    return    query.exec();
}

QSqlQueryModel * parking::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from PARKING order by code asc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nobre_heure "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin_emp"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("cin_cl"));

    return model;
}


bool parking::supprimer(int icode)
{
QSqlQuery query;
QString res= QString::number(icode);
query.prepare("Delete from PARKING where code = :code ");
query.bindValue(":code", res);
return    query.exec();
}

QSqlQueryModel * parking::tri()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from PARKING order by code asc;");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nobre_heure "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin_emp"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("cin_cl"));
        return model;
}

