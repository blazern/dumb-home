QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

QT += qml quick widgets

SOURCES += \
    $$PWD/main/cppsrc/PlayerActionsQmlReceiver.cpp \
    $$PWD/main/cppsrc/map/Map.cpp \
    $$PWD/main/cppsrc/map/Player.cpp \
    $$PWD/main/cppsrc/QmlMapInterface.cpp \
    $$PWD/main/cppsrc/MapObjectQmlWrapper.cpp \
    $$PWD/main/cppsrc/map/Wall.cpp \
    $$PWD/main/cppsrc/map/StaticMapLayer.cpp \
    $$PWD/main/cppsrc/map/DynamicMapLayer.cpp \
    $$PWD/main/cppsrc/map/DynamicMapObjectGeometry.cpp \
    $$PWD/main/cppsrc/json/JsonMapParser.cpp \
    $$PWD/main/cppsrc/json/StaticMapLayerConstructor.cpp \
    $$PWD/main/cppsrc/map/Air.cpp

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
    $$PWD/main/cppsrc/map/Wall.h \
    $$PWD/main/cppsrc/map/StaticMapLayer.h \
    $$PWD/main/cppsrc/map/DynamicMapLayer.h \
    $$PWD/main/cppsrc/map/DynamicMapObjectGeometry.h \
    $$PWD/main/cppsrc/json/JsonObjectParser.h \
    $$PWD/main/cppsrc/json/JsonMapParser.h \
    $$PWD/main/cppsrc/json/StaticMapLayerConstructor.h \
    $$PWD/main/cppsrc/map/Air.h
