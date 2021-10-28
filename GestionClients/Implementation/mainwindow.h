#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<client.h>
#include<QSqlQueryModel>
#include <QMainWindow>

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
    void on__ajouter_clicked();

    void on__supprimer_clicked();

private:
    Ui::MainWindow *ui;
    Client cl;
};
#endif // MAINWINDOW_H
