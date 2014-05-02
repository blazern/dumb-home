QMAKE_CXXFLAGS += -std=c++11

QT += qml quick widgets

SOURCES += \
    $$PWD/main/cppsrc/PlayerActionsQmlReceiver.cpp \
    $$PWD/main/cppsrc/map/Map.cpp \
    $$PWD/main/cppsrc/map/Player.cpp \
    $$PWD/main/cppsrc/QmlMapInterface.cpp \
    $$PWD/main/cppsrc/MapObjectQmlWrapper.cpp \
    $$PWD/main/cppsrc/map/StaticMapObjectImpl.cpp

HEADERS += \
    $$PWD/main/cppsrc/PlayerActionsQmlReceiver.h \
    $$PWD/main/cppsrc/map/Map.h \
    $$PWD/main/cppsrc/map/Player.h \
    $$PWD/main/cppsrc/map/Mover.h \
    $$PWD/main/cppsrc/map/DynamicMapObject.h \
    $$PWD/main/cppsrc/map/MapListener.h \
    $$PWD/main/cppsrc/QmlMapInterface.h \
    $$PWD/main/cppsrc/map/StaticMapObject.h \
    $$PWD/main/cppsrc/MapObjectQmlWrapper.h \
    $$PWD/main/cppsrc/map/StaticMapObjectImpl.h
