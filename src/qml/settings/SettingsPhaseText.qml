import QtQuick 2.0
import "../component"

Item {
    id: root

    property string number
    property string text
    property bool dimmed: true
    property string color: "#FFFFFF"

    opacity: dimmed ? 0.8 : 1.0

    width: 337; height: 38

    Row {
        spacing: 16
        width: contentWidth
        height: parent.height
        anchors.centerIn: parent

        PretendardText {
            width: 23; height: 24
            size: 20
            anchors.verticalCenter: parent.verticalCenter
            text: root.number
            color: root.color
            font.weight: dimmed ? 400 : 700
        }
        PretendardText {
            width: contentWidth; height: 38
            size: 32
            anchors.verticalCenter: parent.verticalCenter
            text: root.text
            color: root.color
            font.weight: dimmed ? 400 : 700
        }
    }
}
