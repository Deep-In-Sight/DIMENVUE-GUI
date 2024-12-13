import QtQuick 2.0
import "../component"

Item {
    id: root

    property string iconPath
    property string buttonText
    property string bgColor: !enabled ? "transparent" :
                                        mouseArea.pressed ? Qt.rgba(0,0,0,0.1) :
                                                            Qt.rgba(1,1,1,0.1)

    signal clicked()

    width: 192; height: 64
    Rectangle {
        id: bg

        anchors.fill: parent
        radius: 16
        color: bgColor
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
            anchors.verticalCenter: parent.verticalCenter
            spacing: 8

            Item {
                width: 32; height: 32
                anchors.verticalCenter: parent.verticalCenter
                Image {
                    anchors.centerIn: parent
                    source: iconPath
                    opacity: root.enabled ? 1.0 : 0.5
                }
            }
            PretendardText {
                width: 83; height: 33
                anchors.verticalCenter: parent.verticalCenter
                fontWeight: 400
                size: 28
                color: "#FFFFFF"
                text: buttonText
                opacity: root.enabled ? 1.0 : 0.5
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
