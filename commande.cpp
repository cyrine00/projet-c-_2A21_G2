#include "commande.h"
#include <QSqlQuery>
#include<QtDebug>
#include <QObject>
#include<QString>
#include <QSqlQueryModel>
#include<QPdfWriter>
#include<QMessageBox>
#include<QSystemTrayIcon>
#include<QPainter>
#include<QDesktopServices>
#include<QUrl>

Commande ::Commande()
{
    num_commande=0;
    formule="";
    cin_emp=0;
    cin_cl=0;

}
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

    query.prepare("INSERT INTO commande (num_commande,formule,cin_cl, cin_emp,date_com ) VALUES (:num_commande,:formule,:cin_cl,:cin_emp,:date_com)");

    query.bindValue(":num_commande", num_commande);
    query.bindValue(":formule", formule);
    query.bindValue(":cin_cl", cin_cl_string);
    query.bindValue(":cin_emp", cin_emp_string);
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
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num_commande"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Forumle"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr(" CIN employe"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN client"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date Commande"));

    return model;
}
bool Commande::update(int num_commande, QString formule,int cin_cl,int cin_emp,QDate date_com)
{
    QSqlQuery query;
    query.prepare("UPDATE commande SET num_commande=:num_commande,formule=:formule,cin_cl=:cin_cl,cin_emp=:cin_emp,date_com=:date_com WHERE cin_cl=:cin_cl");
    query.bindValue(":num_commande", num_commande);
    query.bindValue(":formule", formule);
    query.bindValue(":cin_cl", cin_cl);
    query.bindValue(":cin_emp", cin_emp);
    query.bindValue(":date_com", date_com);

    return    query.exec();
}
QSqlQueryModel* Commande::rechercher (const QString &aux)

{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from commande where ((num_commande||formule||cin_emp||cin_cl||date_com) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("num_commande"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("formule"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("cin_emp"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin_cl"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_com"));

    return model;

}
QChart* Commande ::chart_bar()
{
    QSqlQuery q1,q2,q3,q4;
    qreal tot=0,c1=0,c2=0,c3=0;

    q1.prepare("SELECT * FROM COMMANDE");
    q1.exec();

    q2.prepare("SELECT * FROM COMMANDE WHERE cin_emp>100 AND cin_emp<300");
    q2.exec();

    q3.prepare("SELECT * FROM COMMANDE WHERE cin_emp>300 AND cin_emp<600");
    q3.exec();

    q4.prepare("SELECT * FROM COMMANDE WHERE cin_emp>600 AND cin_emp<999");
    q4.exec();

    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}

    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;

    //     Assign names to the set of bars used
    QBarSet *set0 = new QBarSet("inf 3");
    QBarSet *set1 = new QBarSet("inf 10");
    QBarSet *set2 = new QBarSet("inf 20");

    //     Assign values for each bar
    *set0 << c1;
    *set1 << c2;
    *set2 << c3;

    //     Add all sets of data to the chart as a whole
    //     1. Bar Chart
    QBarSeries *series = new QBarSeries();

    //     2. Stacked bar chart
    series->append(set0);
    series->append(set1);
    series->append(set2);

    //     Used to define the bar chart to display, title, legend
    QChart *chart = new QChart();

    //     Add the chart
    chart->addSeries(series);

    //     Adds categories to the axes
    //     QBarCategoryAxis *axis = new QBarCategoryAxis();

    //     1. Bar chart
    //     chart->setAxisX(axis, series);

    //    // Used to change the palette
    //    QPalette pal = qApp->palette();

    //    // Change the color around the chart widget and text
    //    pal.setColor(QPalette::Window, QRgb(0xffffff));
    //    pal.setColor(QPalette::WindowText, QRgb(0x404044));

    //     Apply palette changes to the application
    //    qApp->setPalette(pal);

    return chart;
}

QChart* Commande ::chart_pie()
{
    QSqlQuery q1,q2,q3,q4;
    qreal tot=0,c1=0,c2=0,c3=0;


    q1.prepare("SELECT * FROM COMMANDE");
    q1.exec();

    q2.prepare("SELECT * FROM COMMANDE WHERE cin_emp>100 AND cin_emp<300");
    q2.exec();

    q3.prepare("SELECT * FROM COMMANDE WHERE cin_emp>300 AND cin_emp<600");
    q3.exec();

    q4.prepare("SELECT * FROM COMMANDE WHERE cin_emp>600 AND cin_emp<999");
    q4.exec();

    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}

    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;

    //     Define slices and percentage of whole they take up
    QPieSeries *series = new QPieSeries();
    series->append("Employe 1", c1);
    series->append("Employe 2", c2);
    series->append("Employe 3", c3);
    //     Create the chart widget
    QChart *chart = new QChart();

    //     Add data to chart with title and show legend
    chart->addSeries(series);
    chart->legend()->show();

    return chart;

}

