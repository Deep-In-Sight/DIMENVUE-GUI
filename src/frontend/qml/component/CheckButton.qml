import QtQuick 2.0

Item {
    id: root

    property bool check: false
    property var sources: [
        "qrc:/resources/images/checked.png",
        "qrc:/resources/images/unchecked.png"
    ]

    signal clicked()

    width: 48; height: 48

    Image {
        anchors.fill: parent
        source: check ? sources[0] : sources[1]
    }
    MouseArea {
        id: mouseArea

        anchors.fill: parent
        onClicked: {
            root.clicked()
        }
    }
}
