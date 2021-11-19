#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "employe.h"
#include <QMainWindow>

#include <QCameraInfo>
#include<QCamera>
#include<QCameraViewfinder>
#include<QCameraImageCapture>
#include<QVBoxLayout>
#include<QScopedPointer>
#include<QPushButton>


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
};

#endif // MAINWINDOW_H
