import QtQuick 2.0

Item {
    id: root

    property alias buttonText: text.text
    property alias textSize: text.size

    signal clicked()

    width: 800; height: 96

    Rectangle {
        anchors.fill: parent
        radius: 16
        color: mouseArea.pressed ? "#8E9DAF" : "#FFFFFF"
        opacity: enabled ? 1.0 : 0.3
    }
    PretendardText {
        id: text

        anchors.centerIn: parent
        fontWeight: 700
        size: 44
        opacity: 0.8
        color: mouseArea.pressed ? "#313B47" : "#313B47"
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            root.clicked()
        }
    }
}
