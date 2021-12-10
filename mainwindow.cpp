#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPrinter>
#include<QMessageBox>
//#include<QIntValidator>
//#include<QSqlQueryModel>
//#include<QSqlQuery>
//#include<QtDebug>
//#include<QObject>
//#include<QDate>
//#include<QTableWidget>
//#include<QPixmap>
//#include<QTextDocument>
#include<QDesktopServices>
#include<QPainter>
#include "employe.h"
#include "historique.h"
//#include "QFile"
//#include "QTextStream"
#include<QPrintDialog>
#include<QString>

#include<QCameraImageCapture>
#include<QCamera>
#include<QCameraViewfinder>
#include<QCameraImageCapture>
#include<QVBoxLayout>
#include<QCameraInfo>
#include<QFileDialog>
#include <QSqlQuery>

#include <QMediaPlayer>
#include<QDateTime>
#include<QTimer>

//*******************************************gestion restaurant**************************************************************
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
#include <QFileDialog>
#include <QTextDocument>
#include<QPrintDialog>
#include "excel.h"


//*************************************************gestion client***************************************************************
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

//******************************************************gestion parking***********************************************************************
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

//********************************************************getion reservation***************************************************************************
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





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//arduino
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).


//horloge
    Timer= new QTimer(this);
    connect (Timer,SIGNAL(timeout()),this,SLOT(son()));
Timer->start(1000);


QTime time =QTime::currentTime();
QString time_text =time.toString("hh : mm : ss");
ui->label_11->setText(time_text);


    //son
    mMediaPlayer = new QMediaPlayer(this);
   connect(mMediaPlayer,&QMediaPlayer::positionChanged,[&](qint64 pos){ui->avance->setValue(pos);});
   connect(mMediaPlayer,&QMediaPlayer::positionChanged,[&](qint64 dur){ui->avance->setMaximum(dur);});


//camera
    mCamera = new QCamera(this);
    mCameraViewfinder = new QCameraViewfinder(this);
    mCameraImageCapture = new QCameraImageCapture(mCamera, this);


    m = new QVBoxLayout;
    mOpcionesMenu =new QMenu("Option", this);
    mEncenderAction = new QAction("ouvrir camera",this);
    mApagarAction = new QAction("voir photo",this);
    mCapturarAction =new QAction("enregistrer photo",this);


    mOpcionesMenu->addActions({ mEncenderAction,mApagarAction, mCapturarAction});
    ui->pushButton_9->setMenu(mOpcionesMenu);




mCamera->setViewfinder(mCameraViewfinder);

  m->addWidget(mCameraViewfinder);
  m->setMargin(0);
ui->scrollArea->setLayout(m);
connect(mEncenderAction,&QAction:: triggered,[&](){

mCamera->start();
});
connect(mApagarAction,&QAction::triggered, [&](){
mCamera->stop();
});
  connect (mCapturarAction,&QAction::triggered, [&](){
      auto filename = QFileDialog:: getSaveFileName(this,"capturar","/",
                                                    "imagen (*.jpg;*.jpeg)");
      if(filename.isEmpty()){
          return;
      }
mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
QImageEncoderSettings imageEncoderSettings;
imageEncoderSettings.setCodec("image/jpeg");
imageEncoderSettings.setResolution(1600,1200);
  mCameraImageCapture->setEncodingSettings(imageEncoderSettings);
mCamera->setCaptureMode(QCamera::CaptureStillImage);
 mCamera->start();
 mCamera->searchAndLock();
 mCameraImageCapture->capture(filename);
 mCamera->unlock();

  });

//controle de siasie
   ui->l_CIN->setValidator(new QIntValidator(0,999999,this));
   ui->l_tel->setValidator(new QIntValidator(0,999999999,this));
   ui->l_salaire->setValidator(new QIntValidator(0,999999999,this));

ui->tab_etud->setModel(E.afficher());


//************************************************gestion restaurant*****************************************************************************
QPixmap pix("C:/Users/ASUS/Desktop/LES diagrammes/qt_pic.jpg");
ui->le_cincl->setValidator(new QIntValidator(0, 99999999, this));
ui->le_cinemp->setValidator(new QIntValidator(0, 99999999, this));
ui->le_cinclsup->setValidator(new QIntValidator(0, 99999999, this));
ui->tab_commande->setModel(C.afficher());


//**************************************************gestion client**************************************************************************

ui->le_CIN->setValidator(new QIntValidator(0,9999999,this));
ui->le_mobile->setValidator(new QIntValidator(0,99999999,this));
ui->le_age->setValidator(new QIntValidator(0,99,this));
ui->tab_client->setModel(cl.afficher());

//****************************************************gestion parking*******************************************************************************
ui->tableView_park->setModel(tmparking.afficher());
ui->tabpartenaire_2->setModel(tmparking.afficher());
//***************************************************gestion reservation*************************************************************************************
ui->tab_reservation->setModel(R.afficher());
connect(ui->sendBtn_reservation, SIGNAL(clicked()),this, SLOT(sendMail()));
connect(ui->browseBtn_reservation, SIGNAL(clicked()), this, SLOT(browse()));

}

MainWindow::~MainWindow()
{
    delete ui;

}
void MainWindow::son()
{
QTime time =QTime::currentTime();
QString time_text =time.toString("hh : mm : ss");
ui->label_11->setText(time_text);
}
void MainWindow::on_ajouter_clicked()
{
 ui->tab_etud->setModel(E.afficher());

    int CIN=ui->l_CIN->text().toInt();
    int salaire=ui->l_salaire->text().toInt();
    int tel=ui->l_tel->text().toInt();

    QString nom=ui->l_nom->text();
    QString prenom=ui->l_prenom->text();

    QString sexe(ui->l_sexe->currentText());
    QString fonction(ui->comboBox->currentText());

Historique h;
  h.save("prenom:"+ui->l_prenom->text(),"nom :"+ui->l_nom->text(),"numero telephone:"+ui->l_tel->text());

     Employe E(nom,prenom,CIN,fonction,salaire,tel,sexe);

bool test=E.ajouter();

if(test)

    ui->tab_etud->setModel(E.afficher()); //refresh
        QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("Ajout avec succes\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
     ui->tab_etud->setModel(E.afficher()); //refresh

}




void MainWindow::on_button_modifier_clicked()
{ui->tab_etud->setModel(E.afficher());

    bool    test=E.modifierj(ui->l_CIN->text().toInt(),ui->l_nom->text(),ui->l_prenom->text(),ui->comboBox->currentText(),ui->l_salaire->text().toInt(),ui->l_sexe->currentText(),ui->l_tel->text().toInt());

    if (test)
          {
                  ui->tab_etud->setModel(E.afficher()); //refresh

              QMessageBox::information(nullptr,QObject::tr("OK"),
                                   QObject::tr("modification établie"),
                                   QMessageBox::Ok);}
          else{
          QMessageBox::critical(nullptr,("ERROR404"),
                                  QObject::tr("modification non établie"),
                                  QMessageBox::Cancel);}
}

void MainWindow::on_supprimer_clicked()
{

    Employe E1; E1.setcin(ui->lineEdit_sup->text().toInt());
    bool test=E1.supprimer(E1.getcin());
    QMessageBox msgBox;
    if(test)
    {
         ui->tab_etud->setModel(E1.afficher());
        msgBox.setText("suppression avec succes.");
    }
    else
          msgBox.setText("echec d'ajout");
                msgBox.exec();


}

void MainWindow::on_radioButton_clicked()
{
    QMessageBox msgBox ;
        QSqlQueryModel * model= new QSqlQueryModel();



           model->setQuery("select * from table1 order by fonction");

           model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("fonction"));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire"));
           model->setHeaderData(5, Qt::Horizontal, QObject::tr("sexe"));
           model->setHeaderData(5, Qt::Horizontal, QObject::tr("telephone"));
                    ui->tab_etud_4->setModel(model);
                    ui->tab_etud_4->show();
                    msgBox.setText("Tri avec succés.");
                    msgBox.exec();
}

void MainWindow::on_radioButton_3_clicked()
{
    QMessageBox msgBox ;
            QSqlQueryModel * model= new QSqlQueryModel();


               model->setQuery("select * from table1 order by CIN ");
               model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
               model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
               model->setHeaderData(3, Qt::Horizontal, QObject::tr("fonction"));
               model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire"));
               model->setHeaderData(5, Qt::Horizontal, QObject::tr("sexe"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("telephone"));
                        ui->tab_etud_4->setModel(model);
                        ui->tab_etud_4->show();
                        msgBox.setText("Tri avec succés.");
                        msgBox.exec();
}

void MainWindow::on_radioButton_2_clicked()
{
    QMessageBox msgBox ;
        QSqlQueryModel * model= new QSqlQueryModel();



           model->setQuery("select * from table1 order by nom");

           model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("fonction"));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire"));
           model->setHeaderData(5, Qt::Horizontal, QObject::tr("sexe"));
   model->setHeaderData(5, Qt::Horizontal, QObject::tr("telephone"));
                    ui->tab_etud_4->setModel(model);
                    ui->tab_etud_4->show();
                    msgBox.setText("Tri avec succés.");
                    msgBox.exec();
}

void MainWindow::on_l_r_textChanged(const QString &arg1)
{
    Employe a;
        if(ui->l_r->text() == "")
            {
                ui->rech->setModel(a.afficher());
            }
            else
            {
                 ui->rech->setModel(a.rechercher(ui->l_r->text()));
            }
}


void MainWindow::on_pushButton_clicked()
{
        Employe emp;
        emp.genererPDF();
        QString link="C:/Users/Administrateur/OneDrive/Bureau/liste.pdf";
        QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_historique_clicked()
    {
    QString link="C:/Users/Administrateur/OneDrive/Bureau/Atelier_Connexion/his.txt";
    QDesktopServices::openUrl(QUrl(link));
    }


void MainWindow::on_pushButton_2_clicked()
    {
    QPrinter  printer;
    printer.setPrinterName("test");
    QPrintDialog dialog(&printer,this);
    if (dialog.exec()==QDialog::Rejected) return;
    }


void MainWindow::on_pushButton_4_clicked()
    {
    QString link="https://mail.google.com/mail/u/0/#inbox";
    QDesktopServices::openUrl(QUrl(link));
    }


void MainWindow::on_pushButton_3_clicked()
    {
    QString link="https://www.facebook.com/watch/?ref=tab";
    QDesktopServices::openUrl(QUrl(link));
    }
void MainWindow::on_pushButton_5_clicked()
    {
    QString link="https://www.google.com/?hl=fr";
    QDesktopServices::openUrl(QUrl(link));
    }


                                                //music

void MainWindow::on_abrir_clicked()//choisir music
{
  QString filename = QFileDialog::getOpenFileName(this,"choisir votre music");
  if(filename.isEmpty())
  {
      return;
  }
mMediaPlayer->setMedia(QUrl::fromLocalFile(filename))  ;
mMediaPlayer->setVolume(ui->volume->value());
on_play_clicked();
}

void MainWindow::on_play_clicked()
{
mMediaPlayer->play();
}

void MainWindow::on_pause_clicked()
{
mMediaPlayer->pause();
}

void MainWindow::on_stop_clicked()
{
mMediaPlayer->stop();
}

void MainWindow::on_mute_clicked()
{
    if(ui->mute->text()=="Mute")
    {
       mMediaPlayer->setMuted(true);
       ui->mute->setText("unmute");
    } else
    {
        mMediaPlayer->setMuted(false);
        ui->mute->setText("mute");
    }

}

void MainWindow::on_volume_valueChanged(int value)
{
mMediaPlayer->setVolume(value);
}


//arduino

void MainWindow::on_pushButton_6_clicked() //ouvrir porte
{
      A.write_to_arduino("r");
}

void MainWindow::on_pushButton_7_clicked() //alarme
{
     A.write_to_arduino("a");
}

void MainWindow::on_pushButton_8_clicked() //pointage EXCEL
{
    QString link="‪C:/Users/Administrateur/OneDrive/Bureau/pointage employée.xlsm";
    QDesktopServices::openUrl(QUrl(link));
}


//*********************************************gestion restaurant************************************************************
void MainWindow::on_pb_ajouter_clicked()
{
    ui->tab_commande->setModel(C.afficher());
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
        ui->le_form->setText("");
        ui->le_cincl->setText("");
        ui->le_cinemp->setText("");
        ui->le_numcomm->setText("");
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));

        notifyIcon->showMessage("GESTION COMMANDE   ","COMMANDE Ajouter",QSystemTrayIcon::Information,15000);
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);


    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Commande"),QObject::tr("Erreur!\n" "click ok to exit"),QMessageBox::Ok);
    }



}



void MainWindow::on_pb_supprimer_clicked()
{

    C1.setcin_cl(ui->le_cinclsup->text().toInt());
    bool test=C1.supprimer(C1.getcin_cl());
    QMessageBox msgBox;
    if(test)
    {
        ui->tab_commande->setModel(C.afficher());
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));

        notifyIcon->showMessage("GESTION COMMANDE   ","COMMANDE supprimer",QSystemTrayIcon::Information,15000);
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("suppression effectué.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

    }

    else
    {

        msgBox.setText("Echec de suppression");
        msgBox.exec();

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

    bool test = C.update(num_commande,formule,cin_emp,cin_cl,date_com);
    if (test)
    {
        ui->tab_commande->setModel(C.afficher());

        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));

        notifyIcon->showMessage("GESTION COMMANDE","COMMANDE Modifiee",QSystemTrayIcon::Information,15000);
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("modification effectué.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                              QObject::tr("modification non établie"),
                              QMessageBox::Cancel);}
    ui->tab_commande->setModel(C.afficher());
}

void MainWindow::on_tri_parcincl_clicked()
{
    {
        QMessageBox msgBox ;
        QSqlQueryModel * model= new QSqlQueryModel();


        model->setQuery("select * from commande order by cin_cl");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num_commande"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Forumle"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr(" CIN employe"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN client"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date Commande"));

        ui->tableView->setModel(model);
        ui->tableView->show();
        msgBox.setText("Tri avec succés.");
        msgBox.exec();

    }
}

void MainWindow::on_tri_parcinemp_clicked()
{
    {
        QMessageBox msgBox ;
        QSqlQueryModel * model= new QSqlQueryModel();


        model->setQuery("select * from commande order by cin_emp ");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num_commande"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Forumle"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr(" CIN employe"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN client"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date Commande"));


        ui->tableView->setModel(model);
        ui->tableView->show();
        msgBox.setText("Tri avec succés.");
        msgBox.exec();
    }
}


void MainWindow::on_tri_parnumcom_clicked()
{
    QMessageBox msgBox ;
    QSqlQueryModel * model= new QSqlQueryModel();



    model->setQuery("select * from commande order by num_commande");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num_commande"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Forumle"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr(" CIN employe"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN client"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date Commande"));

    ui->tableView->setModel(model);
    ui->tableView->show();
    msgBox.setText("Tri avec succés.");
    msgBox.exec();
}

void MainWindow::on_le_recherche_commande_textChanged (const QString &arg1)
{
    Commande c;
    if(ui->le_recherche_commande->text() == "")
    {
        ui->tableView->setModel(c.afficher());
    }
    else
    {
        ui->tableView->setModel(c.rechercher(ui->le_recherche_commande->text()));
    }
}


void MainWindow::on_pushButton_pdf_clicked() //generer PDF
{

    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tab_commande->model()->rowCount();
    const int columnCount = ui->tab_commande->model()->columnCount();

    out <<  "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("strTitle")
        <<  "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"

           //     "<align='right'> " << datefich << "</align>"
           "<center> <H1>Liste des commandes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tab_commande->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tab_commande->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr> <td bkcolor=0>" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tab_commande->isColumnHidden(column))
            {
                QString data = ui->tab_commande->model()->data(ui->tab_commande->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table> </center>\n"
           "</body>\n"
           "</html>\n";

    QString fileName = QFileDialog::getSaveFileName((QWidget * )0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer (QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);

}
void MainWindow::on_pushButton_stat_clicked()
{
    QChart* chart_bar = C.chart_pie();
    QChartView* chart_view_bar = new QChartView(chart_bar, ui->label_stat );
    chart_view_bar->setRenderHint(QPainter::Antialiasing);
    chart_view_bar->setMinimumSize(400,400);
    chart_view_bar->show();
}

void MainWindow::on_pushButton_excel_clicked() // generer EXCEL
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation en fichier Excel"), qApp->applicationDirPath (),
                                                    tr("Fichiers d'extension Excel (*.xls)"));
    if (fileName.isEmpty())
        return;

    EXCEL obj(fileName, "SOURCE_PROJET2A", ui->tab_commande);

    // you can change the column order and
    // choose which colum to export
    obj.addField(0, "Num_commande", "char(20)");
    obj.addField(1, "Formule", "char(20)");
    obj.addField(2, "CIN_EMP", "char(20)");
    obj.addField(3, "CIN_CL", "char(20)");
    obj.addField(4, "DATE_COM", "char(20)");



    int retVal = obj.export2Excel();

    if( retVal > 0)
    {
        QMessageBox::information(this, tr("FAIS!"),
                                 QString(tr("%1 enregistrements exportés!")).arg(retVal)
                                 );
    }
}



void MainWindow::on_pb_commandeprete_clicked()
{
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->setIcon(QIcon("icone.png"));

    notifyIcon->showMessage("GESTION COMMANDE"," LA COMMANDE EST PRETE ",QSystemTrayIcon::Information,15000);
}


//******************************************************gestion client*************************************************************************

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



//****************************************************************gestion parking**********************************************************************

void MainWindow::on_pbconfirme_park_clicked()
{srand (time(NULL));
    QDate d = QDate::currentDate() ;
     QString datee =d.toString("dd / MM / yyyy ") ;
     QString fn="ajouter" ;
     parkingh ph("parking",datee,fn);
             ph.ajoutehis();
    int code = ui->codelin->text().toInt();
           QString nbh= ui->nbh->text();
           QString prix= ui->prix_park->text();
           int cin_emp = ui->cin_emp_park->text().toInt();
           int cin_cl = ui->cin_cl->text().toInt();
            parking p(code,nbh,prix,cin_emp,cin_cl);
         bool test=p.ajouter();
         if(test)
       {
       QMessageBox::information(nullptr, QObject::tr("Ajouter un produit"),
                         QObject::tr("Ajoute success.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
       ui->tableView_park->setModel(tmparking.afficher());
       }
         else
             QMessageBox::critical(nullptr, QObject::tr("Ajouter un produit"),
                         QObject::tr("Erreur !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tableView_park_activated(const QModelIndex &index)
{
    QString val = ui->tableView_park->model()->data(index).toString() ;
       QSqlQuery qry;
       qry.prepare(" SELECT * from PARKING where code = '"+val+"'");
       int code = ui->codelin->text().toInt();
              QString nbh= ui->nbh->text();
              QString prix= ui->prix_park->text();
              int cin_emp = ui->cin_emp_park->text().toInt();
              int cin_cl = ui->cin_cl->text().toInt();
       if (qry.exec())
       {
           while (qry.next()) {
               ui->codelin->setText(qry.value(0).toString()) ;
               ui->nbh->setText(qry.value(1).toString()) ;
               ui->prix_park->setText(qry.value(2).toString()) ;
               ui->cin_emp_park->setText(qry.value(3).toString()) ;
               ui->cin_cl->setText(qry.value(4).toString()) ;
              }
              ui->tableView_park->setModel(tmparking.afficher());
      }
}

void MainWindow::on_pushButton_modif_parking_clicked()
{
    int code = ui->codelin->text().toInt();
           QString nbh= ui->nbh->text();
           QString prix= ui->prix_park->text();
           int cin_emp = ui->cin_emp_park->text().toInt();
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
  ui->tableView_park->setModel(tmparking.afficher());
}

void MainWindow::on_pushButton_supp_parking_clicked()
{
    int code = ui->codelin->text().toInt();
    bool test=tmparking.supprimer(code);
    if (test)
    {
        ui->tableView_park->setModel(tmparking.afficher());
        QMessageBox::information(nullptr, QObject::tr("supprimer un parking"),
                          QObject::tr("parking supprimé.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
        }
          else
              QMessageBox::critical(nullptr, QObject::tr("Supprimer un parking"),
                          QObject::tr("Erreur !.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

ui->tableView_park->setModel(tmparking.afficher());

}

void MainWindow::on_pushButton_pdf_parking_clicked()
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

void MainWindow::on_recherche_park_clicked()
{
    int code;

        code=ui->codelin->text().toInt();
    bool test= true;
    if(test==(true))
    {
      ui->tableView_park->setModel(tmparking.rechercher(code));
}
}

void MainWindow::on_pushButton_tri_park_clicked()
{
   ui->tableView_park->setModel( tmparking.afficher_tri());
}

void MainWindow::on_pbconfirme_2_park_clicked()
{
    ui->tabpartenaire_2->setModel(tmparking.afficher());

}

//**********************************************************gestion reservation***************************************************************************


void MainWindow::on_pb_ajouter_reservation_clicked()
{
    int code_r=ui->code_res->text().toInt();
    int nb_table=ui->num_t_reservation->text().toInt();
    int nb_per=ui->num_p_reservation->text().toInt();
    QString email=ui->Email_reservation->text();
    QDate date=ui->la_date_reservation->date();
    QString type_r=ui->type_reservation->text();
    QTime heure_d=ui->heure_s_reservation->time();
    QTime heure_a=ui->heure_e_reservation->time();

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

void MainWindow::on_pb_modifier_reservation_clicked()
{
    int code_r=ui->code_res->text().toInt();
    int nb_table=ui->num_t_reservation->text().toInt();
    int nb_per=ui->num_p_reservation->text().toInt();
    QString email=ui->Email_reservation->text();
    QDate date=ui->la_date_reservation->date();
    QString type_r=ui->type_reservation->text();
    QTime heure_d=ui->heure_s_reservation->time();
    QTime heure_a=ui->heure_e_reservation->time();



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
            ui->type_reservation->setText(qry.value(1).toString());
            ui->num_p_reservation->setText(qry.value(2).toString());
            ui->la_date_reservation->setDate(qry.value(3).toDate());
            ui->num_t_reservation->setText(qry.value(4).toString());
            ui->Email_reservation->setText(qry.value(5).toString());
            ui->heure_e_reservation->setTime(qry.value(6).toTime());
            ui->heure_s_reservation->setTime(qry.value(7).toTime());

        }
    }
}

void MainWindow::on_pb_supprimer_reservation_clicked()
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




void MainWindow::on_tri_reserv_clicked()
{
    ui->tab_reservation->setModel(R.afficher_tri_type());

}

void MainWindow::on_heure_reservation_clicked()
{
    ui->tab_reservation->setModel(R.afficher_tri_heure());

}

void MainWindow::on_chercher_reservation_clicked()
{
    QString choix;
            choix=ui->li_chercher_reservation->text();
            QString li_rechercher=ui->li_chercher_reservation->text();
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

    ui->file_reservation->setText( fileListString );

}


void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("malek.bensaid@esprit.tn",ui->mail_pass_reservation->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("malek.bensaid@esprit.tn", ui->rcpt_reservation->text() , ui->subject_reservation->text(),ui->msg_reservation->toPlainText(), files );
    else
        smtp->sendMail("malek.bensaid@esprit.tn", ui->rcpt_reservation->text() , ui->subject_reservation->text(),ui->msg_reservation->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt_reservation->clear();
    ui->subject_reservation->clear();
    ui->file_reservation->clear();
    ui->msg_reservation->clear();
    ui->mail_pass_reservation->clear();
}






void MainWindow::on_stat_reservation_clicked()
{

    QPieSeries *series=new QPieSeries();
    series->append("< 10",tmpr.calcul_type(0,10));
    series->append("[10..25]",tmpr.calcul_type(10,25));
    series->append("[25..50]",tmpr.calcul_type(25,50));
    series->append("[50..100]",tmpr.calcul_type(50,100));

    QPieSlice *slice1=series->slices().at(1);
    slice1->setExploded(true);

    QChart *chart =new QChart();
    chart->addSeries(series);
    chart->setTitle("les types de reservations");
    chart->setAnimationOptions(QChart::AllAnimations);
    QChartView *chartview=new QChartView(chart);

    this->setCentralWidget(chartview);

}
