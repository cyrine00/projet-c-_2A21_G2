#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commande.h"

#include <QIntValidator>
#include <QString>
#include <QPixmap>
#include<QMessageBox>
#include <QtDebug>
#include <QTableWidget>
#include <QDate>
#include <QSystemTrayIcon>
#include <QtPrintSupport/QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextEdit>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/ASUS/Desktop/LES diagrammes/qt_pic.jpg");
   int  w=ui->label_pic->width();
   int  h=ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->le_cincl->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_cinemp->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_cinclsup->setValidator(new QIntValidator(0, 99999999, this));
    ui->tab_commande->setModel(C.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int cin_cl=ui->le_cincl->text().toInt();
     int cin_emp=ui->le_cinemp->text().toInt();
     int num_commande=ui->le_numcomm->text().toInt();
     QString formule=ui->le_form->text();
      QDate date_com=ui->la_date->date();

    Commande C (num_commande,formule,cin_emp,cin_cl,date_com);
    bool test=C.ajouter();

   if(test)
    {
       ui->tab_commande->setModel(C.afficher());

       /*

      QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("ajout non effectué\n"),QMessageBox::Cancel);
    }
    else
    {
     QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("ajout effectué\n"),QMessageBox::Cancel);*/

     QMessageBox::information(this,QObject::tr("ok"),QObject::tr("ajout effectué\n"),QMessageBox::Cancel);
      ui->le_form->setText("");
       ui->le_cincl->setText("");
        ui->le_cinemp->setText("");
          ui->le_numcomm->setText("");

    }

}

void MainWindow::on_pb_supprimer_clicked()
{

    C1.setcin_cl(ui->le_cinclsup->text().toInt());
    bool test=C1.supprimer(C1.getcin_cl());
 if(test)
    {
      ui->tab_commande->setModel(C.afficher());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("suppression effetuee .\n"),QMessageBox::Cancel);
        }

        else
 {
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),

                                         QObject::tr("Suppression non effetuee.\n"
                                                     "click Cancel to exit."), QMessageBox::Cancel);
}
}


void MainWindow::on_pb_modifier_clicked()
{
    ui->tab_commande->setModel(C.afficher());

    int num_commande= ui->le_numcomm->text().toInt();
    QString formule=ui->le_form->text();
    int cin_cl=ui->le_cincl->text().toInt();
    int cin_emp= ui->le_cinemp->text().toInt();
     QDate date_com=ui->la_date->date();

        bool test = C.update(num_commande,formule,cin_cl,cin_emp,date_com);
        if (test)
              {
                      ui->tab_commande->setModel(C.afficher());

                  QMessageBox::information(nullptr,QObject::tr("OK"),
                                       QObject::tr("modification établie"),
                                       QMessageBox::Ok);}
              else{
              QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                      QObject::tr("modification non établie"),
                                      QMessageBox::Cancel);}
    }
