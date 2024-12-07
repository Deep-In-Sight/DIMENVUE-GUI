import QtQuick 2.0
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0

Item {
    id: root

    width: 2270; height: 1420

    Rectangle {
        anchors.fill: parent

        LinearGradient {
            anchors.fill: parent

            start: Qt.point(0,0)
            end: Qt.point(root.width, root.height)

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#4A678A" }
                GradientStop { position: 0.5; color: "#3F4C5B" }
                GradientStop { position: 1.0; color: "#323C48" }
            }
        }

        Image {
            id: logo
            x: 685
            y: 480
            source: "qrc:/resources/images/Logo_White_1.png"
        }
        Text {
            width: 276; height: 38
            x: 997
            y: 1312
            font.family: "Pretendard"
            font.pixelSize: 32
            color: "#FFFFFF"
            text: "DIMENVUE V 1.8.16"
        }
        SequentialAnimation {
            id: ani
            NumberAnimation {
                target: root
                property: "opacity"
                from: 1.0
                to: 0.0
                duration: 300
            }
            ScriptAction {
                script: {
                    console.log("Intro.qml close()")
                    modal.unload()
                }
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                ani.running = true
            }            
        }
    }
}
