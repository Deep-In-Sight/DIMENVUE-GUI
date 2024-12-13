import QtQuick 2.0
import "../component"

Item {
    id: root

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_MEASURING: tr(STRING.STR_MEASURING)
    property string tr_DATA_DENSITY: tr(STRING.STR_DATA_DENSITY)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_MEASURING = tr(STRING.STR_MEASURING)
            tr_DATA_DENSITY = tr(STRING.STR_DATA_DENSITY)
        }
    }
    //-------------------------------------------------------------------------

    property string measureUnit
    property bool dataDensityVisible: true

    Rectangle {
        id: bg

        width: 2270; height: 96
        y: 1324
        color: "#1D2937"
    }
    Row {
        id: frame_8206

        width: 2126; height: 40
        x: 72
        y: 1352
        spacing: 117

        Item {
            id: measure

            width: 360; height: 36
            Rectangle {
                width: 2; height: 36
                color: "#FFFFFF"
            }
            Rectangle {
                width: 360; height: 2
                y: 34
                color: "#FFFFFF"
            }
            Rectangle {
                width: 2; height: 36;
                x: 360
                color: "#FFFFFF"
            }
            PretendardText {
                anchors.centerIn: parent

                opacity: 0.8
                fontWeight: 300
                size: 32
                color: "#FFFFFF"
                text: measureUnit
            }
        }
        Row {
            id: dataDensity

            width: 1649; height: 40
            spacing: 16
            visible: dataDensityVisible

            Row {
                id: frame_208

                width: 1578; height: 40
                spacing: 32

                PretendardText {
                    width: 146; height: 38
                    color: "#FFFFFF"
                    opacity: 0.8
                    fontWeight: 300
                    size: 32
                    text: tr_DATA_DENSITY
                }
                Rectangle {
                    id: group_66

                    width: 1400; height: 40
                    radius: 12
                    color: "#000000"

                    PretendardText {
                        anchors.centerIn: parent

                        fontWeight: 700
                        size: 28
                        text: tr_MEASURING //"측정 중..."
                        color: "#8E9DAF"
                    }
                }
            }
        }
    }
}
