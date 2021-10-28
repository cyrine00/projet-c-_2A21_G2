#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"client.h"
#include<QMessageBox>
#include <QApplication>
#include "connection.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
ui->tab_client->setModel(cl.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on__ajouter_clicked()
{
    int CIN=ui->_CIN->text().toInt();
    int age=ui->_age->text().toInt();
    int mobile=ui->_mobile->text().toInt();
  /* QDate date_naissance=ui->_datenaissance->setDate();*/
    QString nom=ui->_nom->text();
     QString prenom=ui->_prenom->text();
      QString ville=ui->_ville->text();
Client cl (CIN , age , mobile ,/*date_naissance, */nom, prenom, ville);
bool test=cl.ajouter();
QMessageBox msgBox;
if (test)
  {  msgBox.setText("Ajout avec succes");
    ui->tab_client->setModel(cl.afficher());
}
else
    msgBox.setText("Echec d'ajout");
            msgBox.exec();
}



void MainWindow::on__supprimer_clicked()
{
Client cl1;
/*cl1.setCIN(ui->tab_client->removeColumn());*/
bool test=cl1.supprimer(cl1.getCIN());
QMessageBox msgBox;
if (test)
  {  msgBox.setText("suppresion avec succes");
ui->tab_client->setModel(cl.afficher());
}
else
    msgBox.setText("Echec de suppression");
            msgBox.exec();
}
