import QtQuick 2.0

Item {
    id: root

    enabled: false

    signal bgClicked()
    signal modalUnloaded(string url)

    property bool isFullscreen: false

    function load(url, x, y) {
        loader.source = url
        root.enabled = true
        loader.item.x = x
        loader.item.y = y

        isFullscreen = false
    }
    function loadFullscreen(url, x, y) {
        loader.source = url
        root.enabled = true
        loader.item.x = x
        loader.item.y = y
        isFullscreen = true
    }
    function load2(url, x, y, callback) {
        load(url, x, y)

        callback(loader.item)
    }

    function unload() {
        var url = loader.source

        loader.source = ""
        root.enabled = false

        root.modalUnloaded(url)
    }
    function unload2(url) {
        var index = loader.source.toString().indexOf(url, 0)
        console.log("unload2(" + url + ") index: " + index)

        if (0 <= index) {
            unload()
        }
    }

    MouseArea {
        id: bgModal

        anchors.fill: parent
        enabled: root.enabled
        onClicked: {
            root.bgClicked()

            console.log("bg clicked: " + mouseX + ", " + mouseY)
        }
    }
    Loader {
        id: loader

        //anchors.fill: parent
        enabled: root.enabled
    }
}
