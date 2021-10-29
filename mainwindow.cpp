#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include<QMessageBox>
#include<QIntValidator>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>

#include<QTableWidget>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   ui->tab_etud->setModel(E.afficher());
   ui->l_CIN->setValidator(new QIntValidator(0,9999999,this));
ui->tab_etud->setModel(E.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_ajouter_clicked()
{ui->tab_etud->setModel(E.afficher());
   int CIN=ui->l_CIN->text().toInt();
    int salaire=ui->l_salaire->text().toInt();
    int tel=ui->l_tel->text().toInt();
     QString nom=ui->l_nom->text();
     QString prenom=ui->l_prenom->text();
     QString sexe=ui->l_sexe->text();
     QString fonction=ui->l_fonction->text();
     Employe E(nom,prenom,CIN,fonction,salaire,tel,sexe);

bool test=E.ajouter();

if(test)
{
   QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("ajout non effectué\n"),QMessageBox::Cancel);
}
else
{
 QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("ajout effectué\n"),QMessageBox::Cancel);

}
}




void MainWindow::on_button_modifier_clicked()
{ui->tab_etud->setModel(E.afficher());

    bool    test=E.modifierj(ui->l_CIN->text().toInt(),ui->l_nom->text(),ui->l_prenom->text(),ui->l_fonction->text(),ui->l_salaire->text().toInt(),ui->l_sexe->text(),ui->l_tel->text().toInt());

    if (test)
          {
                  ui->tab_etud->setModel(E.afficher());

              QMessageBox::information(nullptr,QObject::tr("OK"),
                                   QObject::tr("modification établie"),
                                   QMessageBox::Ok);}
          else{
          QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                  QObject::tr("modification non établie"),
                                  QMessageBox::Cancel);}
}

void MainWindow::on_supprimer_clicked()
{ ui->tab_etud->setModel(E.afficher());
    bool test=E.supprimer(ui->lineEdit_sup->text().toInt());

    if(test)
    {ui->tab_etud->setModel(E.afficher());//actualisation taa afficher
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("suppression succful .\n"),
                    QMessageBox::Cancel);
        }

        else
            QMessageBox::critical(nullptr,QObject::tr("supprimer not open"),
                                    QObject::tr("click cancel to exist"),
                                    QMessageBox::Cancel);
}
