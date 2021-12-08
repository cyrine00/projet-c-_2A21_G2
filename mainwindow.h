#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "reservation.h"
#include "smtp.h"
#include <QFileDialog>
#include <QDebug>
#include "QTimer"
#include "QPalette"
#include "vector"
#include "QKeyEvent"
#include "QLineEdit"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_modifier_clicked();

    void on_tab_reservation_activated(const QModelIndex &index);

    void on_pb_supprimer_2_clicked();




    void on_tri_clicked();



    void on_chercher_clicked();

    void sendMail();
    void mailSent(QString);
    void browse();








    void on_pushButton_3_clicked();

    void on_qr_clicked();

    void on_tri_date_clicked();

private:
    Ui::MainWindow *ui;
    Reservation R;
    QStringList files;
};
#endif // MAINWINDOW_H
