import QtQuick 2.0
import "../component"

Item {
    id: root

    width: 694; height: 482

    property url openMapUrl: "qrc:/qml/datalist/OpenMap.qml"

    function setModelIndex(item) {
        item.modelIndex = index

        console.log("item.modelIndex: " + index)
    }

    function openPopup(x, y) {
        modal.load2(openMapUrl, x/*1714*/, y+8, setModelIndex)
    }

    Item {
        Rectangle {
            width: 694; height: 482
            radius: 16
            color: "#313B47"

            Image {
                source: image
            }
        }
        CheckButton {
            x: 33
            y: 36
            check: checked
            onClicked: {
                checked = !checked
            }
        }

        Row {
            width: 404; height: 34
            x: 80
            y: 412
            spacing: 16

            PretendardText {
                width: 277; height: 34
                fontWeight: 400
                size: 28
                color: "#8E9DAF"
                text: time
            }
            Rectangle {
                anchors.verticalCenter: parent.verticalCenter
                width: 2; height: 30
                color: "#3A4D63"
            }
            Row {
                width: 95; height: 34
                spacing: 4
                PretendardText {
                    width: Math.max(60, contentWidth); height: 34
                    fontWeight: 700
                    size: 28
                    text: area.toFixed(1)
                    color: "#FFFFFF"
                }
                Item {
                    width: 31; height: 34
                    Image {
                        anchors.centerIn: parent
                        source: "qrc:/resources/images/group_90.png"
                    }
                }
            }
        }
        PretendardText {
            width: 556; height: 43
            x: 92
            y: 362
            fontWeight: 400
            size: 36
            color: "#FFFFFF"
            text: name
        }
        PretendardText {
            x: 28
            y: 362
            width: 41; height: 43
            fontWeight: 700
            size: 36
            color: "#FFFFFF"
            text: index
        }
        Item {
            id: move_vert

            width: 46; height: 48
            x: 616
            y: 360
            Image {
                anchors.centerIn: parent
                source: "qrc:/resources/images/move_vert.png"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    //selected = true
                    var pt = move_vert.mapToItem(mainLoader, 0, 0)
                    var x = pt.x - 384
                    var y = pt.y
                    openPopup(x, y)
                }
            }
        }
    }
}
