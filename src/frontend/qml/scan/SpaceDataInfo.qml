import QtQuick 2.0
import "../component"

Item {
    id: root

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_DENSITY: tr(STRING.STR_DENSITY)
    property string tr_AREA: tr(STRING.STR_AREA)
    property string tr_SCAN_DATETIME: tr(STRING.STR_SCAN_DATETIME)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_DENSITY = tr(STRING.STR_DENSITY)
            tr_AREA = tr(STRING.STR_AREA)
            tr_SCAN_DATETIME = tr(STRING.STR_SCAN_DATETIME)
        }
    }
    //-------------------------------------------------------------------------

    width: 297; height: 136

    property real spaceArea: 0.0
    property real density: 0.0

    Column {
        anchors.fill: parent
        spacing: 14

        Row {
            id: frame_240

            width: 258; height: 61
            spacing: 60

            Item {
                width: 94; height: 61
                PretendardText {
                    width: 41; height: 24
                    fontWeight: 700
                    size: 20
                    color: "#758395"
                    text: tr_AREA
                }
                PretendardText {
                    id: area
                    y: 23
                    size: 32
                    fontWeight: Font.Regular
                    text: root.spaceArea
                    color: "#FFFFFF"
                }
                Image {
                    width: 32; height: 38
                    x: 61
                    y: 23
                    source: "qrc:/resources/images/group_90.png"
                }
            }
            Item {
                width: 104; height: 61
                PretendardText {
                    width: 41; height: 24
                    fontWeight: Font.Bold
                    size: 20
                    color: "#758395"
                    text: tr_DENSITY
                }
                PretendardText {
                    id: densityText
                    y: 23
                    size: 32
                    fontWeight: Font.Regular
                    text: root.density
                    color: "#FFFFFF"
                }
                PretendardText {
                    anchors.left: densityText.right
                    anchors.bottom: densityText.bottom

                    width: 31; height: 38
                    fontWeight: Font.Bold
                    size: 32
                    text: "%"
                    color: "#8E9DAF"
                }
            }
        }

        Item {
            width: 297; height: 61
            PretendardText {
                //y: 75
                width: 80; height: 24
                fontWeight: Font.Bold
                size: 20
                color: "#758395"
                text: tr_SCAN_DATETIME
            }

            PretendardText {
                y: 98-75
                width: 297; height: 38
                fontWeight: Font.Regular
                color: "#FFFFFF"
                size: 32
                text: "2024년11월07일 11:07"
            }
        }
    }
}
