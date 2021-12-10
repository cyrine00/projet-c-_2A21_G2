#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"arduino.h"
#include "employe.h"

#include <QMainWindow>

#include <QCameraInfo>
#include<QCamera>
#include<QCameraViewfinder>
#include<QCameraImageCapture>
#include<QVBoxLayout>
#include<QScopedPointer>
#include<QPushButton>
//**********************************************gestion restaurant**********************************************************************
#include "commande.h"

//**********************************************gestion client**********************************************************************************
#include <QMainWindow>
#include<client.h>
#include<avis.h>

//**********************************************gestion parking********************************************************************************

#include "parking.h"
#include <QDesktopServices>
#include <QDateTime>
#include <QHeaderView>
#include <QStandardItemModel>

//***********************************************************gestion reservation****************************************************************
#include "reservation.h"
#include "smtp.h"
#include <QFileDialog>
#include <QDebug>
#include "QTimer"
#include "QPalette"
#include "vector"
#include "QKeyEvent"
#include "QLineEdit"





namespace Ui {
class MainWindow;
}


class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;


class QMediaPlayer;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
void son();

private slots:
void on_login_clicked();
    void on_ajouter_clicked();
    void on_supprimer_clicked();
    void on_button_modifier_clicked();
    void on_historique_clicked();
    void on_radioButton_clicked();
    void on_radioButton_3_clicked();
    void on_radioButton_2_clicked();
    void on_l_r_textChanged(const QString &arg1);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
   // void on_pushButton_9_clicked();

   // void on_sendBtn_clicked();

   // void on_sendBtn_windowIconTextChanged(const QString &iconText);

   // void on_sendBtn_objectNameChanged(const QString &objectName);

  //  void on_sendBtn_windowTitleChanged(const QString &title);

 //   void on_rcpt_textChanged(const QString &arg1);

    void on_pushButton_6_clicked();

    void on_musicplay_clicked();

    void on_mutemusic_clicked();

    void on_abrir_clicked();

    void on_play_clicked();

    void on_pause_clicked();

    void on_stop_clicked();

    void on_mute_clicked();

    void on_volume_valueChanged(int value);

    void on_sooon_clicked();

    void on_groupBox_3_clicked();

    void on_label_11_linkActivated(const QString &link);

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();


 //******************************************************gestion restaurant****************************************************************
    void on_pb_ajouter_clicked();
    void on_pb_supprimer_clicked();
    void on_pb_modifier_clicked();

    void on_le_recherche_abonne_cursorPositionChanged(int arg1, int arg2);

    void on_le_recherche_commande_textChanged(const QString &arg1);

    //void on_radioButton_clicked();

    void on_tri_parcincl_clicked();

    void on_tri_parcinemp_clicked();

    void on_tri_parnumcom_clicked();

    void on_pushButton_pdf_clicked();

    //void on_pushButton_5_clicked();

    void on_pushButton_stat_clicked();

    void on_pushButton_excel_clicked();

    //void on_pushButton_6_clicked();

    void on_pb_commandeprete_clicked();

//*********************************************gestion client******************************************************************************
    void on__ajouter_clicked();

    void on_supprimer_pb_clicked();

    void on_modifier_pb_clicked();

    void on_pb_afficher_clicked();

    void on_ageb_clicked();

    void on_nomb_clicked();

    void on_lineEdit_23_textChanged(const QString &arg1);

    void on_tab_client_activated(const QModelIndex &index);

    void on_valider_clicked();

    void on_tabWidget_2_currentChanged(int index);

    void on_nbvisite_clicked();

    void on_imprimer_clicked();

    void on_reset_clicked();

    void on_client_mois_clicked();

    void on_gifts_clicked();
//****************************************************gestion parking****************************************************************
    void on_pbconfirme_park_clicked();

    void on_tableView_park_activated(const QModelIndex &index);

    void on_pushButton_modif_parking_clicked();

    void on_pushButton_supp_parking_clicked();

    void on_pushButton_pdf_parking_clicked();

    void on_recherche_park_clicked();

    void on_pushButton_tri_park_clicked();

    void on_pbconfirme_2_park_clicked();

//******************************************************gestion resrevation*************************************************************
    void on_pb_ajouter_reservation_clicked();

    void on_pb_modifier_reservation_clicked();

    void on_tab_reservation_activated(const QModelIndex &index);

    void on_pb_supprimer_reservation_clicked();




    void on_tri_reserv_clicked();

    void on_heure_reservation_clicked();

    void on_chercher_reservation_clicked();

    void sendMail();
    void mailSent(QString);
    void browse();



    void on_stat_reservation_clicked();
    //**********Arduino1***************
void update_label();




void on_qr_clicked();

private:
    Ui::MainWindow *ui;
    Employe E;

    QCamera *mCamera;
    QCameraViewfinder * mCameraViewfinder;
    QCameraImageCapture *mCameraImageCapture;
    QVBoxLayout *m;
    QMenu *mOpcionesMenu;
    QAction *mEncenderAction; // ouvrir
    QAction *mApagarAction; //stop
    QAction *mCapturarAction; //capture

QMediaPlayer *mMediaPlayer;
QTimer *Timer;

QByteArray data;
Arduino A;
//************************************************gestion restaurant********************************************************
Commande C,C1;
QStringList files;

//*************************************************gestion client******************************************************************
Client cl;
Avis a;
//**************************************************gestion parking**********************************************************************
parking tmparking;
QDesktopServices service;
QDateTime date;

//**************************************************gestion reservation*******************************************************************************
Reservation R;
QStringList files2;
 Reservation tmpr;

//*****************Arduino**********************************
 QByteArray data1;
     Arduino Ar;
};

#endif // MAINWINDOW_H
