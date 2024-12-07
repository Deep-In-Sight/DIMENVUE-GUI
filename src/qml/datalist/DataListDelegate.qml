import QtQuick 2.0
import "../component"

Item {
    id: root

    property bool selected: false
    property url openMapUrl: "qrc:/qml/datalist/OpenMap.qml"

    width: 2126; height: 132

    function setModelIndex(item) {
        item.modelIndex = index

        console.log("item.modelIndex: " + index)
    }

    function openPopup(y) {
        modal.load2(openMapUrl, 1714, y+8, setModelIndex)
    }

    Connections {
        target: modal
        onModalUnloaded: {
            if (url == openMapUrl) {
                selected = false
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        radius: 16
        color: "#313B47"
        opacity: 0.9
    }
    Item {
        width: 2053; height: 100
        x: 36
        y: 16

        Item {
            width: 1945; height: 100

            Row {
                id: row0

                width: 162; height: 48
                anchors.verticalCenter: parent.verticalCenter

                spacing: 24

                CheckButton {
                    check: checked
                    onClicked: {
                        console.log(name + "[0] CheckButton.checked: " + checked)
                        checked = !checked
                        console.log(name + "[1] CheckButton.checked: " + checked)
                    }
                }

                PretendardText {
                    width: 90; height: 43
                    fontWeight: 700
                    size: 36
                    color: "#FFFFFF"
                    text: index
                }
            }
            Row {
                id: row1

                width: 1783; height: 100
                spacing: 60
                anchors.left: row0.right

                Rectangle {
                    width: 180; height: 100
                    radius: 4
                    color: "transparent"
                    border.width: 1
                    border.color: "#313B47"

                    Image {
                        anchors.centerIn: parent
                        source: image
                    }
                }
                PretendardText {
                    width: 925; height: 43
                    anchors.verticalCenter: parent.verticalCenter

                    fontWeight: 400
                    size: 36
                    color: "#FFFFFF"
                    text: name
                }
                Row {
                    width: 126; height: 50
                    spacing: 4
                    anchors.verticalCenter: parent.verticalCenter

                    PretendardText {
                        width: Math.max(77, contentWidth); height: 43
                        anchors.verticalCenter: parent.verticalCenter

                        fontWeight: 700
                        size: 36
                        color: "#FFFFFF"
                        text: area.toFixed(1) //areaText
                    }
                    Item {
                        width: 45; height: 50
                        Image {
                            anchors.centerIn: parent
                            source: "qrc:/resources/images/group_90.png"
                        }
                    }
                }
                PretendardText {
                    width: 356; height: 43
                    anchors.verticalCenter: parent.verticalCenter

                    fontWeight: 400
                    size: 36
                    color: "#FFFFFF"
                    text: time
                }
            }
        }
        Item {
            id: move_vert
            width: 48; height: 48
            x: 1990
            y: 26

            Image {
                width: 8; height: 32
                x: 20
                y: 8
                source: "qrc:/resources/images/move_vert.png"
                opacity: selected ? 0.5 : 1.0
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    selected = true
                    var pt = move_vert.mapToItem(mainLoader, 0, 0)
                    var y = pt.y
                    openPopup(y)
                }
            }
        }
    }
}
