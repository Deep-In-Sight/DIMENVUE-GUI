import QtQuick 2.0

Column {
    id: root

    width: 24
    height: 24

    signal upClicked()
    signal downClicked()

    Item {
        width: 16; height: 12
        Image {
            anchors.centerIn: parent
            source: "qrc:/resources/images/spin_up.png"
            opacity: mouseArea0.pressed ? 0.2 : 1.0
        }
        MouseArea {
            id: mouseArea0
            anchors.fill: parent
            onClicked: {
                root.upClicked()
            }
        }
    }
    Item {
        width: 16; height: 12
        Image {
            anchors.centerIn: parent
            source: "qrc:/resources/images/spin_down.png"
            opacity: mouseArea1.pressed ? 0.2 : 1.0
        }
        MouseArea {
            id: mouseArea1
            anchors.fill: parent
            onClicked: {
                root.downClicked()
            }
        }
    }
}
