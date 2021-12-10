#include "arduino1.h"

#include<QDebug>

Arduino1::Arduino1()
{
data1="";
arduino_port_name="";
arduino_is_available=false;
serial=new QSerialPort;
}
QString Arduino1::getarduino_port_name()
{
    return arduino_port_name;
}
QSerialPort* Arduino1::getserial()
{
    return serial;
}

int Arduino1::connect_arduino()
{
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts() )
    {
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier())
        {if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier() == arduino_uno_product_id)
            {arduino_is_available = true;
                arduino_port_name=serial_port_info.portName();
    }}
}
    qDebug() <<"arduino_port_name is :" << arduino_port_name;
    if(arduino_is_available)
    {
        serial->setPortName(arduino_port_name);
        if(serial->open(QSerialPort::ReadOnly))
        {
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        return 0;
        }
        return 1;

    }}

QByteArray Arduino1::read_from_arduino()
{
    if(serial->isReadable())
    {
        data1=serial->readAll();
        return data1;
    }
}
int Arduino1::close_arduino()
{
    if(serial->isOpen())
    {
        serial->close();
        return 0;
    }
    return 1;
}
