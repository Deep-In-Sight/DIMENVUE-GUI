import QtQuick 2.0
import "../component"
Item {
    id: root

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_INPUT_ID: tr(STRING.STR_INPUT_ID)
    property string tr_INPUT_PASSWORD: tr(STRING.STR_INPUT_PASSWORD)
    property string tr_LOGIN: tr(STRING.STR_LOGIN)
    property string tr_INCORRECT_ID_OR_PASSWORD: tr(STRING.STR_INCORRECT_ID_OR_PASSWORD)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_INPUT_ID = tr(STRING.STR_INPUT_ID)
            tr_INPUT_PASSWORD = tr(STRING.STR_INPUT_PASSWORD)
            tr_LOGIN = tr(STRING.STR_LOGIN)
            tr_INCORRECT_ID_OR_PASSWORD = tr(STRING.STR_INCORRECT_ID_OR_PASSWORD)
        }
    }
    //-------------------------------------------------------------------------

    property bool passwordIncorrect: false
    property int offsetY: 0

    Connections {
        target: monitor
        onUserLoginDone: {
            var id = idInput.inputText
            var pw = pwInput.inputText

            offsetY = 0

            console.log("login(id: " + id + ", pw: " + pw + "): " + value)

            app.hideKeyboard()

            if (value) {
                setCurrentView("Booting")
            } else {
                root.passwordIncorrect = true
                idInput.clear()
                pwInput.clear()
            }
        }
    }

    Item {
        width: 800; height: 372
        x: 735
        y: 364
        clip: true

        Column {
            id: frame_8200

            width: 800; height: 372
            y: offsetY
            spacing: 60

            Column {
                id: frame_153
                width: parent.width; height: 216
                spacing: 24

                TextField {
                    id: idInput
                    icon: "qrc:/resources/images/id.png"
                    displayText: tr_INPUT_ID
                    border.color: passwordIncorrect ? "#FF5C00" : "#FFFFFF"
                    onTextFieldClicked: {
                        passwordIncorrect = false
                        app.showKeyboard()
                    }
                    onAccepted: {
                        pwInput.setFocus()
                    }
                }
                TextField {
                    id: pwInput
                    icon: "qrc:/resources/images/lock.png"
                    enableVisibility: true
                    displayText: tr_INPUT_PASSWORD
                    border.color: passwordIncorrect ? "#FF5C00" : "#FFFFFF"
                    onTextFieldClicked: {
                        passwordIncorrect = false
                        app.showKeyboard()
                    }
                    onAccepted: {
                        offsetY = -150
                        okButton.forceActiveFocus()
                    }

                    Item {
                        visible: passwordIncorrect

                        width: 648; height: 40
                        y: 96
                        Row {
                            anchors {
                                left: parent.left; leftMargin: 12
                                right: parent.right; rightMargin: 12
                                top: parent.top; topMargin: 8
                                bottom: parent.bottom; bottomMargin: 8
                            }
                            spacing: 4

                            Image {
                                anchors.verticalCenter: parent.verticalCenter
                                width: 14; height: 14
                                source: "qrc:/resources/images/error.png"
                            }
                            PretendardText {
                                width: 446; height: 24
                                fontWeight: 400
                                size: 20
                                text: tr_INCORRECT_ID_OR_PASSWORD
                                color: "#FF5C00"
                            }
                        }
                    }
                }
            }
            TextButton {
                id: okButton

                buttonText: tr_LOGIN
                onClicked: {
                    var id = idInput.inputText
                    var pw = pwInput.inputText
                    var result = db.login(id, pw)
                }
            }
        }
    }
}
