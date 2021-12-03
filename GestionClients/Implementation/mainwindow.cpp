#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"client.h"
#include<QMessageBox>
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QSqlQueryModel>
#include<QIntValidator>
#include <QStackedWidget>
#include<QImage>
#include <QtGui>
#include<QPixmap>
#include<QPrintDialog>
#include<QPrinter>
#include<QPainter>
#include<QRadioButton>
#include<QFile>
#include<QIODevice>
#include<QTextStream>
#include<qcustomplot.h>
#include<avis.h>
#include <QDesktopServices>
#include <QUrl>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_CIN->setValidator(new QIntValidator(0,9999999,this));
     ui->le_mobile->setValidator(new QIntValidator(0,99999999,this));
      ui->le_age->setValidator(new QIntValidator(0,99,this));
    ui->tab_client->setModel(cl.afficher());

    int ret=A.connect_arduino();
    switch(ret)
    {
    case(0):qDebug()<<"arduino is available and connected to : " << A.getarduino_port_name();
        break;
    case(1):qDebug()<<"arduino is available but not connected to : " << A.getarduino_port_name();
        break;
    case(-1):qDebug()<<"arduino is not available : " << A.getarduino_port_name();
    }
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
    int nb_visite=ui->nb_visite->text().toInt();
    QString nom=ui->le_nom->text();
     QString prenom=ui->le_prenom->text();
      QString ville=ui->le_ville->text();
      cl.setCIN(ui->le_CIN->text().toInt());
Client cl (CIN , age , mobile,nb_visite ,nom, prenom, ville);
bool test=cl.ajouter();
if (test)
{

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
      int nb_visite=ui->nb_visite->text().toInt();
    QString nom=ui->le_nom->text();
     QString prenom=ui->le_prenom->text();
      QString ville=ui->le_ville->text();
Client cl (CIN , age , mobile,nb_visite ,nom, prenom, ville);
bool test=cl.modifier ();

    if (test)
      {
         ui->tab_client->setModel(cl.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("modification avec succes\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

 ui->tab_client->setModel(cl.afficher());
        }

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

void MainWindow::on_nbvisite_clicked()
{
    ui->tab_client->setModel(cl.trie_clnbvis());

}

void MainWindow::on_lineEdit_23_textChanged(const QString &arg1) ///recherche
{
    QString ch = arg1;

                    if (ch=="")
                        ui->tab_client->setModel(cl.afficher());
                    else
                      ui->tab_client->setModel(cl.rechercher(ch));                 
}


void MainWindow::on_tab_client_activated(const QModelIndex &index)
{
    QString val=ui->tab_client->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from client where CIN='"+val+"'");
if(qry.exec())
{
    while(qry.next())
{
        ui->le_CIN->setText((qry.value(0).toString()));
        ui->le_nom->setText((qry.value(1).toString()));
        ui->le_prenom->setText((qry.value(2).toString()));
        ui->le_age->setText((qry.value(3).toString()));
        ui->le_ville->setText((qry.value(4).toString()));
        ui->le_mobile->setText((qry.value(5).toString()));
        ui->nb_visite->setText((qry.value(6).toString()));
    }
}
else
{
    QMessageBox::critical(nullptr, QObject::tr("erreur"),
                QObject::tr("Echec de modification\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
}


void MainWindow::on_reset_clicked()
{
    ui->le_CIN->clear();
    ui->le_age->clear();
    ui->le_mobile->clear();
    ui->nb_visite->clear();
    ui->le_nom->clear();
    ui->le_prenom->clear();
    ui->le_ville->clear();
}

void MainWindow::on_imprimer_clicked()
{
    QPrinter  printer;
    printer.setPrinterName("desired printer name");
    QPrintDialog dialog(&printer,this);
    if(dialog.exec() == QDialog::Rejected) return;
    ui->textEdit_2->print(&printer);
    QMessageBox::information(nullptr, QObject::tr("Carte"),
                QObject::tr("Carte imprimé ! \n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tabWidget_2_currentChanged(int index)
{
    // background //
                 QLinearGradient gradient(0, 0, 0, 400);
                 gradient.setColorAt(0, QColor(90, 90, 90));
                 gradient.setColorAt(0.38, QColor(105, 105, 105));
                 gradient.setColorAt(1, QColor(70, 70, 70));
                 ui->plot->setBackground(QBrush(gradient));

                 QCPBars *amande = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
                /* QCPBars *amande1 = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
                 QCPBars *amande2 = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);*/

                 amande->setAntialiased(false);
                 /*amande1->setAntialiased(false);
                 amande2->setAntialiased(false);*/
                 amande->setStackingGap(1);
                 /*amande1->setStackingGap(1);
                 amande2->setStackingGap(1);*/
                  //couleurs
                 /*amande1->setName("Repartition des clients selon VILLE ");
                 amande1->setPen(QPen(QColor(0, 168, 140).lighter(130)));
                 amande1->setBrush(QColor(0, 168, 140));*/
                 amande->setName("Repartition des clients selon AGE");
                 amande->setPen(QPen(QColor(250, 170, 20).lighter(150)));
                 amande->setBrush(QColor(250, 170, 20));
                 /*amande2->setName("Repartition des clients selon NOMBRE DE VISITE");
                 amande2->setPen(QPen(QColor(111, 9, 176).lighter(170)));
                 amande2->setBrush(QColor(111, 9, 176));*/

                 /* // stack bars on top of each other:
                 amande1->moveAbove(amande2);
                 amande->moveAbove(amande1);*/
                  //axe des abscisses
                 QVector<double> ticks;
                 QVector<QString> labels;
                 cl.statistique(&ticks,&labels);

                 QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
                 textTicker->addTicks(ticks, labels);
                 ui->plot->xAxis->setTicker(textTicker);
                 ui->plot->xAxis->setTickLabelRotation(60);
                 ui->plot->xAxis->setSubTicks(false);
                 ui->plot->xAxis->setTickLength(0, 4);
                 ui->plot->xAxis->setRange(0, 8);
                 ui->plot->xAxis->setBasePen(QPen(Qt::white));
                 ui->plot->xAxis->setTickPen(QPen(Qt::white));
                 ui->plot->xAxis->grid()->setVisible(true);
                 ui->plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
                 ui->plot->xAxis->setTickLabelColor(Qt::white);
                 ui->plot->xAxis->setLabelColor(Qt::white);

                 // axe des ordonnées
                 ui->plot->yAxis->setRange(0,10);
                 ui->plot->yAxis->setPadding(5);
                 ui->plot->yAxis->setLabel("Statistique");
                 ui->plot->yAxis->setBasePen(QPen(Qt::white));
                 ui->plot->yAxis->setTickPen(QPen(Qt::white));
                 ui->plot->yAxis->setSubTickPen(QPen(Qt::white));
                 ui->plot->yAxis->grid()->setSubGridVisible(true);
                 ui->plot->yAxis->setTickLabelColor(Qt::white);
                 ui->plot->yAxis->setLabelColor(Qt::white);
                 ui->plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
                 ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

                 // ajout des données  (statistiques selon l'age)//

                 QVector<double> PlaceData,PlaceData1,PlaceData2;
                 QSqlQuery q1("select AGE  from client");
                 while (q1.next()) {
                               int  nbr_fautee = q1.value(0).toInt();
                               PlaceData<< nbr_fautee;
                              /* int  nbr_fautee1 = q1.value(0).toInt();
                               PlaceData1<< nbr_fautee1;
                               int  nbr_fautee2 = q1.value(0).toInt();
                               PlaceData2<< nbr_fautee2;*/

                                 }
                 amande->setData(ticks, PlaceData);
               /*  amande1->setData(ticks, PlaceData1);
                 amande2->setData(ticks, PlaceData2);*/


                 ui->plot->legend->setVisible(true);
                 ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                 ui->plot->legend->setBrush(QColor(255, 255, 255, 100));
                 ui->plot->legend->setBorderPen(Qt::NoPen);
                 QFont legendFont = font();
                 legendFont.setPointSize(5);
                 ui->plot->legend->setFont(legendFont);
                 ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
void MainWindow::on_valider_clicked() ///valider avis
{
    /*QString fname = "C:\\Users\\ASUS\\Desktop\\smart park\\Avis.txt";
    QFile file(fname);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
            QTextStream stream(&file);*/
            QString Acceuil_telephonique = ui->comboBox->currentText();
            QString Amabilite = ui->comboBox_2->currentText();
            QString Disponibilite = ui->comboBox_3->currentText();
            QString Espace_vert = ui->comboBox_4->currentText();
            QString Espace_jeux = ui->comboBox_5->currentText();
            QString Parking = ui->comboBox_6->currentText();
            QString recommandation = ui->comboBox_7->currentText();
            QString revisiter = ui->comboBox_8->currentText();
            QString positif = ui->positif->toPlainText();
            QString negatif = ui->negatif->toPlainText();

       /*  stream << "Acceuil telephonique :" << Acceuil_telephonique << endl;
         stream << "Amabilite :" << Amabilite << endl;
         stream << "Disponibilite :" << Disponibilite << endl;
         stream << "Espace vert :" << Espace_vert << endl;
         stream << "Espace des jeux :" << Espace_des_jeux << endl;
         stream << "Parking :" << Parking << endl;
         stream << "Souhaitez-vous nous recommander aupres d autres ? :" << box << endl;
         stream << "Pensez-vous a nous revisiter ? :" << com << endl;
         stream << "Sur l ensemble de votre manifestation quel a ete le point le plus positif ? :" << positif << endl;
         stream << "Sur l ensemble de votre manifestation quel a ete le point le plus négatif ? :" << negatif << endl;

}
file.close();*/
Avis a (Acceuil_telephonique,Amabilite,Disponibilite,Espace_vert,Espace_jeux,Parking,recommandation,revisiter,positif,negatif);

            bool test=a.ajouter();
            if (test)
            {

                QMessageBox::critical(nullptr, QObject::tr("Avis"),
                            QObject::tr("Avis non enregistré\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
}
            else
                QMessageBox::information(nullptr, QObject::tr("Avis"),
                                QObject::tr("Avis enregistré\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_client_mois_clicked()
{
 ui->tab_client->setModel(cl.client_mois());
}


void MainWindow::on_gifts_clicked()
{
   QString link= "https://wheel-decide.com/prizewheel.html";
   QDesktopServices::openUrl(link);
}
