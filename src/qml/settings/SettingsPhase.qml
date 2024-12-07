import QtQuick 2.0
import "../component"

Item {
    id: root

    property int phase: 0

    Rectangle {
        anchors.fill: parent
        color: "#FFFFFF"
        opacity: 0.1
        radius: 16
    }

    Row {
        anchors.fill: parent
        anchors.leftMargin: 40
        anchors.rightMargin: 40
        anchors.topMargin: 20
        anchors.bottomMargin: 20
        spacing: 10

        SettingsPhaseText {
            width: 337; height: 38
            number: "01"
            text: "Language Selection"
            dimmed: 0 !== phase
        }
        Image {
            source: "qrc:/resources/images/arrow.png"
            anchors.verticalCenter: parent.verticalCenter
        }

        SettingsPhaseText {
            width: 286; height: 38
            number: "02"
            text: "Network Settins"
            dimmed: 1 !== phase
        }
        Image {
            source: "qrc:/resources/images/arrow.png"
            anchors.verticalCenter: parent.verticalCenter
        }
        SettingsPhaseText {
            width: 151; height: 38
            number: "03"
            text: "Log-in"
            dimmed: 2 !== phase
        }
    }
}
