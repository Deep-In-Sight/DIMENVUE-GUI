import QtQuick 2.0

Item {
    id: root

    property alias buttonText: text.text

    width: 800; height: 96

    Rectangle {
        anchors.fill: parent
        radius: 16
        //color: "#FFFFFF"
        //opacity: mouseArea.pressed ? 1.0 : 0.3
        gradient: Gradient {
            GradientStop { position: 0.0; color: Qt.rgba(0.125,0.475,1.0,0.5) }
            GradientStop { position: 1.0; color: Qt.rgba(0.125,0.475,1.0,0.8) }
        }
    }
    PretendardText {
        id: text

        anchors.centerIn: parent
        fontWeight: 700
        size: 44
        opacity: 0.8
        color: "#FFFFFF"
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }
}
