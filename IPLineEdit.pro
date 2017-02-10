#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T14:20:00
#
#-------------------------------------------------

QT       += core gui designer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IPLineEdit


DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11 plugin release

#раскомментировать это и закомментировать соответствубщее, чтобы проверить функциональность
#TEMPLATE = lib
#TARGET = $$qtLibraryTarget($$TARGET)

TEMPLATE = app

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

INCLUDEPATH += .

SOURCES += \
    main.cpp \
    iplineedit.cpp \
    iplineeditplugin.cpp

HEADERS  += \
    iplineedit.h \
    iplineeditplugin.h \
    ipaddress.h

