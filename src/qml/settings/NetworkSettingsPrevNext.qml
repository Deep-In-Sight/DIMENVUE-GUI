import QtQuick 2.0
import "../component"

Item {
    id: root

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_GO_PREVIOUS: tr(STRING.STR_GO_PREVIOUS)
    property string tr_SKIP: tr(STRING.STR_SKIP)
    property string tr_INPUT_WIFI_PASSWORD: tr(STRING.STR_INPUT_WIFI_PASSWORD)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_GO_PREVIOUS = tr(STRING.STR_GO_PREVIOUS)
            tr_SKIP = tr(STRING.STR_SKIP)
            tr_INPUT_WIFI_PASSWORD = tr(STRING.STR_INPUT_WIFI_PASSWORD)
        }
    }
    //-------------------------------------------------------------------------


    signal prevClicked()
    signal skipClicked()

    PretendardText {
        width: 166; height: 43
        x: 95
        y: 1251
        fontWeight: 400
        size: 36
        text: "< " + tr_GO_PREVIOUS
        color: "#FFFFFF"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.prevClicked()
            }
        }
    }
    PretendardText {
        width: 125; height: 43
        x: 2049
        y: 1251
        fontWeight: 400
        size: 36
        text: tr_SKIP
        color: "#FFFFFF"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.skipClicked()
            }
        }
    }
}
