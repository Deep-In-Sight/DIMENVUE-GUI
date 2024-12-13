import QtQuick 2.0
import "../component"

Item {
    id: root

    width: 2270; height: 1420

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_DATA_TRANSFER: tr(STRING.STR_DATA_TRANSFER)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_DATA_TRANSFER = tr(STRING.STR_DATA_TRANSFER)
        }
    }
    //-------------------------------------------------------------------------

    property int progress: 0
    property real ratio: progress/100.0
    property bool complete: progress == 100

    Connections {
        target: monitor
        onUploadScanDone: {
            if (value) {
                modal.unload2("DataTransfer")
            }
        }
    }

    Timer {        
        interval: 100
        running: true
        repeat: true

        onTriggered: {
            progress += 5
            if (progress == 100) {
                stop()
                closeTimer.start()
            }
        }
    }
    Timer {
        id: closeTimer

        interval: 1000
        onTriggered: {
            modal.unload()
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "#FFFFFF"

        Rectangle {
            anchors.fill: parent
            color: "#000000"
            opacity: 0.3
        }
    }

    Rectangle {
        width: 1470; height: 1032
        radius: 32
        anchors.centerIn: parent

        color: "#1D2937"

        PretendardText {
            width: 274; height: 72
            x: 597
            y: 240
            fontWeight: 700
            size: 60
            text: tr_DATA_TRANSFER
            color: "#FFFFFF"
            horizontalAlignment: Text.AlignHCenter
        }
    }
    Item {
        id: loadingProgress

        width: 1200; height: 71
        x: 535
        y: 675

        Rectangle {
            id: outline

            width: 1200; height: 30
            y: 41
            radius: height/2
            color: "#364456"
            border.width: 2
            border.color: "#FFFFFF"
        }
        Rectangle {
            id: progressBar

            property int w: 1188 - 18

            width: 18 + w*ratio
            height: 18
            radius: height/2
            y: 47
            x: 6
            color: complete ? "#8E9DAF" : "#FFFFFF"
        }
        PretendardText {
            id: percentText

            width: complete ? 1 : 25; height: 33
            x: 1160
            fontWeight: 400
            size: 28
            text: complete ? "" : "%"
            color: "#FFFFFF"
        }
        PretendardText {
            width: 19; height: 48
            //anchors.right: percentText.left
            x: complete ? 977 :
                          progress < 10 ? 1130 :
                                          1110
            anchors.bottom: percentText.bottom
            fontWeight: 700
            size: 40
            text: complete ? "Completed" : progress
            color: complete ? "#8E9DAF" : "#FFFFFF"
            //horizontalAlignment: Text.AlignRight
        }
    }
}
