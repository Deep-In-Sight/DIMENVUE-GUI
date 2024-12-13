import QtQuick 2.0
import "../component"

Item {
    id: root

    property string wifiName
    property int wifiLevel
    property bool isLock
    property alias displayText: textField.displayText
    property alias isOkVisible: frame_8188.visible

    signal wifiConnectOk()

    width: 800; height: 216

    function showOkButton(show) {
        frame_8188.visible = show
    }
    function clearInput() {
        textField.clear()
    }

    Connections {
        target: monitor
        onConnectWifiDone: {
            console.log("onWifiConnectDone: " + value)

            if (value) {
                root.wifiConnectOk()
            }
        }
    }    

    Column {
        id: frame_150

        anchors.fill: parent
        spacing: 24;

        WifiListDelegate {
            width: parent.width
            height: 96
            wifiName: root.wifiName
            wifiLevel: root.wifiLevel
            isLock: root.isLock
        }
        TextField {
            id: textField

            icon: "qrc:/resources/images/lock.png"
            //displayText: "와이파이 비밀번호를 입력하세요."
            enableVisibility: true

            onTextFieldClicked: {
                if (isKeyboardVisible) {
                    showOkButton(true)
                } else {
                    app.showKeyboard()
                    textField.clearInput()
                    showOkButton(false)
                }
            }
            onAccepted: {
                showOkButton(true)
            }
        }
        Column {
            id: frame_8188

            visible: false
            width: 800; height: 170
            spacing: 36
            TextButton {
                buttonText: tr_INPUT_WIFI_PASSWORD_DONE
                onClicked: {
                    var ssid = root.wifiName
                    var pw = textField.inputText
                    var result = db.wifiConnect(ssid, pw)

                    //TODO: move to thread

                    console.log("wifiConnect(ssid: " + ssid + ", pw:" + pw + "): " + result )

//                    if (result) {
//                        root.wifiConnectOk()
//                    }
                }
            }
            PretendardText {
                width: 800; height: 38
                horizontalAlignment: Text.AlignHCenter
                font.underline: true
                fontWeight: 400
                size: 32
                color: "#FFFFFF"
                text: tr_NETWORK_SEARCH

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        gotoNetworkSearch()
                    }
                }
            }
        }
    }
}
