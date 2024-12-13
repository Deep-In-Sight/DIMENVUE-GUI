import QtQuick 2.0
import "../component"

Rectangle {
    id: root

    property alias text: text.text

    signal selected()

    radius: 16

    states: [
        State {
            name: "normal"
            PropertyChanges {
                target: root
                color: "#0C1A2A"
            }
        },
        State {
            name: "selected"
            PropertyChanges {
                target: root
                color: "#2079FF"
            }
        }
    ]

    InterText {
        id: text

        anchors.centerIn: parent
        fontWeight: 700
        size: 52
        text: "한국어"
        color: "#FFFFFF"
    }
    MouseArea {
        anchors.fill: parent

        onPressed: {
            root.selected()
        }
    }
}
