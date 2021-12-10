#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parking.h"
#include <QMessageBox>
#include <QDateTime>
#include <QPainter>
#include <QPdfWriter>
 #include <QUrl>
#include<QPdfWriter>
#include<QPainter>
#include<QDesktopServices>
#include<QUrl>
#include <QPrinter>
#include <QFileDialog>
#include<QTextDocument>
#include <QDate>
#include <QSystemTrayIcon>
#include<QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->tableView->setModel(tmparking.afficher());
    ui->tabpartenaire_2->setModel(tmparking.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pbconfirme_clicked()
{srand (time(NULL));
    QDate d = QDate::currentDate() ;
     QString datee =d.toString("dd / MM / yyyy ") ;
     QString fn="ajouter" ;
     parkingh ph("parking",datee,fn);
             ph.ajoutehis();
    int code = ui->codelin->text().toInt();
           QString nbh= ui->nbh->text();
           QString prix= ui->prix->text();
           int cin_emp = ui->cin_emp->text().toInt();
           int cin_cl = ui->cin_cl->text().toInt();
            parking p(code,nbh,prix,cin_emp,cin_cl);
         bool test=p.ajouter();
         if(test)
       {
             erreur->setMedia(QUrl("C:/Users/Mahmoud/Desktop/Atelier_Connexion/sounds/ziw.mp3")) ;
                         erreur->setVolume(100) ;
                         erreur->play() ;

       QMessageBox::information(nullptr, QObject::tr("Ajouter un produit"),
                         QObject::tr("Ajoute success.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
       ui->tableView->setModel(tmparking.afficher());
       }
         else
             erreur->setMedia(QUrl("C:/Users/Mahmoud/Desktop/Atelier_Connexion/sounds/nziw.mp3")) ;
                         erreur->setVolume(100) ;
                         erreur->play() ;


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
      erreur->setMedia(QUrl("C:/Users/Mahmoud/Desktop/Atelier_Connexion/sounds/sup.mp3")) ;
                  erreur->setVolume(100) ;
                  erreur->play() ;
QMessageBox::information(nullptr, QObject::tr("modifier un parking"),
                  QObject::tr("parking modifié.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}
  else
      erreur->setMedia(QUrl("C:/Users/Mahmoud/Desktop/Atelier_Connexion/sounds/nziw.mp3")) ;
                  erreur->setVolume(100) ;
                  erreur->play() ;
      QMessageBox::critical(nullptr, QObject::tr("modifier un parking"),
                  QObject::tr("Erreur !.\n" "Click Cancel to exit."), QMessageBox::Cancel);
  ui->tableView->setModel(tmparking.afficher());
}

void MainWindow::on_pushButton_2_clicked()
{
    int code = ui->codelin->text().toInt();
    bool test=tmparking.supprimer(code);
    if (test)
    {
        erreur->setMedia(QUrl("C:/Users/Mahmoud/Desktop/Atelier_Connexion/sounds/mod.mp3")) ;
                    erreur->setVolume(100) ;
                    erreur->play() ;
        ui->tableView->setModel(tmparking.afficher());
        QMessageBox::information(nullptr, QObject::tr("supprimer un parking"),
                          QObject::tr("parking supprimé.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
        }
          else
        erreur->setMedia(QUrl("C:/Users/Mahmoud/Desktop/Atelier_Connexion/sounds/nziw.mp3")) ;
                    erreur->setVolume(100) ;
                    erreur->play() ;
              QMessageBox::critical(nullptr, QObject::tr("Supprimer un parking"),
                          QObject::tr("Erreur !.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

ui->tableView->setModel(tmparking.afficher());

}

void MainWindow::on_pushButton_3_clicked()
{

    QString str;
    str.append("<html><head></head><body><center>"+QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;;<font size=""10"" color =""red""> GESTION DES PARKING </font><br /> <br /> "));
    str.append("<table border=1><tr>");
    str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">code</font>&nbsp;&nbsp;"+"</td>");
    str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">cin_emp</font>&nbsp;&nbsp;"+"</td>");


    QSqlQuery * query=new QSqlQuery();
    query->exec("SELECT code,cin_emp FROM PARKING");
    while(query->next())
    {
        str.append("<tr><td>");
        str.append("&nbsp;&nbsp;<font color =""green"" size= ""10"">"+query->value(0).toString()+"&nbsp;&nbsp;");
        str.append("</td><td>");
        str.append("&nbsp;&nbsp;<font color =""green""  size=""10"">"+query->value(1).toString()+"&nbsp;&nbsp;");
        str.append("</td><td>");

}

    str.append("</table></center><body></html>");

    QPrinter printer;
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);

    QString path= QFileDialog::getSaveFileName(NULL,"imprimer","gestion des PARKING","PDF(*.pdf");
     if(path.isEmpty()) return;
     printer.setOutputFileName(path);
     QTextDocument doc;
     doc.setHtml(str);
     doc.print(&printer);


}

void MainWindow::on_recherche_clicked()
{
    int code;

        code=ui->codelin->text().toInt();
    bool test= true;
    if(test==(true))
    {
      ui->tableView->setModel(tmparking.rechercher(code));
}
}

void MainWindow::on_pushButton_4_clicked()
{
   ui->tableView->setModel( tmparking.afficher_tri());
}

void MainWindow::on_pbconfirme_2_clicked()
{
    ui->tabpartenaire_2->setModel(tmparking.afficher());

}

void MainWindow::on_pb_ask_clicked()
{
    QString text = ui->le_pb_ask->text();
    if(text=="help")
    {
        erreur->setMedia(QUrl("C:/Users/Mahmoud/Desktop/Atelier_Connexion/sounds/helpaj.mp3")) ;
        erreur->setVolume(100) ;
        erreur->play() ;
    }
        else if(text=="prix parking")
    {
        erreur->setMedia(QUrl("C:/Users/Mahmoud/Desktop/Atelier_Connexion/sounds/prix.mp3")) ;
        erreur->setVolume(100) ;
        erreur->play() ;
    }
        else if(text=="salut")
        {
            erreur->setMedia(QUrl("C:/Users/Mahmoud/Desktop/Atelier_Connexion/sounds/salut.mp3")) ;
            erreur->setVolume(100) ;
            erreur->play() ;
        }
    else
    {
        erreur->setMedia(QUrl("C:/Users/Mahmoud/Desktop/Atelier_Connexion/sounds/helpadmin.mp3")) ;
        erreur->setVolume(100) ;
        erreur->play() ;
    }
}


