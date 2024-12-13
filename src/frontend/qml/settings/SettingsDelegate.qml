import QtQuick 2.0
import "../component"

Item {
    id: root

    property url iconPath
    property string title
    property bool showArrow: true

    signal clicked()

    width: 2126; height: 160

    Rectangle {
        anchors.fill: parent
        radius: 16
        color: "#313B47"
        opacity: 0.9
    }
    Row {
        width: 223; height: 48
        x: 69
        y: 56
        spacing: 20
        Item {
            width: 48; height: 48
            Image {
                anchors.centerIn: parent
                source: iconPath
            }
        }
        PretendardText {
            width: 165; height: 43
            anchors.verticalCenter: parent.verticalCenter
            fontWeight: 400
            size: 36
            color: "#FFFFFF"
            text: title
        }
    }
    Item {
        visible: showArrow

        width: 744; height: 48
        x: 1296
        y: 58

        Item {
            width: 48; height: 48
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter

            Image {
                anchors.centerIn: parent
                source: "qrc:/resources/images/arrow_back_ios.png"
            }
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.clicked()
        }
    }
}
