QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QWaitLabel

TEMPLATE = app

SOURCES += main.cpp\
        window.cpp \
    qwaitlabel.cpp

HEADERS  += window.h \
    qwaitlabel.h

FORMS    += window.ui
