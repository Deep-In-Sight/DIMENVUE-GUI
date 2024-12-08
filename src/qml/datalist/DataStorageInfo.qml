import QtQuick 2.0
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0
import "../component"

Item {
    id: root

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_SSD_CAPACITY: tr(STRING.STR_SSD_CAPACITY)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_SSD_CAPACITY = tr(STRING.STR_SSD_CAPACITY)
        }
    }
    //-------------------------------------------------------------------------

    property real usage
    property real usageByTB: usage / 1000.0
    property real guageWidth: 1642 * usageByTB

    Rectangle {
        width: 2270; height: 96
        y: 1324

        color: "#1D2937"
    }
    Item {
        width: 2126; height: 43
        x: 72
        y: 1351

        Item {
            width: 113; height: 34
            y: 5
            PretendardText {
                width: Math.max(113, contentWidth)
                height: 34
                anchors.right: parent.right
                //y: 5
                opacity: 0.8
                fontWeight: 700
                size: 28
                color: "#FFFFFF"
                text: tr_SSD_CAPACITY
            }
        }

        Rectangle {
            id: group_168

            width: 1642; height: 34
            x: 150
            y: 5
            radius: height/2
            color: "#0C1A2A"

            Rectangle {
                id: rect

                width: guageWidth
                height: 36
                anchors.verticalCenter: parent.verticalCenter
                radius: height/2
                color: "#0C1A2A"

                LinearGradient {
                    id: guage

                    anchors.fill: parent

                    start: Qt.point(0,0)
                    end: Qt.point(rect.width, rect.height)
                    visible: false

                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "#802079FF" }
                        GradientStop { position: 0.25; color: "#8020AFFF" }
                        GradientStop { position: 0.5; color: "#802079FF" }
                        GradientStop { position: 0.75; color: "#804A5058" }
                    }
                }
                Rectangle {
                    id: mask
                    anchors.fill: rect
                    radius: height/2
                    color: "#0C1A2A"
                }
                OpacityMask {
                    anchors.fill: guage
                    source: guage
                    maskSource: mask
                }

                Row {
                    width: 94; height: 36
                    spacing: 4
                    anchors.centerIn: parent

                    PretendardText {
                        width: 52; height: 34
                        fontWeight: 700
                        size: 28
                        color: "#FFFFFF"
                        opacity: 0.8
                        text: usage
                    }
                    PretendardText {
                        width: 38; height: 34
                        fontWeight: 400
                        size: 28
                        color: "#FFFFFF"
                        opacity: 0.8
                        text: "GB"
                    }
                }
            }

        }
        Row {
            id: frame_157
            width: 274; height: 43
            anchors.right: parent.right

            spacing: 8

            Row {
                id: frame_36
                width: 128; height: 43
                spacing: 7

                PretendardText {
                    width: 76; height: 43
                    fontWeight: 700
                    size: 36
                    color: "#7FB2FF"
                    text: usageByTB.toFixed(2)
                }
                PretendardText {
                    width: 45; height: 43
                    fontWeight: 400
                    size: 36
                    color: "#7FB2FF"
                    text: "TB"
                }
            }
            PretendardText {
                width: 12; height: 43
                fontWeight: 300
                size: 36
                color: "#667588"
                text: "/"
            }
            Row {
                width: 118; height: 43
                spacing: 7

                PretendardText {
                    width: 66; height: 43
                    fontWeight: 400
                    size: 36
                    color: "#667588"
                    text: "1.00"
                }
                PretendardText {
                    width: 45; height: 43
                    fontWeight: 400
                    size: 36
                    color: "#667588"
                    text: "TB"
                }
            }
        }
    }
}
