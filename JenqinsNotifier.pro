QT += gui
QT += core
QT += xml
QT += network
QT += widgets


TARGET = JenqinsNotifier

CONFIG -= app_bundle
CONFIG += c++11
CONFIG += console

TEMPLATE = app

SOURCES = \
    main.cpp \
    application.cpp \
    singleinstanceguard.cpp \
    networkmanagersingleton.cpp \
    settingssingleton.cpp \
    jenkinsApi/apihandler.cpp \
    jenkinsApi/lastsuccesbuildnumber.cpp \
    jenkinsApi/xmlapihandler.cpp \
    jenkinsApi/joblist.cpp \
    jenkinsApi/buildapihandler.cpp \
    jenkinsApi/buildstatus.cpp \
    jenkinsApi/changesinfo.cpp \
    dataTypes/notificationruledata.cpp \
    notificationrule.cpp \
    notificationlogic.cpp \
    xmlutils.cpp \
    ui/uimanager.cpp \

HEADERS = \
    application.h \
    singleinstanceguard.h \
    networkmanagersingleton.h \
    settingssingleton.h \
    jenkinsApi/apihandler.h \
    jenkinsApi/lastsuccesbuildnumber.h \
    jenkinsApi/xmlapihandler.h \
    jenkinsApi/joblist.h \
    jenkinsApi/buildapihandler.h \
    jenkinsApi/buildstatus.h \
    jenkinsApi/changesinfo.h \
    dataTypes/buildresult.h \
    dataTypes/changeitem.h \
    dataTypes/notificationdata.h \
    dataTypes/notificationruledata.h \
    notificationrule.h \
    notificationlogic.h \
    xmlutils.h \
    ui/uimanager.h \

