import QtQuick 2.0

Item {
    anchors.left: parent.left
    anchors.right: parent.right
    height: 66

    Row {
        width: 269 //HUG
        height: 32
        x: 28
        y: 17
        spacing: 4

        SSD {
            anchors.verticalCenter: parent.verticalCenter
        }
        Item {
            width: 236
            height: 32

            Item {
                width: 216
                height: 34

                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: parent.height

                    PretendardText {
                        width: contentWidth; height: parent.height
                        verticalAlignment: Qt.AlignVCenter
                        fontWeight: 700
                        size: 28
                        color: "#DFDFDF"
                        text: db.usageTB.toFixed(2)
                    }
                    PretendardText {
                        width: contentWidth; height: contentHeight
                        verticalAlignment: Qt.AlignVCenter
                        fontWeight: 400
                        size: 28
                        color: "#DFDFDF"
                        text: "TB"
                    }
                    PretendardText {
                        width: contentWidth
                        height: parent.height
                        verticalAlignment: Qt.AlignVCenter
                        fontWeight: 400
                        size: 28
                        color: "#DFDFDF"
                        text: " / " + db.totalTB.toFixed(2) + "TB"
                    }
                }
            }
        }
    }

    Row {
        x: 1761
        y: 15
        width: 481
        height: 36
        spacing: 40

        Item {
            id: local_see
            width: 32
            height: 32
            Image {
                anchors.centerIn: parent
                source: "qrc:/resources/images/TitleBar/local_see.png"
            }
        }
        Item {
            id: wifi
            width: 32
            height: 32
            Image {
                anchors.centerIn: parent
                source: db.wifiConnected ? "qrc:/resources/images/TitleBar/wifi_off.png"
                                         : "qrc:/resources/images/TitleBar/wifi_off.png"
            }
        }
        Row {
            width: 107
            height: 34
            spacing: 16

            Item {
                id: battery
                width: 32
                height: 32
                Image {
                    anchors.centerIn: parent
                    source: "qrc:/resources/images/TitleBar/battery2.png"
                }
            }
            Item {
                width: 59
                height: 34
                PretendardText {
                    anchors.centerIn: parent
                    size: 28
                    text: db.batteryCharge + "%"
                    color: "#F5F5F5"
                }
            }
            Row {
                width: 190
                height: 36
                spacing: 28

                PretendardText {
                    width: 126
                    height: 34
                    text: db.time
                    size: 28
                    color: "#F5F5F5"
                }
                Item {
                    width: 36
                    height: 36
                    Image {
                        anchors.centerIn: parent
                        source: "qrc:/resources/images/TitleBar/power.png"
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            modal.load("qrc:/qml/popup/PowerOffPopup.qml", 0, 0)
                        }
                    }
                }
            }
        }
    }
}
