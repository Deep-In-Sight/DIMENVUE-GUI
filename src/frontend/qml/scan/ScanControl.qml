import QtQuick 2.0
import "../component"

Item {
    id: root

    signal zoomInClicked()
    signal zoomOutClicked()

    Image {
        id: xyz
        width: 240; height: 240
        x: 72
        y: 181
        source: "qrc:/resources/images/xyz.png"
    }

    Column {
        id: select3D

        width: 96; height: 204
        x: 72
        y: 820
        spacing: 12

        ImageButton {
            id: orthoButton

            width: 96; height: 96
            sources: [
                "qrc:/resources/images/move.png",
                "qrc:/resources/images/move_p.png",
                "qrc:/resources/images/move_s.png"
            ]
            onClicked: {
                perspButton.state = "0"
                db.setProjectionMode(1) //orthographic
            }
        }
        ImageButton {
            id: perspButton

            width: 96; height: 96
            sources: [
                "qrc:/resources/images/perspective.png",
                "qrc:/resources/images/perspective_p.png",
                "qrc:/resources/images/perspective_s.png"
            ]
            onClicked: {
                orthoButton.state = "0"
                db.setProjectionMode(0) //perspective
            }
        }
    }

    ImageButton {
        id: zoom

        width: 96; height: 192
        x: 72
        y: 1060

        enableMouseArea: false
        sources: [
            "qrc:/resources/images/zoom.png",
            "qrc:/resources/images/zoomin.png", //+
            "qrc:/resources/images/zoomout.png" //-
        ]
        Column {
            MouseArea {
                width: 96; height: 96
                onPressed: {
                    zoom.state = "1"
                }
                onClicked: {
                    zoom.state = "0"
                    root.zoomInClicked()
                }
            }
            MouseArea {
                width: 96; height: 96
                onPressed: {
                    zoom.state = "2"
                }
                onClicked: {
                    zoom.state = "0"
                    root.zoomOutClicked()
                }
            }
        }
    }
}
