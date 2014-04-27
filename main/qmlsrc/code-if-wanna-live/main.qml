import QtQuick 2.0
import DumbHome 1.0
import "BackgroundBlocks.js" as BackgroundBlocks

Item {
    id: container
    width: 300
    height: 300
    focus: true

    property int direction_up: 0
    property int direction_right: 1
    property int direction_down: 2
    property int direction_left: 3

    property Player player

    Rectangle {
        width: 100
        height: 100
        color: "blue"
        x: 150
        y: 40

        Text {
            text: "up"
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                playerActionsReceiver.onMoveRequested(direction_down);
            }
            onReleased: {
                playerActionsReceiver.onMoveStopRequested();
            }
        }
    }

    Rectangle {
        width: 100
        height: 100
        color: "blue"
        x: 150
        y: 160

        Text {
            text: "down"
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                playerActionsReceiver.onMoveRequested(direction_up);
            }
            onReleased: {
                playerActionsReceiver.onMoveStopRequested();
            }
        }
    }

    Rectangle {
        width: 100
        height: 100
        color: "blue"
        x: 40
        y: 160

        Text {
            text: "left"
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                playerActionsReceiver.onMoveRequested(direction_left);
            }
            onReleased: {
                playerActionsReceiver.onMoveStopRequested();
            }
        }
    }

    Rectangle {
        width: 100
        height: 100
        color: "blue"
        x: 260
        y: 160

        Text {
            text: "right"
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                playerActionsReceiver.onMoveRequested(direction_right);
            }
            onReleased: {
                playerActionsReceiver.onMoveStopRequested();
            }
        }
    }

    Keys.onPressed: {
        switch (event.key) {
        case Qt.Key_Up:
            playerActionsReceiver.onMoveRequested(direction_down);
            break;
        case Qt.Key_Right:
            playerActionsReceiver.onMoveRequested(direction_right);
            break;
        case Qt.Key_Down:
            playerActionsReceiver.onMoveRequested(direction_up);
            break;
        case Qt.Key_Left:
            playerActionsReceiver.onMoveRequested(direction_left);
            break;
        }
    }

    Keys.onReleased: {
        playerActionsReceiver.onMoveStopRequested();
    }

    function createElement(hor, ver, componentUrl) {
        var component = Qt.createComponent(componentUrl);
        if (component.status === Component.Ready) {
            var element = component.createObject(container);
            element.x = hor * 11;
            element.y = ver * 11;
            return element;
        }
    }

    function setUpGraphicalMap() {
        for (var i = 0; i < BackgroundBlocks.size(); i++) {
            BackgroundBlocks.get(i).destroy();
        }
        BackgroundBlocks.clear();

        for (var hor = 0; hor < qmlMapInterface.getWidth(); hor++) {
            for (var ver = 0; ver < qmlMapInterface.getWidth(); ver++) {
                BackgroundBlocks.add(createElement(hor, ver, "BackgroundBlock.qml"));
            }
        }

        player =
                createElement(
                    qmlMapInterface.getPlayerPositionX(),
                    qmlMapInterface.getPlayerPositionX(),
                    "Player.qml");
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

        onPlayerChangePosition: {
            player.x = 11 * x;
            player.y = 11 * y;
        }
    }
}
