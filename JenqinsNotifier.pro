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
    networkmanagersingleton.cpp \
    settingssingleton.cpp \
    jenkinsApi/apihandler.cpp \
    jenkinsApi/lastsuccesbuildnumber.cpp \
    jenkinsApi/xmlapihandler.cpp \
    jenkinsApi/joblist.cpp \
    jenkinsApi/buildapihandler.cpp \
    jenkinsApi/buildstatus.cpp \
    jenkinsApi/changesinfo.cpp \
    notificationruledata.cpp \
    notificationrule.cpp \
    notificationlogic.cpp \
    xmlutils.cpp \

HEADERS = \
    networkmanagersingleton.h \
    settingssingleton.h \
    buildresult.h \
    jenkinsApi/apihandler.h \
    jenkinsApi/lastsuccesbuildnumber.h \
    jenkinsApi/xmlapihandler.h \
    jenkinsApi/joblist.h \
    jenkinsApi/buildapihandler.h \
    jenkinsApi/buildstatus.h \
    jenkinsApi/changesinfo.h \
    notificationruledata.h \
    notificationrule.h \
    notificationlogic.h \
    xmlutils.h \

