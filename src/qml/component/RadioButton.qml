import QtQuick 2.0

Item {
    id: root

    property bool checked: false
    property alias text: radioText.text

    signal clicked()

    width: 134; height: 48

    Row {
        anchors.fill: parent
        spacing: 16

        Image {
            width: 48; height: 48
            source: "qrc:/resources/images/" + (checked ? "radio_check" : "radio_uncheck") + ".png"
        }
        PretendardText {
            id: radioText

            width: 74; height: 43
            anchors.verticalCenter: parent.verticalCenter
            fontWeight: checked ? 700 : 400
            size: 36
            color: "#FFFFFF"
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            checked = true

            root.clicked()
        }
    }
}
