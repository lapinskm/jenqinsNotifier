QT -= gui
QT += core
QT += xml
QT += network

TARGET = JenqinsNotifier

CONFIG -= app_bundle
CONFIG += c++11
CONFIG += console

TEMPLATE = app

SOURCES = \
    main.cpp \
    joblist.cpp \
    xmlapihandler.cpp \
    networkmanagersingleton.cpp \
    poller.cpp \
    buildstatus.cpp \
    settingssingleton.cpp \
    buildapihandler.cpp \
    apihandler.cpp \

HEADERS += \
    joblist.h \
    xmlapihandler.h \
    networkmanagersingleton.h \
    poller.h \
    buildstatus.h \
    settingssingleton.h \
    buildapihandler.h \
    apihandler.h \
