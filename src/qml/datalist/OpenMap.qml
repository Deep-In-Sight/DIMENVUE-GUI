import QtQuick 2.0
import "../component"

Item {
    width: 384; height: 216

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_OPEN_MAP: tr(STRING.STR_OPEN_MAP)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_OPEN_MAP = tr(STRING.STR_OPEN_MAP)
        }
    }
    //-------------------------------------------------------------------------

    property int modelIndex: -1

    Rectangle {
        anchors.fill: parent
        radius: 16
        color: "#0C1A2A"
    }
    Column {
        width: 360; height: 192
        x: 12
        y: 12

        Item {
            width: 360; height: 96
            PretendardText {
                anchors.centerIn: parent
                fontWeight: 400
                size: 36
                color: "#FFFFFF"
                text: tr_OPEN_MAP
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    modal.unload()

                    app.openMap(modelIndex)
                    mainLoader.source = "qrc:/qml/scan/ScanMain.qml"
                    app.loadScanComplete()
                }
            }
        }
        Item {
            width: 360; height: 96
            PretendardText {
                anchors.centerIn: parent
                fontWeight: 400
                size: 36
                color: "#FFFFFF"
                text: "------"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("------ clicked")
                    modal.unload()
                }
            }
        }
    }
}
