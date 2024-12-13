import QtQuick 2.0
import "../component"

SettingsBase {
    id: root

    property string networkName: db.currentWifiSSID// "Network name-03"

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_NETWORK_CONNECTION_SETTING: tr(STRING.STR_NETWORK_CONNECTION_SETTING)
    property string tr_COMPLETE: tr(STRING.STR_COMPLETE)
    property string tr_NETWORK_SEARCH: tr(STRING.STR_NETWORK_SEARCH)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_NETWORK_CONNECTION_SETTING = tr(STRING.STR_NETWORK_CONNECTION_SETTING)
            tr_COMPLETE = tr(STRING.STR_COMPLETE)
            tr_NETWORK_SEARCH = tr(STRING.STR_NETWORK_SEARCH)
        }
    }
    //-------------------------------------------------------------------------


    iconPath: "qrc:/resources/images/wifi.png"
    title: tr_NETWORK_CONNECTION_SETTING

    onPrevClicked: {
        mainLoader.source = "Settings.qml"
    }

    SettingsDelegate2 {
        key: "WI-FI connection"
        x: 735
        y: 414

        Item {
            width: 800; height: 120
            anchors.bottom: parent.bottom

            Row {
                width: 740; height: 48
                x: 30
                anchors.verticalCenter: parent.verticalCenter
                spacing: 48

                Row {
                    width: 616; height: 48
                    spacing: 24
                    Item {
                        width: 33; height: 33
                        anchors.verticalCenter: parent.verticalCenter
                        Image {
                            anchors.centerIn: parent
                            source: "qrc:/resources/images/check_circle.png"
                        }
                    }
                    PretendardText {
                        width: 596; height: 48
                        fontWeight: 400
                        size: 40
                        color: "#FFFFFF"
                        text: networkName
                    }
                }

                Row {
                    width: 76; height: 32
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 12

                    Item {
                        width: 32; height: 32
                        Image {
                            anchors.centerIn: parent
                            source: "qrc:/resources/images/lock.png"
                        }
                    }
                    Item {
                        width: 32; height: 32
                        Image {
                            anchors.centerIn: parent
                            source: "qrc:/resources/images/info.png"
                        }
                    }
                }
            }
        }
    }
    TextButton {
        width: 800; height: 96
        x: 735
        y: 644
        buttonText: tr_COMPLETE
    }
    PretendardText {
        width: 202; height: 38
        x: 1034
        y: 776
        fontWeight: 400
        size: 32
        color: "#FFFFFF"
        text: tr_NETWORK_SEARCH
        font.underline: true
    }
}
