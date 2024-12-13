import QtQuick 2.0
import "../component"

Column {
    id: frame_8196

    width: 800; height: 170
    spacing: 17

    property bool wifiOn: wifiOn.on

    PretendardText {
        width: parent.width; height: 33
        opacity: 0.6
        fontWeight: 400
        size: 28
        text: "WI-FI connection"
        color: "#FFFFFF"
    }
    Rectangle {
        width: parent.width; height: 120
        radius: 16
        color: "#0C1A2A"

        Row {
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter

            spacing: 279

            Row {
                id: frame106

                width: 384; height: 40
                spacing: 24
                anchors.verticalCenter: parent.verticalCenter

                Image {
                    source: "qrc:/resources/images/wifi_3.png"
                    anchors.verticalCenter: parent.verticalCenter
                }
                PretendardText {
                    width: 300; height: 38
                    anchors.verticalCenter: parent.verticalCenter
                    fontWeight: 400
                    size: 36
                    color: "#FFFFFF"
                    text: "Wi-Fi"
                }
            }
            ToggleButton {
                id: wifiOn
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
