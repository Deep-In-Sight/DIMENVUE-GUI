import QtQuick 2.0

Item {
    id: root

    property alias buttonText: text.text

    signal clicked()

    width: 360; height: 96

    Rectangle {
        anchors.fill: parent
        radius: 16
        color: mouseArea.pressed ? "#FFFFFF" : "#1D2937"
        border.color: mouseArea.pressed ? "#FFFFFF" : "darkgray"
    }
    PretendardText {
        id: text

        anchors.centerIn: parent
        fontWeight: mouseArea.pressed ? 700 : 400
        size: 36

        color: mouseArea.pressed ? "#1D2937" : "#FFFFFF"
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            root.clicked()
        }
    }
}
