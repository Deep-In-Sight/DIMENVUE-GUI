import QtQuick 2.0

Rectangle {
    id: root

    property bool on: false

    width: 90; height: 60; radius: 30
    color: on ? "#2079FF" : "#1D2937"

    Rectangle {
        width: 48; height: 48; radius: 24
        x: root.on ? 36 : 6
        y: 6
        color: on ? "#FFFFFF" : "#364456"

        MouseArea {
            anchors.fill: parent
            onClicked: root.on = !root.on
        }
    }
}
