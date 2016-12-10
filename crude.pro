#-------------------------------------------------
#
# Project created by QtCreator 2016-04-18T20:53:47
#
#-------------------------------------------------

QT       += core gui
QT += multimediawidgets
QT += multimedia
QT += gui
QT += network \
      xml \

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = crude
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    get_tag.cpp \
    listwidgetplsopen.cpp \
    tablepls.cpp \
    qwt.cpp \
    music_properties.cpp
unix|win32: LIBS += -ltag
HEADERS  += mainwindow.h \
    get_tag.h \
    listwidgetplsopen.h \
    tablepls.h \
    qwt.h \
    music_properties.h

FORMS    += mainwindow.ui \
    listwidgetplsopen.ui \
    tablepls.ui \
    music_properties.ui

RESOURCES += \
    image.qrc

