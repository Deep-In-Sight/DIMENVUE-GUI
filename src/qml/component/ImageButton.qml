import QtQuick 2.0

Item {
    id: root

    property var sources    //0: normal
                            //1: pressed
                            //2: selected

    property bool checkable: false
    property bool checked: false

    property alias enableMouseArea: mouseArea.enabled

    signal clicked()

    state: "0"
    states: [
        State {
            name: "0"
            PropertyChanges {
                target: image; source: sources[0]
            }
        },
        State {
            name: "1"
            PropertyChanges {
                target: image; source: sources[1]
            }
        },
        State {
            name: "2"
            PropertyChanges {
                target: image; source: sources[2]
            }
        }
    ]
    Image {
        id: image
    }
    MouseArea {
        id: mouseArea

        anchors.fill: parent

        onPressed: {
            root.state = "1"
        }
        onClicked: {
            if (checkable) {
                checked = !checked
                root.state = checked ? "2" : "0"
            } else {
                root.state = "2"
            }
            root.clicked()
        }
    }
}
