import QtQuick 2.0
import "../component"

Item {
    id: root

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_INPUT_WIFI_PASSWORD: tr(STRING.STR_INPUT_WIFI_PASSWORD)
    property string tr_INPUT_WIFI_PASSWORD_DONE: tr(STRING.STR_INPUT_WIFI_PASSWORD_DONE)
    property string tr_NETWORK_SEARCH: tr(STRING.STR_NETWORK_SEARCH)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_INPUT_WIFI_PASSWORD = tr(STRING.STR_INPUT_WIFI_PASSWORD)
            tr_INPUT_WIFI_PASSWORD_DONE = tr(STRING.STR_INPUT_WIFI_PASSWORD_DONE)
            tr_NETWORK_SEARCH = tr(STRING.STR_NETWORK_SEARCH)
        }
    }
    //-------------------------------------------------------------------------

    property int phase: 0   //0 : Wifi Off
                            //1 : Wifi On (display list)
                            //2 : Wifi Select
                            //3 : Wifi Password (show keyboard)

    property bool isKeyboardVisible : keyboard.visible
    property bool isOkVisible: wifiPassword.isOkVisible
    property int okOffsetY: isOkVisible ? -110 : 0
    property int kbdOffsetY: isKeyboardVisible ? -281 : 0
    property int offsetY: okOffsetY + kbdOffsetY

    function gotoNetworkSearch() {
        dummy.forceActiveFocus()

        app.hideKeyboard()
        phase = 1
        wifiPassword.showOkButton(false)
    }

    Item {
        width: 800; height: 770
        x: 735
        y: 384
        clip: isKeyboardVisible || isOkVisible

        Column {
            id: frame_8195
            width: 800; height: 770
            y: offsetY
            spacing: 60

            WifiConnection {
                id: wifiConnection
                width: 800; height: 170

                onWifiOnChanged: {
                    if (false == wifiOn) {
                        phase = 0
                        wifiPassword.isOkVisible = false
                    } else {
                        db.updateWifi()

                        phase = 1
                    }
                }
            }

            Item {
                width: 800; height: 540
                visible: wifiConnection.wifiOn

                WifiList {
                    visible: (1 === phase)

                    onWifiSelected: {
                        wifiPassword.wifiName = name
                        wifiPassword.wifiLevel = level
                        wifiPassword.isLock = lock

                        phase = 2
                    }
                }
                WifiPassword {
                    id: wifiPassword

                    visible: (2 === phase)
                    displayText: tr_INPUT_WIFI_PASSWORD
                    wifiLevel: 3
                    isLock: true

                    Connections {
                        target: keyboard
                        onKeyClicked: {
                            if (key == "Enter") {
                                wifiPassword.showOkButton(true)
                            }
                        }
                    }
                    onWifiConnectOk: {
                        app.hideKeyboard()
                        setCurrentView("Login")
                    }
                }
            }
        }

        Rectangle {
            visible: isKeyboardVisible //&& !isOkVisible
            width: 800; height: 69
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#FF253241" }
                GradientStop { position: 0.5; color: "#CC253241" }
                GradientStop { position: 1.0; color: "#00232E3D" }
            }
        }
        Item {
            id: dummy
        }
    }
}
