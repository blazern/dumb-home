import QtQuick 2.0

Item {
    property int windowWidth: -1
    property int windowHeight: -1
    property int playerWidth: -1

    function isPointAboveTheMainDiagonal(x, y) {
        if (-windowHeight * x + windowWidth * y >= 0) {
            return true;
        } else {
            return false;
        }
    }

    function isPointAboveTheSecondaryDiagonal(x, y) {
        if ((windowHeight * x + windowWidth * y + (-windowHeight * windowWidth)) >= 0) {
            return true;
        } else {
            return false;
        }
    }

    Rectangle {
        id: moveControls
        width: windowWidth
        height: windowHeight

        MouseArea {
            anchors.fill: parent
            onPressed: {
                if (isPointAboveTheSecondaryDiagonal(mouseX, mouseY) &&
                       (isPointAboveTheMainDiagonal(mouseX, mouseY))) {
                   playerActionsReceiver.onMoveRequested(direction_up);
                }

                if (isPointAboveTheSecondaryDiagonal(mouseX, mouseY) &&
                       (!isPointAboveTheMainDiagonal(mouseX, mouseY))) {
                   playerActionsReceiver.onMoveRequested(direction_right);
                }

                if (!isPointAboveTheSecondaryDiagonal(mouseX, mouseY) &&
                       (!isPointAboveTheMainDiagonal(mouseX, mouseY))) {
                   playerActionsReceiver.onMoveRequested(direction_down);
                }

                if (!isPointAboveTheSecondaryDiagonal(mouseX, mouseY) &&
                       (isPointAboveTheMainDiagonal(mouseX, mouseY))) {
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
        width: windowWidth / 5
        height: width
        x: (windowWidth - width + playerWidth) / 2
        y: (windowHeight - height + playerWidth) / 2
        z: 1

        MouseArea {
            anchors.fill: parent
        }
    }
}
