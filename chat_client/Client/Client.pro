#-------------------------------------------------
#
# Project created by QtCreator 2018-11-21T19:51:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
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
        client.cpp \
    signin.cpp \
    timetable.cpp \
    chatting.cpp \
    receiver.cpp \
    list.cpp \
    friendsearch.cpp \
    friendalarm.cpp \
    makechatroom.cpp \
    schedule.cpp \
    thread.cpp \
    dailyscheduleadd.cpp \
    weeklyscheduleadd.cpp \
    timethread.cpp \
    weeklyscheduledelete.cpp \
    groupscheduleadd.cpp \
    groupscheduleaccept.cpp

HEADERS += \
        client.h \
    signin.h \
    timetable.h \
    chatting.h \
    receiver.h \
    list.h \
    tool.h \
    friendsearch.h \
    friendalarm.h \
    makechatroom.h \
    schedule.h \
    thread.h \
    dailyscheduleadd.h \
    weeklyscheduleadd.h \
    timethread.h \
    weeklyscheduledelete.h \
    groupscheduleadd.h \
    groupscheduleaccept.h

FORMS += \
        client.ui \
    signin.ui \
    timetable.ui \
    chatting.ui \
    list.ui \
    friendsearch.ui \
    friendalarm.ui \
    makechatroom.ui \
    schedule.ui \
    dailyscheduleadd.ui \
    weeklyscheduleadd.ui \
    weeklyscheduledelete.ui \
    groupscheduleadd.ui \
    groupscheduleaccept.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    client.qmodel

STATECHARTS += \
    CL.scxml
