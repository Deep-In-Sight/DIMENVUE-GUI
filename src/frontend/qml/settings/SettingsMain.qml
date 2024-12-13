import QtQuick 2.0
import "../component"

Item {
    id: settingsMain

    property int currentView: 0

    function setCurrentView(name) {
        switch (name) {
        case "Language":
            settingsLoader.source = "LanguageSelection.qml"
            prevNext.visible = false
            currentView = 0
            break;
        case "Network":
            settingsLoader.source = "NetworkSettings.qml"
            prevNext.visible = true
            currentView = 1
            break;
        case "Login":
            settingsLoader.source = "Login.qml"
            prevNext.visible = true
            currentView = 2
            break;
        case "Booting":
            mainLoader.source = "../menu/Menu.qml"
            app.hideKeyboard()
            break
        }
    }

    Component.onCompleted: {
        switch (currentView) {
        case 0:
            setCurrentView("Language")
            break
        case 1:
            setCurrentView("Network")
            break
        case 2:
            setCurrentView("Login")
            break
        }
    }

    Rectangle {
        width: parent.width
        height: 1535
        y: 66
        color: "#0C1A2A"
        opacity: 0.8
    }
    SettingsPhase {
        id: settingsPhase

        width: 1302
        height: 78
        x: 484
        y: 186

        phase: currentView
    }
    Loader {
        id: settingsLoader

        anchors.fill: parent

        //source: "LanguageSelection.qml"
        //source: "NetworkSettings.qml"
        //source: "Login.qml"
        //source: "Settings.qml"

        onLoaded: {
            console.log(settingsLoader.source + " is loaded...")
        }
    }
    NetworkSettingsPrevNext {
        id: prevNext

        y: keyboard.visible ? -700 : 0

        onPrevClicked: {
            switch (currentView) {
            case 1:
                setCurrentView("Language")
                app.hideKeyboard()
                break
            case 2:
                setCurrentView("Network")
                break
            }
        }
        onSkipClicked: {
            switch (currentView) {
            case 1:
                setCurrentView("Login")
                app.hideKeyboard()
                break
            case 2:
                mainLoader.source = "../menu/Menu.qml"
                break
            }
        }
    }
}
