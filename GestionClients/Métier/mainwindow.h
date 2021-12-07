#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<client.h>
#include<avis.h>

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


private:
    Ui::MainWindow *ui;
    Client cl;
    Avis a;

};

#endif // MAINWINDOW_H
