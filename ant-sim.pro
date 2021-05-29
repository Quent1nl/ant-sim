QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ant.cpp \
    anthill.cpp \
    cellule.cpp \
    environnement.cpp \
    food.cpp \
    main.cpp \
    mainwindow.cpp \
    obstacle.cpp

HEADERS += \
    ant.h \
    anthill.h \
    cellule.h \
    environnement.h \
    food.h \
    mainwindow.h \
    obstacle.h

FORMS += \
    environnement.ui \
    mainwindow.ui

TRANSLATIONS += \
    ant-sim_en_150.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
