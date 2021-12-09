#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "parking.h"
#include <QDesktopServices>
#include <QDateTime>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <arduino.h>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbconfirme_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_recherche_clicked();

    void on_pushButton_4_clicked();

    void on_pbconfirme_2_clicked();

    void on_pb_ask_clicked();

private:
    QMediaPlayer * erreur = new QMediaPlayer ;
    Ui::MainWindow *ui;
    parking tmparking;
    QDesktopServices service;
    Arduino A;
    QDateTime date;

};

#endif // MAINWINDOW_H
