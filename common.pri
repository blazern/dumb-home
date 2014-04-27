QMAKE_CXXFLAGS += -std=c++11

QT += qml quick widgets

SOURCES += \
    $$PWD/main/cppsrc/PlayerActionsQmlReceiver.cpp \
    $$PWD/main/cppsrc/Map.cpp \
    $$PWD/main/cppsrc/Player.cpp \
    $$PWD/main/cppsrc/QmlMapInterface.cpp

HEADERS += \
    $$PWD/main/cppsrc/PlayerActionsQmlReceiver.h \
    $$PWD/main/cppsrc/Map.h \
    $$PWD/main/cppsrc/Player.h \
    $$PWD/main/cppsrc/Mover.h \
    $$PWD/main/cppsrc/MapObject.h \
    $$PWD/main/cppsrc/MapListener.h \
    $$PWD/main/cppsrc/QmlMapInterface.h
