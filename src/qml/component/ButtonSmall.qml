import QtQuick 2.0
import "../component"

Item {
    id: root

    property string iconPath
    property string buttonText

    signal clicked()

    Rectangle {
        id: rect

        anchors.fill: parent
        radius: 16
        color: mouseArea.pressed ? "#FFFFFF" : Qt.rgba(1,1,1,0.3)
    }

    Item {
        anchors {
            left: parent.left; leftMargin: 24
            right: parent.right; rightMargin: 24
            top: parent.top; topMargin: 8
            bottom: parent.bottom; bottomMargin: 8
        }
        Row {
            width: 144; height: 48
            spacing: 8

            Item {
                width: 32; height: 32
                anchors.verticalCenter: parent.verticalCenter
                Image {
                    anchors.centerIn: parent
                    source: iconPath
                }
            }
            PretendardText {
                width: 83; height: 33
                anchors.verticalCenter: parent.verticalCenter
                fontWeight: 400
                size: 28
                color: "#0C1A2A"
                text: buttonText
            }
        }
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            root.clicked()
        }
    }
}
