#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<client.h>
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

private:
    Ui::MainWindow *ui;
    Client cl;
};

#endif // MAINWINDOW_H
