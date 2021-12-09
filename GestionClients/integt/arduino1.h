#ifndef ARDUINO1_H
#define ARDUINO1_H

#include<QtSerialPort/QSerialPort> //classe rassemblant des fonctions permettent l'echange des données
#include<QtSerialPort/QSerialPortInfo> //classe fournissant des informations sur les ports disponibles
#include<QString>
#include<QDebug>

class Arduino1
{
public:
    Arduino1();
    int connect_arduino();
    int close_arduino();
    int write_to_arduino(QByteArray);
    QByteArray read_from_arduino();
    QSerialPort* getserial();
    QString getarduino_port_name();
private:
QSerialPort * serial;
static const quint16 arduino_uno_vendor_id=9025;
static const quint16 arduino_uno_product_id =67;

QString arduino_port_name;
bool arduino_is_available;
QByteArray data1;
};
#endif // ARDUINO1_H
