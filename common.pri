QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

QT += qml quick widgets

SOURCES += \
    $$PWD/main/cppsrc/PlayerActionsQmlReceiver.cpp \
    $$PWD/main/cppsrc/logic/Map.cpp \
    $$PWD/main/cppsrc/logic/Player.cpp \
    $$PWD/main/cppsrc/QmlMapInterface.cpp \
    $$PWD/main/cppsrc/MapObjectQmlWrapper.cpp \
    $$PWD/main/cppsrc/logic/StaticMapLayer.cpp \
    $$PWD/main/cppsrc/logic/DynamicMapLayer.cpp \
    $$PWD/main/cppsrc/json/JsonMapParser.cpp \
    $$PWD/main/cppsrc/json/StaticMapLayerConstructor.cpp \
    $$PWD/main/cppsrc/logic/MapPhysics.cpp \
    $$PWD/main/cppsrc/logic/World.cpp \
    $$PWD/main/cppsrc/logic/MapToolKit.cpp \
    $$PWD/main/cppsrc/logic/util/StairsChecker.cpp \
    $$PWD/main/cppsrc/gen/StaticMapLayerGenerator.cpp \
    $$PWD/main/cppsrc/gen/RoomGenerator.cpp \
    $$PWD/main/cppsrc/gen/StoreyGenerator.cpp \
    $$PWD/main/cppsrc/util/LineDivider.cpp

HEADERS += \
    $$PWD/main/cppsrc/PlayerActionsQmlReceiver.h \
    $$PWD/main/cppsrc/logic/Map.h \
    $$PWD/main/cppsrc/logic/Player.h \
    $$PWD/main/cppsrc/logic/Mover.h \
    $$PWD/main/cppsrc/logic/DynamicMapObject.h \
    $$PWD/main/cppsrc/logic/MapPhysicsListener.h \
    $$PWD/main/cppsrc/QmlMapInterface.h \
    $$PWD/main/cppsrc/logic/StaticMapObject.h \
    $$PWD/main/cppsrc/MapObjectQmlWrapper.h \
    $$PWD/main/cppsrc/logic/StaticMapLayer.h \
    $$PWD/main/cppsrc/logic/DynamicMapLayer.h \
    $$PWD/main/cppsrc/logic/DynamicMapObjectGeometry.h \
    $$PWD/main/cppsrc/json/JsonObjectParser.h \
    $$PWD/main/cppsrc/json/JsonMapParser.h \
    $$PWD/main/cppsrc/json/StaticMapLayerConstructor.h \
    $$PWD/main/cppsrc/logic/MapPhysics.h \
    $$PWD/main/cppsrc/logic/World.h \
    $$PWD/main/cppsrc/logic/Movement.h \
    $$PWD/main/cppsrc/logic/MapToolKit.h \
    $$PWD/main/cppsrc/logic/util/StairsChecker.h \
    $$PWD/main/cppsrc/gen/StaticMapLayerGenerator.h \
    $$PWD/main/cppsrc/gen/RoomGenerator.h \
    $$PWD/main/cppsrc/gen/StoreyGenerator.h \
    $$PWD/main/cppsrc/util/LineDivider.h \
    $$PWD/main/cppsrc/gen/Minimums.h
