import QtQuick 2.0

Item {
    property int windowWidth: -1
    property int windowHeight: -1
    property int controlsMargin: 10
    property color controlsColor: "blue"

    Rectangle {
        id: moveControls
        width: windowWidth
        height: windowHeight
        x: 0
        y: 0

        MouseArea {
            anchors.fill: parent
            onPressed: {
                if (((windowHeight * mouseX + windowWidth * mouseY + (-windowHeight * windowWidth)) >= 0) &&
                       (-windowHeight * mouseX + windowWidth * mouseY >= 0)){
                   playerActionsReceiver.onMoveRequested(direction_up);
                }

                if (((windowHeight * mouseX + windowWidth * mouseY + (-windowHeight * windowWidth)) >= 0) &&
                       (-windowHeight * mouseX + windowWidth * mouseY <= 0)){
                   playerActionsReceiver.onMoveRequested(direction_right);
                }

                if (((windowHeight * mouseX + windowWidth * mouseY + (-windowHeight * windowWidth)) <= 0) &&
                       (-windowHeight * mouseX + windowWidth * mouseY <= 0)){
                   playerActionsReceiver.onMoveRequested(direction_down);
                }

                if (((windowHeight * mouseX + windowWidth * mouseY + (-windowHeight * windowWidth)) <= 0) &&
                       (-windowHeight * mouseX + windowWidth * mouseY >= 0)){
                   playerActionsReceiver.onMoveRequested(direction_left);
                }

            }
            onReleased: {
                playerActionsReceiver.onMoveStopRequested();
            }
        }
    }

    Rectangle {
        id: actionControls
        width: windowWidth/3
        height: windowHeight/3
        x: windowWidth*0.333
        y: windowHeight*0.333
        z: 1
        color: controlsColor

        MouseArea {
            anchors.fill: parent
        }
    }
}
