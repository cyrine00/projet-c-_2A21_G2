#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#QT       += core gui sql
#-------------------------------------------------

QT      += core gui sql
QT += widgets
QT += printsupport
QT += sql network printsupport
QT += gui
QT      += core gui multimedia
QT += serialport
QT      += core gui multimedia multimediawidgets charts
QT       += core gui charts

QT += serialport
QT+= svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    arduino.cpp \
    arduino1.cpp \
    avis.cpp \
    client.cpp \
    commande.cpp \
    employe.cpp \
    excel.cpp \
    historique.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    parking.cpp \
    qcustomplot.cpp \
    qrcode.cpp \
    qrcodegeneratordemo.cpp \
    qrcodegeneratorworker.cpp \
    qrwidget.cpp \
    reservation.cpp \
    smtp.cpp

HEADERS += \
    arduino.h \
    arduino1.h \
    avis.h \
    client.h \
    commande.h \
    employe.h \
    excel.h \
    historique.h \
        mainwindow.h \
    connection.h \
    parking.h \
    qcustomplot.h \
    qrcode.h \
    qrwidget.h \
    reservation.h \
    smtp.h

FORMS += \
        mainwindow.ui

QMAKE_CXXFLAGS+= -std=gnu++11
QMAKE_CXXFLAGS += -std=gnu++14
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

STATECHARTS +=

DISTFILES +=
