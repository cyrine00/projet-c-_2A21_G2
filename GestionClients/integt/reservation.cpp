#include "reservation.h"
#include "QDate"
#include "QTime"

Reservation::Reservation()
{

    code_r=0; nb_per=0 ; nb_table=0 ;
    type_r=" "; email=" ";
    date=QDate::currentDate();
    heure_a=QTime::currentTime();
    heure_d=QTime::currentTime();

}
Reservation::Reservation(int code_r,int nb_per,int nb_table,QTime heure_a,QTime heure_d,QString type_r,QString email,QDate date)
{this->code_r=code_r;
    this->nb_per=nb_per;
    this->nb_table=nb_table;
    this->type_r=type_r;
    this->email=email;
    this->heure_a=heure_a;
    this->heure_d=heure_d;
    this->date=date;
};
int Reservation::getcode_r(){return code_r; }
int Reservation::getnb_per(){ return nb_per;}
int Reservation::getnb_table(){return nb_table;}

QString Reservation::gettype_r(){return type_r;}
QString Reservation::getemail(){return email;}
QTime Reservation::getheure_a(){return heure_a;}
QDate Reservation::getdate(){return date;}
QTime Reservation::getheure_d(){return heure_d;}


void Reservation::setcode_r(int code_r ){this->code_r=code_r;}
void Reservation::setnb_per(int nb_per){this->nb_per=nb_per;}
void Reservation::setnb_table(int nb_table){this->nb_table=nb_table;}
void Reservation::settype_r (QString type_r){ this->type_r=type_r;}
void Reservation::setemail(QString email){this->email=email;}
void Reservation::setheure_a(QTime heure_a){this->heure_a=heure_a;}
void Reservation::setheure_d(QTime heure_d){this->heure_d=heure_d;}
void Reservation::setdate (QDate date) {this->date=date;}
bool Reservation::ajouter()
{
    QString code_r_string=QString::number(code_r);
    QString nb_per_string=QString::number(nb_per);
    QString nb_table_string=QString::number(nb_table);
    QSqlQuery query;
    query.prepare("INSERT INTO reservation (CODE_R, TYPE_R ,NB_PER ,DATES,NB_TABLE,EMAIL,HEURE_A,HEURE_D ) "
                  "VALUES (:CODE_R, :TYPE_R, :NB_PER, :DATES, :NB_TABLE, :EMAIL, :HEURE_A, :HEURE_D )");
    query.bindValue(0,code_r_string);
    query.bindValue(1,type_r);
    query.bindValue(2,nb_per_string);
    query.bindValue(3,date);
    query.bindValue(4,nb_table_string);
    query.bindValue(5,email);
    query.bindValue(6,heure_a);
    query.bindValue(7,heure_d);
    return  query.exec();
}
QSqlQueryModel* Reservation::afficher(){
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("select * from reservation");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("code_r"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type_r"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nb_per"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("dates "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("nb_table"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("email "));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("heure_a"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("heure_d"));

    return model;
}
bool Reservation::modifier(){
    bool test=false;
    QSqlQuery query;
    QString code_r_string=QString::number(code_r);
    QString nb_per_string=QString::number(nb_per);
    QString nb_table_string=QString::number(nb_table);
    query.prepare("UPDATE reservation SET CODE_R=:CODE_R,TYPE_R=:TYPE_R,NB_PER=:NB_PER,DATES=:DATES,NB_TABLE=:NB_TABLE,EMAIL=:EMAIL,HEURE_A=:HEURE_A,HEURE_D=:HEURE_D WHERE CODE_R=:CODE_R");
    query.bindValue(":CODE_R",code_r_string);
    query.bindValue(":TYPE_R",type_r);
    query.bindValue(":NB_PER",nb_per_string);
    query.bindValue(":DATES",date);
    query.bindValue(":NB_TABLE",nb_table_string);
    query.bindValue(":EMAIL",email);
    query.bindValue(":HEURE_A",heure_a);
    query.bindValue(":HEURE_D",heure_d);
    query.exec();
    test =true;
    return test ;
}
bool Reservation::supprimer(int code){

   QSqlQuery query;
     QString res=QString::number(code);
     query.prepare("Delete from reservation where CODE_R=:CODE_R ");
     query.bindValue(":CODE_R",res); //affectation et association des val
     return query.exec();

}


QSqlQueryModel * Reservation::afficher_tri_type()
{QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from reservation order by TYPE_R asc ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CODE_R"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE_R"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NB_PER"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATES"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NB_TABLE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("HEURE_A"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("HEURE_D"));



    return model;
}

QSqlQueryModel * Reservation::afficher_tri_heure()
{QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from reservation order by DATES asc ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CODE_R"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE_R"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NB_PER"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATES"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NB_TABLE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("HEURE_A"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("HEURE_D"));



    return model;
}


QSqlQueryModel* Reservation::chercher(QString text)
{
QSqlQuery query;
    QSqlQueryModel* model=new QSqlQueryModel();
   {
     query.prepare("SELECT * FROM reservation where CODE_R like '"+text+"'");
     query.exec();
     model->setQuery(query);
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("CODE_R"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE_R"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("NB_PER"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATES"));
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("NB_TABLE"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("EMAIL"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("HEURE_A"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("HEURE_D"));
     }

    return model;

}
int Reservation::calcul_type(int min, int max){
    QSqlQuery query;
    query.prepare("select *from reservation where NB_PER between :min and :max");
    query.bindValue(":min",min);
    query.bindValue(":max",max);
    query.exec();

    int total=0;
    while(query.next()){
        total++;
    }

    return total;
}
