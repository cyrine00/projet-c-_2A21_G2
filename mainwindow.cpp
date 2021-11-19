#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPrinter>
#include<QMessageBox>
#include<QIntValidator>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
//#include<QDate>
#include<QTableWidget>
#include<QPixmap>
#include<QTextDocument>
#include<QDesktopServices>
#include<QPainter>
#include "employe.h"
#include "historique.h"
#include "QFile"
#include "QTextStream"
#include<QPrintDialog>
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
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
          QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
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
