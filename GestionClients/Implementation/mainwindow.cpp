#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"client.h"
#include<QMessageBox>
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QSqlQueryModel>
#include<assert.h>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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

    ui->tab_client->setModel((cl.afficher()));
    int CIN=ui->le_CIN->text().toInt();
    int age=ui->le_age->text().toInt();
    int mobile=ui->le_mobile->text().toInt();
    QString nom=ui->le_nom->text();
     QString prenom=ui->le_prenom->text();
      QString ville=ui->le_ville->text();
Client cl (CIN , age , mobile ,nom, prenom, ville);
bool test=cl.ajouter();
if (test)
/*{

    QMessageBox::critical(nullptr, QObject::tr("not ok "),
                QObject::tr("Echec d'ajout\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
else*/
    ui->tab_client->setModel(cl.afficher()); //refresh
    QMessageBox::information(nullptr, QObject::tr("ok"),
            QObject::tr("Ajout avec succes\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
 ui->tab_client->setModel(cl.afficher());
}

void MainWindow::on_supprimer_pb_clicked()
{

    cl.setCIN(ui->CIN_suppr->text().toInt());
    bool test=cl.supprimer(cl.getCIN());
    QMessageBox msgBox;
    if (test)
      { //refresh
         ui->tab_client->setModel(cl.afficher());
        msgBox.setText("suppresion avec succes");
    }
    else
        msgBox.setText("Echec de suppression");
                msgBox.exec();
}

/*void MainWindow::on_modifier_pb_clicked()
{
    ui->tab_client->setModel(cl.afficher());
    bool test=cl.modifier(ui->tab_client);

    QMessageBox msgBox;
    if (test)
      { ui->tab_client->setModel(cl.afficher());

        msgBox.setText("modification avec succes");
    }
    else
        msgBox.setText("Echec de modification");
                msgBox.exec();
}*/
