import QtQuick 2.0

Rectangle {
    id: root

    width: 800; height: 96; radius: 16
    border.width: 2
    border.color: "#FFFFFF"
    color: "transparent"

    property string icon
    property string displayText
    readonly property alias inputText: input.text
    property bool enableVisibility: false

    signal accepted()

    function clear() {
        input.text = ""
        input.focus = false
    }
    function setFocus() {
        input.forceActiveFocus()
    }

    signal textFieldClicked()

    Connections {
        target: app
        onKeyboardTextUpdated: {
            if (input.focus) {
                input.text = value
            }
        }
    }

    Image {
        source: icon
        width: 32; height: 32
        x: 32
        y: 32
    }
    TextInput {
        id: input

        width: 612; height: 38
        x: 88
        y: 29
        font.pixelSize: 32
        font.weight: Font.Normal
        color: "#FFFFFF"
        activeFocusOnPress: true
        echoMode: enableVisibility ? TextInput.Password
                                   : TextInput.Normal
        passwordCharacter: "*"

        onActiveFocusChanged: {
            if (focus) {
                root.textFieldClicked()                
            }
        }
        onAccepted: {
            root.accepted()
        }

        PretendardText {
            anchors.fill: parent
            visible: input.text.length === 0
            opacity: 0.3
            color: "#FFFFFF"
            size: 32
            fontWeight: 400
            text: displayText
        }
        Keys.onPressed: {
            switch (event.key) {
            case Qt.Key_Tab:
                root.accepted()
                event.accepted = true
                break
            }
        }
        MouseArea {
            id: mouseArea
            enabled: input.activeFocus
            anchors.fill: input
            onClicked: {
                root.accepted()
            }
        }
    }

    Image {
        id: visibility

        visible: enableVisibility
        width: 32; height: 32
        x: 736
        y: 32
        source: input.echoMode === TextInput.Password ? "qrc:/resources/images/visibility_off.png"
                                                          : "qrc:/resources/images/visibility.png"
        MouseArea {
            enabled: enableVisibility
            anchors.fill: parent
            onClicked: {
                if (input.echoMode == TextInput.Password) {
                    input.echoMode = TextInput.Normal
                } else {
                    input.echoMode = TextInput.Password
                }
            }
        }
    }
    Rectangle {
        visible: debugMode && input.focus
        anchors.fill: parent
        color: "transparent"
        border.color: "yellow"
        radius: 16
    }
}
