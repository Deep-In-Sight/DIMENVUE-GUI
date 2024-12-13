import QtQuick 2.0
import QtGraphicalEffects 1.0
import "component"
import "keyboard"

Item {
    id: root

    function start() {
        console.log("start() !!!")
        //db.update()
        //timeTimer.start()

        if (debugMode) {
            startDebug()
        } else {
            startRelease()
        }
    }
    function startRelease() {
        mainLoader.source = "settings/SettingsMain.qml"

        modal.load("qrc:/qml/intro/Intro.qml", 0, 0)
    }

    function startDebug() {
        loadDebugvue()
    }
    function loadDebugvue() {
        if (debugMode) {
            mainLoader.source = "Debugvue.qml"

            app.hideKeyboard()
        }
    }
    function keyboardDown() {
        //keyboard.visible = false
        console.error("keyboardDown() is derecated. call app.hideKeyboard()")
    }
    function enableBlur() {
        mainBlur.visible = true
    }
    function disableBlur() {
        mainBlur.visible = false
    }
    function loadScanMain(url) {
        scanMain.load(url)
    }
    function getBackgroundType(url) {
        var ret

        if (url == "qrc:/qml/datalist/DataListMain.qml" ||
            url == "qrc:/qml/settings/Settings.qml" ||
            url == "qrc:/qml/settings/SettingsNetwork.qml" ||
            url == "qrc:/qml/settings/SettingsUserInfo.qml" ||
            url == "qrc:/qml/settings/SettingsProductInfo.qml") {
            ret = 1;
        } else {
            ret = 0;
        }
        console.log("getBackgroundType(" + url + "): " + ret)

        return ret
    }

    Background {
        id: mainItem

        anchors.fill: parent
        type: getBackgroundType(mainLoader.source)

        Loader {
            id: mainLoader

            property var viewList: []

            anchors.fill: parent

            function load(url) {
                viewList.clear()
                mainLoader.source = url
            }
            function stackedLoad(url) {
                viewList.push(mainLoader.source)
                mainLoader.source = url
            }
            function popView() {
                if (viewList.length) {
                    var url = viewList.pop()
                    mainLoader.source = url
                }
            }
        }
        Keyboard {
            id: keyboard
            objectName: "keyboard"
            visible: false
        }
        TitleBar {
            id: titleBar
        }
        GaussianBlur {
            id: mainBlur

            visible: false
            anchors.fill: modal.isFullscreen ? mainItem : mainLoader
            source: modal.isFullscreen ? mainItem : mainLoader
            deviation: 6
            radius: 8
            samples: 16
        }
    }
    Modal {
        id: modal

        anchors.fill: parent
    }
}
