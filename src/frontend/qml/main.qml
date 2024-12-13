import QtQuick 2.12
import QtQuick.Window 2.12
import "component"
import "scan"
import "keyboard"

Window {
    id: window
    visible: true

    title: qsTr("Hello World")
    objectName: "window"
    color: 'blue'

    onActiveFocusItemChanged: {
       app.inputInit("")
    }

    Item {
        id: root
        objectName: "root"

        property bool fullscreen: false
        property int screenWidth
        property int screenHeight
        property real globalScale: scale

        function loadDimenvue() {
            loader.source = "Dimenvue.qml"
        }

        Loader {
            id: loader

            anchors.fill: parent
            onLoaded: {
                item.width = root.screenWidth
                item.height = root.screenHeight
                item.start()
            }
        }
    }
}
