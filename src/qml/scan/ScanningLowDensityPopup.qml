import QtQuick 2.0
import "../component"

Item {
    id: root

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_SCAN_COMPLETE: tr(STRING.STR_SCAN_COMPLETE)
    property string tr_SCAN_COMPLETE_LOW_DENSITY_0: tr(STRING.STR_SCAN_COMPLETE_LOW_DENSITY_0)
    property string tr_SCAN_COMPLETE_LOW_DENSITY_1: tr(STRING.STR_SCAN_COMPLETE_LOW_DENSITY_1)
    property string tr_SCAN_COMPLETE_OK: tr(STRING.STR_SCAN_COMPLETE_OK)
    property string tr_SCAN_COMPLETE_CANCEL: tr(STRING.STR_SCAN_COMPLETE_CANCEL)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_SCAN_COMPLETE = tr(STRING.STR_SCAN_COMPLETE)
            tr_SCAN_COMPLETE_LOW_DENSITY_0 = tr(STRING.STR_SCAN_COMPLETE_LOW_DENSITY_0)
            tr_SCAN_COMPLETE_LOW_DENSITY_1 = tr(STRING.STR_SCAN_COMPLETE_LOW_DENSITY_1)
            tr_SCAN_COMPLETE_OK = tr(STRING.STR_SCAN_COMPLETE_OK)
            tr_SCAN_COMPLETE_CANCEL = tr(STRING.STR_SCAN_COMPLETE_CANCEL)
        }
    }
    //-------------------------------------------------------------------------

    Item {
        width: 1470; height: 1032
        x: 400
        y: 194

        Rectangle {
            anchors.fill: parent
            radius: 32
            color: "#1D2937"
        }
        Column {
            id: frame_252
            width: 1062; height: 161
            x: 204
            y: 120
            spacing: 32

            PretendardText {
                width: 104; height: 33
                anchors.horizontalCenter: parent.horizontalCenter
                color: "#FFFFFF"
                fontWeight: 700
                size: 28
                text: tr_SCAN_COMPLETE
                horizontalAlignment: Text.AlignHCenter
            }
            PretendardText {
                width: 1062; height: 96
                //text: "스캔된 공간 중 밀도가 부족한 부분이 있습니다.\n그래도 스캔을 완료 하시겠습니까?"
                text: tr_SCAN_COMPLETE_LOW_DENSITY_0 + "\n" + tr_SCAN_COMPLETE_LOW_DENSITY_1
                color: "#FFFFFF"
                fontWeight: 400
                size: 40
                opacity: 0.8
                horizontalAlignment: Text.AlignHCenter
            }
        }
        Image {
            width: 707; height: 474
            x: 382
            y: 315
            source: "qrc:/resources/images/group_83.png"
        }
        Row {
            width: 760; height: 96
            x: 355
            y: 835
            spacing: 40

            MadalButton {
                buttonText: tr_SCAN_COMPLETE_CANCEL
                onClicked: {
                    modal.unload()
                    disableBlur()
                }
            }
            MadalButton {
                buttonText: tr_SCAN_COMPLETE_OK
                onClicked: {
                    modal.unload()
                    disableBlur()

                    app.loadScanComplete()

                    modal.load("qrc:/qml/scan/ScanCompleteLoading.qml", 0, 0)
                }
            }
        }
    }
}
