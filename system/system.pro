#-------------------------------------------------
#
# Project created by QtCreator 2019-05-20T22:18:56
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = system
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
        main.cpp \
        add.cpp \
    mainwindow.cpp \
    login.cpp \
    usermanagement.cpp \
    registered.cpp \
    adminmanage.cpp \
    changeclass.cpp \
    help.cpp \
    classnum.cpp

HEADERS += \
        add.h \
    mainwindow.h \
    login.h \
    usermanagement.h \
    registered.h \
    adminmanage.h \
    changeclass.h \
    help.h \
    classnum.h

FORMS += \
        add.ui \
    mainwindow.ui \
    login.ui \
    usermanagement.ui \
    registered.ui \
    adminmanage.ui \
    changeclass.ui \
    help.ui \
    classnum.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    photo.qrc

