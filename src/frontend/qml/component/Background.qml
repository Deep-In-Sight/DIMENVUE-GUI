import QtQuick 2.0
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: root

    property int type: 0    //0: gradient
                            //1: solid #0C1A2A

    LinearGradient {
        visible: type == 0

        anchors.fill: parent

        start: Qt.point(0,0)
        end: Qt.point(root.width, root.height)

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#4A678A" }
            GradientStop { position: 0.5; color: "#3F4C5B" }
            GradientStop { position: 1.0; color: "#323C48" }
        }
    }
    Rectangle {
        visible: type == 1

        anchors.fill: parent

        color: "#0C1A2A"
    }
}
