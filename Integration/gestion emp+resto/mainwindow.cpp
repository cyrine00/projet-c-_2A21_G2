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


//****************************************************************************************************************

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






