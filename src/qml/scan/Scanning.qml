import QtQuick 2.0
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0
import "../component"

Item {
    id: root

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_COMPLETE_THE_SCAN: tr(STRING.STR_COMPLETE_THE_SCAN)
    property string tr_SPEED_CHECK_0: tr(STRING.STR_SPEED_CHECK_0)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_COMPLETE_THE_SCAN = tr(STRING.STR_COMPLETE_THE_SCAN)
            tr_SPEED_CHECK_0 = tr(STRING.STR_SPEED_CHECK_0)
        }
    }
    //-------------------------------------------------------------------------


    Item {
        width: 2270; height: 79
        y: 66
        LinearGradient {
            anchors.fill: parent
            start: Qt.point(0, height/2)
            end: Qt.point(width, height/2)

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#00000000" }
                GradientStop { position: 0.5; color: "#FF2A2A2A" }
                GradientStop { position: 1.0; color: "#00000000" }
            }
        }
        PretendardText {
            anchors.centerIn: parent
            fontWeight: 400
            size: 44
            color: "#FFFFFF"
            text: tr_SPEED_CHECK_0
        }
    }

    Rectangle {
        width: 80; height: 80
        x: 2118
        y: 181
        radius: 16
        border.width: 2
        color: "transparent"
        border.color: "#FFFFFF"

        Image {
            width: 48; height: 48
            anchors.centerIn: parent
            source: "qrc:/resources/images/home.png"
        }
    }
    Column {
        id: frame_214
        width: 500; height: 591
        spacing: 36
        x: 1698
        y: 661

        Column {
            id: frame_28
            width: 500; height: 454
            spacing: 16

            PretendardText {
                width: 137; height: 38
                fontWeight: 700
                size: 32
                text: "Mini Map"
                color: "#FFFFFF"
            }
            Rectangle {
                width: 500; height: 400
                radius: 16
                color: "transparent"
                border.color: "#8E9DAF"
                Circle {
                    anchors.centerIn: parent
                    size: 16
                    color: "#2079FF"
                    border.width: 2
                    border.color: "#25FCF4"
                }
            }
        }
        ButtonLarge {
            width: 500; height: 100
            buttonText: tr_COMPLETE_THE_SCAN
            onClicked: {
                console.log(buttonText + " pressed.")

                if (db.isLowDensity()) {
                    enableBlur()
                    modal.load("qrc:/qml/scan/ScanningLowDensityPopup.qml", 0, 0)
                } else {
                    loader.source = "ScanComplete.qml"
                    popupLoader.source = "ScanCompleteLoading.qml"
                }
            }
        }
    }
}
