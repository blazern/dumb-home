import QtQuick 2.0
import DumbHome 1.0
import "MapObjects.js" as MapObjects

Item {
    id: container
    width: 300
    height: 300
    focus: true

    property int direction_up: 0
    property int direction_right: 1
    property int direction_down: 2
    property int direction_left: 3

    property int pressedKeysCount: 0

    SensorControls {
    }

    Keys.onPressed: {
        switch (event.key) {
        case Qt.Key_Up:
            pressedKeysCount++;
            playerActionsReceiver.onMoveRequested(direction_down);
            break;
        case Qt.Key_Right:
            pressedKeysCount++;
            playerActionsReceiver.onMoveRequested(direction_right);
            break;
        case Qt.Key_Down:
            pressedKeysCount++;
            playerActionsReceiver.onMoveRequested(direction_up);
            break;
        case Qt.Key_Left:
            pressedKeysCount++;
            playerActionsReceiver.onMoveRequested(direction_left);
            break;
        }
    }

    Keys.onReleased: {
        pressedKeysCount--;
        if (pressedKeysCount == 0) {
            playerActionsReceiver.onMoveStopRequested();
        }
    }

    function createElementFrom(mapObject) {
        var component = Qt.createComponent("MapObject.qml");
        if (component.status === Component.Ready) {
            var element = component.createObject(container);
            element.x = mapObject.x;
            element.y = mapObject.y;
            element.width = mapObject.width;
            element.height = mapObject.height;
            element.color = mapObject.color;
            element.mapObjectId = mapObject.id;
            return element;
        }
    }

    function setUpGraphicalMap() {
        for (var i = 0; i < MapObjects.size(); i++) {
            MapObjects.get(i).destroy();
        }
        MapObjects.clear();

        for (var index = 0; index < qmlMapInterface.getObjectsCount(); index++) {
            var mapObject = qmlMapInterface.getMapObject(index);
            MapObjects.add(createElementFrom(mapObject));
        }
    }

    Component.onCompleted: {
        if (qmlMapInterface.isMapSetUp()) {
            setUpGraphicalMap();
        }
    }

    QmlMapInterface {
        id: qmlMapInterface
        objectName: "qmlMapInterface"
        onMapSetUp: {
            setUpGraphicalMap();
        }

        onObjectChangedPosition: {
            for (var index = 0; index < MapObjects.size(); index++) {
                var mapObject = MapObjects.get(index);

                if (mapObject.mapObjectId === id) {
                    mapObject.x = x;
                    mapObject.y = y;
                    return;
                }
            }
        }
    }
}
