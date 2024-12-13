import QtQuick 2.0
import "../component"

Item {
    id: root

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_DATA_LIST: tr(STRING.STR_DATA_LIST)
    property string tr_RESCAN: tr(STRING.STR_RESCAN)
    property string tr_SCANNED_SPACE_DATA: tr(STRING.STR_SCANNED_SPACE_DATA)
    property string tr_DENSITY: tr(STRING.STR_DENSITY)
    property string tr_DATA_UPDATE: tr(STRING.STR_DATA_UPDATE)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_DATA_LIST = tr(STRING.STR_DATA_LIST)
            tr_RESCAN = tr(STRING.STR_RESCAN)
            tr_SCANNED_SPACE_DATA = tr(STRING.STR_SCANNED_SPACE_DATA)
            tr_DENSITY = tr(STRING.STR_DENSITY)
            tr_DATA_UPDATE = tr(STRING.STR_DATA_UPDATE)
        }
    }    

    //-------------------------------------------------------------------------

    property string date: db.scanTime //"2024-11-27"
    property string spaceName: db.scanName //"제목 없음_1"
    property bool isKor: db.language === 0
    Row {
        id: frame_33

        width: 350; height: 16
        x: 960
        y: 98
        spacing: 16

        Row {
            width: 213; height: 24
            spacing: 16

            PretendardText {
                width: 185; height: 24
                fontWeight: 400
                size: 32
                color: "#FFFFFF"
                text: date
            }
            PretendardText {
                width: 12; height: 24
                fontWeight: 400
                size: 32
                color: "#FFFFFF"
                text: "/"
            }
        }
        PretendardText {
            width: 154; height: 24
            fontWeight: 700
            size: 32
            color: "#FFFFFF"
            text: spaceName
        }
    }

    Item {
        id: frame_242

        width: 96; height: 564
        x: 72
        y: 688

        ImageButton {
            id: distance

            width: 96; height: 96

            checkable: true
            sources: [
                "qrc:/resources/images/distance.png",
                "qrc:/resources/images/distance_p.png",
                "qrc:/resources/images/distance_s.png"
            ]
            onClicked: {
                var enable = checked

                db.setMeasurementMode(enable)
            }
        }
    }
    Row {
        width: 419; height: 64
        x: 1779
        y: 182
        spacing: 36

        SmallButton {
            iconPath: "qrc:/resources/images/list.png"
            buttonText: tr_DATA_LIST
            onClicked: {
                mainLoader.source = "qrc:/qml/datalist/DataListMain.qml"
            }
        }
        SmallButtonOutlined {
            width: isKor ? 162+8 : 170+8
            iconPath: "qrc:/resources/images/replay.png"
            buttonText: tr_RESCAN
            onClicked: {
                db.resetView()

                mainLoader.source = ""

                mainLoader.source = "ScanMain.qml"
                modal.load("qrc:/qml/scan/ScanningPopup.qml", 0, 0)
            }
        }
    }
    Item {
        width: 500; height: 693
        x: 1698
        y: 559

        Column {
            id: frame_8209

            width: 500; height: 693
            spacing: 36

            Column {
                id: frame_8208
                width: 500; height: 556
                spacing: 16

                PretendardText {
                    width: 500; height: 38
                    fontWeight: 700
                    size: 32
                    color: "#FFFFFF"
                    text: tr_SCANNED_SPACE_DATA
                }
                Column {
                    id: frame_241
                    width: 500; height: 502

                    Item {
                        anchors.fill: parent

                        Image {
                            id: group_239
                            width: 500; height: 334

                            source: "qrc:/resources/images/image_9.png"
                        }
                        Item {
                            id: group_240
                            width: 500; height: 168
                            anchors.top: group_239.bottom

                            Rectangle {
                                anchors.fill: parent
                                color: "#0C1A2A"
                                opacity: 0.8
                            }
                        }
                        SpaceDataInfo {
                            x: 32
                            y: 350
                        }
                    }
                }

                ButtonLarge {
                    width: 500; height: 100
                    buttonText: tr_DATA_UPDATE
                    onClicked: {
                        db.saveView()
                        db.uploadCurrentView()
                        modal.load("qrc:/qml/datalist/DataTransfer.qml", 0, 0)
                    }
                }
            } //8208
        } //8209
    }
}
