import QtQuick 2.0
import "../component"

Item {
    id: root

    property string key
    property string value

    width: 800; height: 170

    Column {
        anchors.fill: parent

        spacing: 17

        PretendardText {
            width: 800; height: 33
            fontWeight: 400
            size: 28
            color: "#FFFFFF"
            opacity: 0.6
            text: key
        }
        Item {
            width: 800; height: 120
            Rectangle {
                anchors.fill: parent
                radius: 16
                color: "#FFFFFF"
                opacity: 0.1
            }
            PretendardText {
                width: 596; height: 48
                x: 30
                anchors.verticalCenter: parent.verticalCenter
                fontWeight: 400
                size: 40
                color: "#FFFFFF"
                text: value
            }
        }
    }
}
