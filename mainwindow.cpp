#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reservation.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>
#include <QString>
#include <QIntValidator>
#include <QSqlQueryModel>
#include "smtp.h"
#include <QFileDialog>
#include <QTextDocument>
#include <QTextEdit>
#include <QTextStream>
#include <QWidget>
#include <QFile>
#include <QPainter>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QPrintDialog>
#include "QFileDialog"
#include "QDesktopServices"
#include "algorithm"
#include "iostream"
#include "string"
#include "statistiques.h"
#include<QWidget>
#include<QtSvg/QSvgRenderer>
#include<QDirModel>
#include"qrcode.h"
#include<fstream>
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->tab_reservation->setModel(R.afficher());
    connect(ui->sendBtn_2, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn_2, SIGNAL(clicked()), this, SLOT(browse()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pb_ajouter_clicked()
{
    int code_r=ui->code_res->text().toInt();
    int nb_table=ui->num_t->text().toInt();
    int nb_per=ui->num_p->text().toInt();
    QString email=ui->Email->text();
    QDate date=ui->la_date->date();
    QString type_r=ui->type_res->text();
    QTime heure_d=ui->heure_s->time();
    QTime heure_a=ui->heure_e->time();

    R.setcode_r(ui->code_res->text().toInt());
    Reservation R (code_r,nb_per,nb_table,heure_a,heure_d,type_r,email,date);
    bool test=R.ajouter() ;
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Ajout avec succes.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_reservation->setModel(R.afficher());
    }
    else

    {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("Echec d'ajout.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_reservation->setModel(R.afficher());


    }
}

void MainWindow::on_pb_modifier_clicked()
{
    int code_r=ui->code_res->text().toInt();
    int nb_table=ui->num_t->text().toInt();
    int nb_per=ui->num_p->text().toInt();
    QString email=ui->Email->text();
    QDate date=ui->la_date->date();
    QString type_r=ui->type_res->text();
    QTime heure_d=ui->heure_s->time();
    QTime heure_a=ui->heure_e->time();



    Reservation R (code_r,nb_per,nb_table,heure_a,heure_d,type_r,email,date);

    bool test=R.modifier();
    if(test)

    {
        QMessageBox::information(nullptr,QObject::tr("Ok"),
                                 QObject::tr("Modification effectuée\n"
                                             "Click cancel to exit."),QMessageBox::Cancel);
        ui->tab_reservation->setModel(R.afficher());
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                              QObject::tr("Modification non effectuée\n"
                                          "Click cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_tab_reservation_activated(const QModelIndex &index)
{
    QString val=ui->tab_reservation->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT * from reservation where CODE_R='"+val+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {


            ui->code_res->setText(qry.value(0).toString());
            ui->type_res->setText(qry.value(1).toString());
            ui->num_p->setText(qry.value(2).toString());
            ui->la_date->setDate(qry.value(3).toDate());
            ui->num_t->setText(qry.value(4).toString());
            ui->Email->setText(qry.value(5).toString());
            ui->heure_e->setTime(qry.value(6).toTime());
            ui->heure_s->setTime(qry.value(7).toTime());

        }
    }
}

void MainWindow::on_pb_supprimer_2_clicked()
{
    Reservation R;
    R.setcode_r(ui->code_res->text().toInt());
     bool test=R.supprimer(R.getcode_r());
   if (test)
   {

       QMessageBox::information(nullptr,QObject::tr("Ok"),
                            QObject::tr("suppression effectué\n"
                                          "Click cancel to exit."),QMessageBox::Cancel);
       ui->tab_reservation->setModel(R.afficher());

       }
   else
       {
       QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                            QObject::tr("suppression non effectué\n"
                                          "Click cancel to exit."),QMessageBox::Cancel);
       }
}




void MainWindow::on_tri_clicked()
{
    ui->tab_reservation->setModel(R.afficher_tri_type());

}


void MainWindow::on_tri_date_clicked()
{
     ui->tab_reservation->setModel(R.afficher_tri_date());
}


void MainWindow::on_chercher_clicked()
{
    QString choix;
            choix=ui->li_chercher->text();
            QString li_rechercher=ui->li_chercher->text();
            ui->tab_reservation->setModel(R.chercher(li_rechercher));
}



void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file_2->setText( fileListString );

}


void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("malek.bensaid@esprit.tn",ui->mail_pass_2->text(), "smtp.gmail.com");

    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("malek.bensaid@esprit.tn", ui->rcpt_2->text() , ui->subject_2->text(),ui->msg_2->toPlainText(), files );
    else
        smtp->sendMail("malek.bensaid@esprit.tn", ui->rcpt_2->text() , ui->subject_2->text(),ui->msg_2->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt_2->clear();
    ui->subject_2->clear();
    ui->file_2->clear();
    ui->msg_2->clear();
    ui->mail_pass_2->clear();
}






void MainWindow::on_pushButton_3_clicked()
{
    statistiques *s=new statistiques();
        s->show();
}

void MainWindow::on_qr_clicked()
{
    if(ui->tab_reservation->currentIndex().row()==-1)
                   QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                            QObject::tr("Veuillez Choisir un animal du Tableau.\n"
                                                        "Click Ok to exit."), QMessageBox::Ok);
               else
               {

                    int id=ui->tab_reservation->model()->data(ui->tab_reservation->model()->index(ui->tab_reservation->currentIndex().row(),0)).toInt();
                    const QrCode qr = QrCode::encodeText(std::to_string(id).c_str(), QrCode::Ecc::LOW);
                    std::ofstream myfile;
                    myfile.open ("qrcode.svg") ;
                    myfile << qr.toSvgString(1);
                    myfile.close();
                    QSvgRenderer svgRenderer(QString("qrcode.svg"));
                    QPixmap pix( QSize(90, 90) );
                    QPainter pixPainter( &pix );
                    svgRenderer.render( &pixPainter );
                    ui->QRCODE_3->setPixmap(pix);
               }
    }


