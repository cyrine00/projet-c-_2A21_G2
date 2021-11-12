#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parking.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(tmparking.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbconfirme_clicked()
{
    int code = ui->codelin->text().toInt();
           QString nbh= ui->nbh->text();
           QString prix= ui->prix->text();
           int cin_emp = ui->cin_emp->text().toInt();
           int cin_cl = ui->cin_cl->text().toInt();
            parking p(code,nbh,prix,cin_emp,cin_cl);
         bool test=p.ajouter();
         if(test)
       {
       QMessageBox::information(nullptr, QObject::tr("Ajouter un produit"),
                         QObject::tr("Ajoute success.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
       ui->tableView->setModel(tmparking.afficher());
       }
         else
             QMessageBox::critical(nullptr, QObject::tr("Ajouter un produit"),
                         QObject::tr("Erreur !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString val = ui->tableView->model()->data(index).toString() ;
       QSqlQuery qry;
       qry.prepare(" SELECT * from PARKING where code = '"+val+"'");
       int code = ui->codelin->text().toInt();
              QString nbh= ui->nbh->text();
              QString prix= ui->prix->text();
              int cin_emp = ui->cin_emp->text().toInt();
              int cin_cl = ui->cin_cl->text().toInt();
       if (qry.exec())
       {
           while (qry.next()) {
               ui->codelin->setText(qry.value(0).toString()) ;
               ui->nbh->setText(qry.value(1).toString()) ;
               ui->prix->setText(qry.value(2).toString()) ;
               ui->cin_emp->setText(qry.value(3).toString()) ;
               ui->cin_cl->setText(qry.value(4).toString()) ;
              }
              ui->tableView->setModel(tmparking.afficher());
      }
}

void MainWindow::on_pushButton_clicked()
{
    int code = ui->codelin->text().toInt();
           QString nbh= ui->nbh->text();
           QString prix= ui->prix->text();
           int cin_emp = ui->cin_emp->text().toInt();
           int cin_cl = ui->cin_cl->text().toInt();
            parking p(code,nbh,prix,cin_emp,cin_cl);
  bool test=p.modifier();
  if(test)
{
QMessageBox::information(nullptr, QObject::tr("modifier un parking"),
                  QObject::tr("parking modifié.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}
  else
      QMessageBox::critical(nullptr, QObject::tr("modifier un parking"),
                  QObject::tr("Erreur !.\n" "Click Cancel to exit."), QMessageBox::Cancel);
  ui->tableView->setModel(tmparking.afficher());
}

void MainWindow::on_pushButton_2_clicked()
{
    int code = ui->codelin->text().toInt();
    bool test=tmparking.supprimer(code);
    if (test)
    {ui->tableView->setModel(tmparking.afficher());
        QMessageBox::information(nullptr, QObject::tr("supprimer un parking"),
                          QObject::tr("parking supprimé.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
        }
          else
              QMessageBox::critical(nullptr, QObject::tr("Supprimer un parking"),
                          QObject::tr("Erreur !.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

ui->tableView->setModel(tmparking.afficher());

}
