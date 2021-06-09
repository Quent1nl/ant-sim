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
    egg.cpp \
    food.cpp \
    larva.cpp \
    main.cpp \
    map.cpp \
    obstacle.cpp \
    queen.cpp \
    scene.cpp \
    warrior.cpp

HEADERS += \
    ant.h \
    anthill.h \
    cellule.h \
    coordinates.h \
    egg.h \
    food.h \
    larva.h \
    map.h \
    obstacle.h \
    queen.h \
    scene.h \
    warrior.h

FORMS += \
    map.ui

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
