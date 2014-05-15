import QtQuick 2.0

Item {
    property int controlsSize: 100
    property int controlsMargin: 10
    property color controlsColor: "blue"

    Rectangle {
        id: up
        width: controlsSize
        height: controlsSize
        color: "#0500ff"
        x: controlsSize + controlsMargin
        y: 0

        Text {
            anchors.centerIn: parent
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
        id: down
        width: controlsSize
        height: controlsSize
        color: controlsColor
        anchors.top: up.bottom
        anchors.topMargin: controlsMargin
        anchors.left: up.left

        Text {
            anchors.centerIn: parent
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
        width: controlsSize
        height: controlsSize
        color: controlsColor
        anchors.right: down.left
        anchors.rightMargin: controlsMargin
        anchors.top: down.top

        Text {
            anchors.centerIn: parent
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
        width: controlsSize
        height: controlsSize
        color: controlsColor
        anchors.left: down.right
        anchors.leftMargin: controlsMargin
        anchors.top: down.top

        Text {
            anchors.centerIn: parent
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
}
