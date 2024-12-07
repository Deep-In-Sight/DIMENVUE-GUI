import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: root

    signal wifiSelected(string name, int level, bool lock)

    width: 800; height: 540
//    ListModel {
//        id: listModel

//        ListElement { name: "1"; level: 1; lock: true }
//        ListElement { name: "2"; level: 2; lock: true }
//        ListElement { name: "3"; level: 3; lock: false }
//        ListElement { name: "4"; level: 1; lock: true }
//        ListElement { name: "5"; level: 2; lock: false }
//        ListElement { name: "6"; level: 3; lock: true }
//    }

    ListView {
        id: listView

        anchors.fill: parent
        spacing: 10
        clip: true

        delegate: WifiListDelegate {
            //wifiLevel: level
            wifiName: modelData
            //isLock: lock

            onClicked: {
                var level = 0
                var lock = false
                var name = modelData
                root.wifiSelected(name, level, lock)

                //console.log("wifiSelected(" + name + ", " + level +", " + lock + ")")
            }
        }
        //model : listModel
        model: db.ssidList
    }

    LinearGradient {
        visible: listView.contentHeight > listView.height
        width: parent.width; height: 195
        anchors.bottom: parent.bottom

        start: Qt.point(0, 0)
        end: Qt.point(0,195)

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#00232E3D" }
            GradientStop { position: 0.8; color: "#7F253241" }
            GradientStop { position: 1.0; color: "#FF253241" }
        }
    }
}
