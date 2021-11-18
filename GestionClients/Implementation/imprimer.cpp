#include "imprimer.h"
#include "ui_imprimer.h"
#include<QPrinter>
#include<QPrintDialog>
#include<client.h>
#include<QMessageBox>
#include<QObject>
/*#include<QImage>
#include<QPixmap>*/

imprimer::imprimer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::imprimer)
{
    ui->setupUi(this);
}

imprimer::~imprimer()
{
    delete ui;
}

void imprimer::on_pushButton_clicked()
{
    /*QImage imageObject;
        imageObject.load("c:/QR.png");
        ui->labeli->setPixmap(QPixmap::fromImage(imageObject));*/
    QPrinter  printer;
    printer.setPrinterName("desired printer name");
    QPrintDialog dialog(&printer,this);
    if(dialog.exec() == QDialog::Rejected) return;
    ui->textEdit->print(&printer);
    QMessageBox::information(nullptr, QObject::tr("Carte"),
                QObject::tr("Carte imprimé ! \n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
void imprimer::setclient(Client cl)
{
    ui->textEdit->setText(cl.getnom());
}
