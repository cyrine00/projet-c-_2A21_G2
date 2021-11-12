#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"client.h"
#include<QMessageBox>
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QSqlQueryModel>
#include<QIntValidator>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_CIN->setValidator(new QIntValidator(0,9999999,this));
     ui->le_mobile->setValidator(new QIntValidator(0,99999999,this));
      ui->le_age->setValidator(new QIntValidator(0,99,this));
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
      cl.setCIN(ui->le_CIN->text().toInt());
Client cl (CIN , age , mobile ,nom, prenom, ville);
bool test=cl.ajouter();
if (test)
{
  /*  if (CIN==cl.getCIN())
     QMessageBox::warning(this,"Attention","CIN deja existe");

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
}

void MainWindow::on_supprimer_pb_clicked()
{

    cl.setCIN(ui->le_CIN->text().toInt());
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

void MainWindow::on_modifier_pb_clicked()
{

   int CIN=ui->le_CIN->text().toInt();
    int age=ui->le_age->text().toInt();
    int mobile=ui->le_mobile->text().toInt();
    QString nom=ui->le_nom->text();
     QString prenom=ui->le_prenom->text();
      QString ville=ui->le_ville->text();
Client cl (CIN , age , mobile ,nom, prenom, ville);
bool test=cl.modifier ();

    if (test)
      {
         ui->tab_client->setModel(cl.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("modification avec succes\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

 ui->tab_client->setModel(cl.afficher());
        }
       else
     ui->tab_client->setModel(cl.afficher());
        QMessageBox::critical(nullptr, QObject::tr("erreur"),
                    QObject::tr("Echec de modification\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pb_afficher_clicked()
{
    Client cl;
        ui->tab_client->setModel(cl.afficher());
}

void MainWindow::on_ageb_clicked()
{
  ui->tab_client->setModel((cl.trie_clage()));
}

void MainWindow::on_nomb_clicked()
{
  ui->tab_client->setModel(cl.trie_clnom());
}

void MainWindow::on_fidb_clicked()
{
    ui->tab_client->setModel(cl.trie_clnbvis());
}



void MainWindow::on_lineEdit_23_textChanged(const QString &arg1)
{
    QString ch = arg1;

                    if (ch=="")
                        ui->tab_client->setModel(cl.afficher());
                    else
                      ui->tab_client->setModel(cl.rechercher(ch));
}

