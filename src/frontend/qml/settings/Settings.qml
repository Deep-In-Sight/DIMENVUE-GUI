import QtQuick 2.0
import "../component"

Item {
    id: root

    property url callerUrl

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_GO_BACK: tr(STRING.STR_GO_BACK)
    property string tr_SETTING: tr(STRING.STR_SETTING)
    property string tr_SAVE_CHANGE: tr(STRING.STR_SAVE_CHANGE)
    property string tr_USER_INFORMATION: tr(STRING.STR_USER_INFORMATION)
    property string tr_PRODUCT_SETTING: tr(STRING.STR_PRODUCT_SETTING)
    property string tr_NETWORK_CONNECTION_SETTING: tr(STRING.STR_NETWORK_CONNECTION_SETTING)
    property string tr_LANGUAGE_SETTING: tr(STRING.STR_LANGUAGE_SETTING)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_GO_BACK = tr(STRING.STR_GO_BACK)
            tr_SETTING = tr(STRING.STR_SETTING)
            tr_SAVE_CHANGE = tr(STRING.STR_SAVE_CHANGE)
            tr_USER_INFORMATION = tr(STRING.STR_USER_INFORMATION)
            tr_PRODUCT_SETTING = tr(STRING.STR_PRODUCT_SETTING)
            tr_NETWORK_CONNECTION_SETTING = tr(STRING.STR_NETWORK_CONNECTION_SETTING)
            tr_LANGUAGE_SETTING = tr(STRING.STR_LANGUAGE_SETTING)
        }
    }
    //-------------------------------------------------------------------------

    Component.onCompleted: {
        console.log("language: " + db.language)

        if (0 === db.language) {
            radioKor.checked = true
        } else {
            radioEng.checked = true
        }
    }

    ButtonSmall {
        width: 196; height: 64
        x: 72
        y: 106

        iconPath: "qrc:/resources/images/arrow_back.png"
        buttonText: tr_GO_BACK
        onClicked: {
            mainLoader.popView()
        }
    }
    PretendardText {
        width: 83; height: 57
        x: 316
        y: 109
        fontWeight: 500
        size: 48
        color: "#8E9DAF"
        text: tr_SETTING
    }
    TextButton {
        width: 151; height: 64
        x: 2047
        y: 106
        buttonText: tr_SAVE_CHANGE
        textSize: 30
    }
    Column {
        width: 2126; height: 748
        x: 72
        y: 256
        spacing: 36

        SettingsDelegate {
            iconPath: "qrc:/resources/images/person_outline.png"
            title: tr_USER_INFORMATION

            Row {
                width: 744; height: 48
                x: 1296
                y: 58
                spacing: 24

                PretendardText {
                    width: 196; height: 43
                    anchors.verticalCenter: parent.verticalCenter
                    fontWeight: 400
                    size: 36
                    color: "#FFFFFF"
                    text: db.userName //"딥인사이트 님"
                }
                Rectangle {
                    width: 3; height: 40
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#0C1A2A"
                }
                PretendardText {
                    width: 462; height: 43
                    anchors.verticalCenter: parent.verticalCenter
                    fontWeight: 400
                    size: 36
                    color: "#FFFFFF"
                    text: db.userEmail //"deep-insight@deepinsight.ai"
                }
            }
            onClicked: {
                mainLoader.source = "SettingsUserInfo.qml"
            }
        }
        SettingsDelegate {
            iconPath: "qrc:/resources/images/settings_overscan.png"
            title: tr_PRODUCT_SETTING

            onClicked: {
                mainLoader.source = "SettingsProductInfo.qml"
            }
        }
        SettingsDelegate {
            iconPath: "qrc:/resources/images/language.png"
            title: tr_LANGUAGE_SETTING
            showArrow: false

            Row {
                width: 446; height: 48
                x: 1594
                y: 58
                spacing: 108

                RadioButton {
                    id: radioKor

                    width: 158; height: 48
                    text: "한국어"
                    onClicked: {
                        radioEng.checked = false
                        app.changeLanguage(0)
                    }
                }
                RadioButton {
                    id: radioEng

                    width: 158; height: 48
                    text: "English"
                    onClicked: {
                        radioKor.checked = false
                        app.changeLanguage(1)
                    }
                }
            }
        }
        SettingsDelegate {
            iconPath: "qrc:/resources/images/wifi.png"
            title: tr_NETWORK_CONNECTION_SETTING
            PretendardText {
                width: 350; height: 48
                x: 1689
                y: 58
                fontWeight: 400
                size: 36
                color: "#FFFFFF"
                text: db.currentWifiSSID //"Network name-03"
            }

            onClicked: {
                mainLoader.source = "SettingsNetwork.qml"
            }
        }
    }

    PretendardText {
        width: 276; height: 38
        x: 997
        y: 1312
        fontWeight: 400
        size: 32
        color: "#FFFFFF"
        opacity: 0.8
        text: "DIMENVUE V 1.8.16"
    }
}
