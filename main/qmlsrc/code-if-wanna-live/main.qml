import QtQuick 2.0
import DumbHome 1.0
import "MapObjects.js" as MapObjects

Item {
    id: container
    width: 500
    height: 500
    focus: true


    property int direction_up: 0
    property int direction_right: 1
    property int direction_down: 2
    property int direction_left: 3

    property MapObject player: MapObject {}
    property int oldWindowWidth: width
    property int oldWindowHeight: height

    property int pressedKeysCount: 0

    onWidthChanged: {
        for (var index = 0; index < MapObjects.size(); index++) {
            var mapObject = MapObjects.get(index);
            mapObject.x += (width - oldWindowWidth)/2;
        }
        oldWindowWidth = width;
    }

    onHeightChanged: {
        for (var index = 0; index < MapObjects.size(); index++) {
            var mapObject = MapObjects.get(index);
            mapObject.y += (height - oldWindowHeight)/2;
        }
        oldWindowHeight = height;
    }


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
            if (mapObject.id === qmlMapInterface.getPlayerId()) {
                player.mapObjectId = mapObject.id;
                player.x = mapObject.x;
                player.y = mapObject.y;
            }
        }

        for (index = 0; index < MapObjects.size(); index++) {
            mapObject = MapObjects.get(index);
            mapObject.x += (container.width/2 - player.x);
            mapObject.y += (container.height/2 - player.y);
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
            if (id === player.mapObjectId) {
                for (var index = 0; index < MapObjects.size(); index++) {
                    var mapObject = MapObjects.get(index);
                    var xOffset = x - player.x
                    var yOffset = y - player.y;
                    if (mapObject.mapObjectId !== id) {
                        //Move Right/Left
                        if(xOffset != 0){
                            mapObject.x -= xOffset;
                        }

                        //Move Up/Down
                        if(yOffset != 0){
                            mapObject.y -= yOffset;
                        }
                    }
                }
                player.x = x;
                player.y = y;
            }
        }
    }
}
