import QtQuick 2.0

Item {
    id: root

    property url iconPath
    property string buttonText

    signal clicked()

    width: 221; height: 64

    Rectangle {
        anchors.fill: parent
        color: "#FFFFFF"
        radius: 16

        Rectangle {
            visible: mouseArea.pressed && root.enabled

            anchors.fill: parent
            color: "#000000"
            opacity: 0.1
        }
    }
    Item {
        id: frame_59
        anchors {
            top: parent.top; topMargin: 8
            bottom: parent.bottom; bottomMargin: 8
            left: parent.left; leftMargin: 20
            right: parent.right; rightMargin: 20
        }
        Row {
            width: Math.max(181, 36+8+_1.contentWidth)
            height: 48
            spacing: 8
            Item {
                width: 36; height: 36
                anchors.verticalCenter: parent.verticalCenter
                Image {
                    anchors.centerIn: parent
                    source: iconPath
                }
            }
            PretendardText {
                id: _1
                width: Math.max(94, contentWidth)
                height: 36
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                fontWeight: 700
                size: 30
                text: buttonText
                color: "#0C1A2A"
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
