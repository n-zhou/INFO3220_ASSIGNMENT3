#-------------------------------------------------
#
# Project created by QtCreator 2018-04-23T23:26:07
#
#-------------------------------------------------

QT       += core gui
QT       += network
CONFIG += #console

#comment out the console to make it not appear

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PoolTable
TEMPLATE = app


SOURCES += main.cpp \
    dialog.cpp \
    poolgame.cpp \
    gamebuilder.cpp \
    initializer.cpp \
    stage2ball.cpp \
    stage2factory.cpp \
    stage1factory.cpp \
    stage1table.cpp \
    stage1ball.cpp \
    stage2table.cpp \
    pocket.cpp \
    util.cpp \
    changeinpoolgame.cpp \
    cueballdecorator.cpp \
    duplicationballdecorator.cpp \
    mainwindow.cpp \
    server.cpp \
    client.cpp \
    clientdisplay.cpp \
    stage3factory.cpp \
    serverdisplay.cpp \
    memento.cpp \
    originator.cpp

HEADERS  += dialog.h \
    poolgame.h \
    table.h \
    ball.h \
    abstractfactory.h \
    gamebuilder.h \
    initializer.h \
    stage2ball.h \
    stage2factory.h \
    stage1factory.h \
    stage1ball.h \
    stage1table.h \
    changeinpoolgame.h \
    util.h \
    stage2table.h \
    pocket.h \
    balldecorator.h \
    cueballdecorator.h \
    duplicationballdecorator.h \
    mainwindow.h \
    server.h \
    client.h \
    clientdisplay.h \
    stage3factory.h \
    serverdisplay.h \
    multiplayerdisplay.h \
    multiplayerdisplay.h \
    memento.h \
    originator.h

DISTFILES += \
    config.json

