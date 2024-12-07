import QtQuick 2.0

Rectangle {
    id: root

    property string iconPath
    property string pressedColor
    property string normalColor
    property string selectedColor: pressedColor
    property bool selected: false

    signal pressed()
    signal clicked()

    color: selected ? selectedColor :
                      mouseArea.pressed ? pressedColor
                                        : normalColor

    Image {
        anchors.centerIn: parent
        source: iconPath
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onPressed: {
            root.pressed()
        }

        onClicked: {
            selected = true
            root.clicked()
        }
    }
}
