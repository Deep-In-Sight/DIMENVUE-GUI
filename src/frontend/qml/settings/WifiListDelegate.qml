import QtQuick 2.0
import QtGraphicalEffects 1.0
import "../component"

Item {
    id: root

    width: parent.width
    height: 96

    property int wifiLevel
    property string wifiName
    property bool isLock

    signal clicked()

    Rectangle {
        id: normalRect
        anchors.fill: parent
        visible: !mouseArea.pressed
        radius: 16
        color: "#FFFFFF"
        opacity: 0.1
    }
    Rectangle {
        id: selectRect
        anchors.fill: parent
        visible: mouseArea.pressed
        radius: 16
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#052079FF" }
            GradientStop { position: 0.5; color: "#1E2079FF" }
            GradientStop { position: 1.0; color: "#332079FF" }
        }
    }

    Row {
        id: frame_87

        anchors.left: parent.left; anchors.leftMargin: 30
        anchors.right: parent.right; anchors.rightMargin: 30
        anchors.top: parent.top; anchors.topMargin: 24
        anchors.bottom: parent.bottom; anchors.bottomMargin: 24
        spacing: 48

        Row {
            id: frame_85

            width: 660; height: 48
            spacing: 24

            Item {
                width: 40; height: 40
                anchors.verticalCenter: parent.verticalCenter
                Image {
                    anchors.centerIn: parent
                    source: 0 < wifiLevel ? "qrc:/resources/images/wifi_" + wifiLevel + ".png"
                                          : ""
                }
            }

            PretendardText {
                width: 596; height: 48
                fontWeight: 400
                size: 40
                text: wifiName
                color: "#FFFFFF"
            }
        }
        Item {
            width: 32; height: 32
            Image {
                visible: isLock
                anchors.centerIn: parent
                source: "qrc:/resources/images/lock.png"
            }
        }
    }

    GradientBorder {
        anchors.fill: parent
        visible: mouseArea.pressed

        start: Qt.point(0,0)
        end: Qt.point(root.width, root.height)

        gradient: Gradient {
            GradientStop {
               position: 0.0; color: "#2079FF"
            }
            GradientStop {
               position: 0.25; color: "#20AFFF"
            }
            GradientStop {
               position: 0.5; color: "#2079FF"
            }
            GradientStop {
               position: 0.75; color: "#4A5058"
            }
            GradientStop {
               position: 1.0; color: "#4A5058"
            }
        }

        borderWidth: 3
        radius: 16
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            root.clicked()
        }
    }
}
