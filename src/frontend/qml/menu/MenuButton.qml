import QtQuick 2.0
import "../component"

Item {
    id: root

    property string mainText
    property string subText
    property url icon
    property alias imageWidth: image.width
    property alias imageHeight: image.height
    property alias imageX: image.x
    property alias imageY: image.y
    property bool gradientBackground: false

    signal clicked()

    width: 680; height: 700
    Rectangle {
        anchors.fill: parent
        visible: gradientBackground
        radius: 70

        gradient: Gradient {
            GradientStop {
               position: 0.0; color: Qt.rgba(0.125,0.472,1,0.02) //#2079FF05 2%
            }
            GradientStop {
               position: 0.5; color: Qt.rgba(0.125,0.472,1,0.12)
            }
            GradientStop {
               position: 1.5; color: Qt.rgba(0.125,0.472,1,0.2)
            }
        }
    }

    GradientBorder {
        anchors.fill: parent

        start: Qt.point(0,0)
        end: Qt.point(parent.width, parent.height)

        gradient: Gradient {
            GradientStop {
               position: 0.0; color: Qt.rgba(1,1,1,0.21)
            }
            GradientStop {
               position: 0.25; color: Qt.rgba(1,1,1,0.3)
            }
            GradientStop {
               position: 0.5; color: Qt.rgba(1,1,1,0.15)
            }
            GradientStop {
               position: 0.75; color: Qt.rgba(1,1,1,0.06)
            }
        }

        borderWidth: 6
        radius: 70
    }
    Item {
        width: 233; height: 210
        x: 233
        y: 175
        Image {
            id: image

            width: 103; height: 56
//            x: 65
//            y: 55
            anchors.centerIn: parent
            source: icon// "qrc:/resources/images/group_156.png"
        }
    }

    HelveticaCompressedText {
        width: 539; height: 38
        x: 86
        y: 483
        fontWeight: 400
        size: 72
        text: mainText //"Scanning the space"
        color: "#FFFFFF"
        horizontalAlignment: Text.AlignHCenter
    }
    PretendardText {
        width: 550; height: 66
        x: 65
        y: 562
        fontWeight: 400
        size: 32
        color: "#FFFFFF"
        text: subText //"실내 공간을 3D 데이터로 전환해 보세요."
        horizontalAlignment: Text.AlignHCenter
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.clicked()
        }
    }
}
