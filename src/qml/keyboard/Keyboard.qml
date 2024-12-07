import QtQuick 2.0
import "../component"

Item {
    id: root

    property bool isNumpad: false
    property string keyboardType: "eng"
    property bool isCaps: false
    property bool displayUpperText: keyboardType != "eng"

    width: 2270; height: 760
    y: 660

    signal keyClicked(string key)

    function imageUrl(keyName) {
        var baseUrl = "qrc:/resources/images/"

        switch (keyName) {
        case "Back" : return baseUrl + "back.png"
        case "Enter": return baseUrl + "enter.png"
        case "Shift": return baseUrl + "shift.png"
        case "Numeric": return baseUrl + "numeric.png"
        case "International": return baseUrl + "language.png"
        case "Hide": return baseUrl + "keyboard_down.png"
        default:
            return ""
        }
    }
    function setKeyboardType(type) {
        isNumpad = type === "numpad";
        keyboardType = type

        switch (type) {
        case "kor":
            modelLoader.source = "KeyboardModelKor.qml"
            break;
        case "eng":
            modelLoader.source = "KeyboardModelEng.qml"
            break;
        case "etc":
            modelLoader.source = "KeyboardModelEtc.qml"
            break
        case "numpad":
            modelLoader.source = "KeyboardModelNumpad.qml"
            break
        }
    }
    function onKeyPressed(key) {
        console.log(key + " pressed.")

        switch (key) {
        case "Hide":
            keyboard.forceActiveFocus()
            keyboard.visible = false
            isCaps = false
            break
        case "International":
            if (keyboardType === "eng") {
                setKeyboardType("kor")
            } else {
                setKeyboardType("eng")
            }
            isCaps = false
            break
        case "Numeric":
            setKeyboardType("etc")
            isCaps = false
            break
        case "Kor":
            setKeyboardType("kor")
            isCaps = false
            break
        case "Shift":
            isCaps = !isCaps
            break

        case "Space":
            app.inputNoHangulKey(" ")
            break

        case "Back":
            app.inputBackspace()
            break

        case "Enter":
            break

        default:
            if (keyboardType == "kor") {
                var a = automata.processKoreanKey(key)
                if (a !== key) {
                    app.inputHangulKey(a)
                } else {
                    app.inputNoHangulKey(a)
                }
            } else {
                app.inputNoHangulKey(key)
            }
            break
        }
        keyClicked(key)
    }

    Component.onCompleted: {
        setKeyboardType(keyboardType);
    }

    Loader {
        id: modelLoader

        onLoaded: {
            frame_74.model = item.line0
            frame_76.model = item.line1
            frame_77.model = item.line2
            frame_78.model = item.line3
        }
    }
    KeyboardKorInput {
        id: automata
    }

    Rectangle {
        anchors.fill: parent
        color: "#0C1A2A"
    }
    Column {
        id: frame_83

        width: 1868; height: 656
        x: 201
        y: 64
        spacing: 32

        Component {
            id: keyComponent

            Item {
                width: rect.width; height: 140

                property bool isSpecial: specialKey.length

                Rectangle {
                    id: rect

                    width: isSpecial ? keyWidth: 140
                    height: 140
                    radius: 16
                    color: (specialKey == "Shift" && isCaps)    ? "#8E9DAF" :
                           (isSpecial && specialKey !== "Space")? "#313B47" :
                                                                  "#4E5F74"

                    PretendardText {
                        visible: !isSpecial || (isSpecial && specialKey == "Kor")
                        width: parent.width; height: 50
                        //x: 55
                        horizontalAlignment: Text.AlignHCenter
                        y: 45
                        text: (isSpecial && specialKey == "Kor")? "한글" :
                              (isCaps && (0 < upperText.length))? upperText :
                                                                  centerText
                        fontWeight: 700
                        size: 48
                        color: "#FFFFFF"
                    }
                    PretendardText {
                        visible: (!isSpecial && displayUpperText && !isCaps)
                        width: 17; height: 38
                        x: 16
                        y: 4
                        opacity: 0.5
                        text: upperText
                        fontWeight: 400
                        size: 36
                        color: "#FFFFFF"
                    }
                    Image {
                        visible: isSpecial
                        anchors.centerIn: parent
                        source: isSpecial ? imageUrl(specialKey) : ""
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        var text
                        if (!isSpecial) {
                            if (isCaps && upperText.length) {
                                text = upperText
                            } else {
                                text = centerText
                            }
                        } else {
                            text = specialKey
                        }
                        onKeyPressed(text)
                    }
                }
            }
        }

        ListView {
            id: frame_74
            width: 1860; height: 140
            spacing: 32
            orientation: ListView.Horizontal
            delegate: keyComponent
        }
        ListView {
            id: frame_76
            width: 1828; height: 140
            anchors.right: parent.right
            spacing: 32
            orientation: ListView.Horizontal
            delegate: keyComponent
        }
        ListView {
            id: frame_77
            width: 1860; height: 140
            spacing: 32
            orientation: ListView.Horizontal
            delegate: keyComponent
        }
        ListView {
            id: frame_78
            width: 1868; height: 140
            spacing: 32
            orientation: ListView.Horizontal
            delegate: keyComponent
        }
    }
}
