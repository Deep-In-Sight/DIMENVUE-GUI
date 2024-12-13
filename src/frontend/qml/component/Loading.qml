import QtQuick 2.0

Item {
    id: root

    property int type: 0        // 0: gray
                                // 1: accent blue
                                // 2: dimenvue scanner
    property int current: 0
    readonly property int frameCount: (type == 2) ? 10 : 7
    property alias interval: timer.interval

    property string sourceBase: "qrc:/resources/images/loading/loading_"
    property string source: sourceBase + type + current + ".png"

    function start() {
        timer.running = true
    }
    function stop() {
        timer.running = false
    }

    Timer {
        id: timer
        interval: 100
        repeat: true

        onTriggered: {
            if (current == frameCount-1) {
                current = 0;
            } else {
                current += 1
            }/*

            current += 1
            if (frameCount <= current) {
                current = 0
            }*/
        }
    }
    Image {
        anchors.fill: parent
        source: root.source
    }
}
