import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: root

    width: 500; height: 100

    property alias buttonText: text.text

    signal clicked()

    Gradient {
        id: disableGradient
        GradientStop{ position: 0.0; color: "#1AFFFFFF" }
        GradientStop{ position: 1.0; color: "#1AFFFFFF" }
    }
    Gradient {
        id: enableGradient
        GradientStop{ position: 0.0; color: "#7F2079FF" }
        GradientStop{ position: 1.0; color: "#CC2079FF" }
    }
    Gradient {
        id: pressGradient
        GradientStop{ position: 0.0; color: "#7F2079FF" }
        GradientStop{ position: 0.5; color: "#CC2079FF" }
        GradientStop{ position: 1.0; color: "#4D134999" }
    }

    state: root.enabled ?
               mouseArea.pressed ? "pressed"
                                 : "enabled"
                        : "disabled"
    states: [
        State {
            name: "disabled"
            PropertyChanges {
                target: bg
                gradient: disableGradient
            }
        },
        State {
            name: "enabled"
            PropertyChanges {
                target: bg
                gradient: enableGradient
            }
        },
        State {
            name: "pressed"
            PropertyChanges {
                target: bg
                gradient: pressGradient
            }
        }
    ]

    LinearGradient {
        id: outline

        visible: root.state != "disabled"

        width: parent.width-6; height: parent.height-6
        anchors.centerIn: parent
        start: Qt.point(0,0)
        end: Qt.point(width, height)
    }
    Rectangle {
        id: bg

        anchors.fill: parent
        radius: 16
        border.width: 3
        border.color: "#FFFFFF"
        color: "transparent"

        PretendardText {
            id: text

            anchors.centerIn: parent
            opacity: root.enabled ? 1.0 : 0.5
            fontWeight: 700
            size: 44
            color: "#FFFFFF"
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
