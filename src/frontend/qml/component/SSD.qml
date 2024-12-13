import QtQuick 2.0

Item {
    id: root

    property real circleSize: 2.5
    property string circleColor: "#DFDFDF"

    width: 28.5
    height: 24.5

    Rectangle {
        id: rect

        anchors.fill: parent

        radius: 2
        border.width: 2
        border.color: "#DFDFDF"
        color: "transparent"

        Circle {
            size: circleSize
            x: 23
            y: 19
            color: circleColor
        }
        Circle {
            size: circleSize
            x: 3
            y: 19
            color: circleColor
        }
        Circle {
            size: circleSize
            x: 3
            y: 3
            color: circleColor
        }
        Circle {
            size: circleSize
            x: 23
            y: 9
            color: circleColor
        }
        PretendardText {
            width: 17
            height: 10
            x: 6
            y: 7
            size: 8
            text: "SSD"
            color: circleColor
        }
    }
}
