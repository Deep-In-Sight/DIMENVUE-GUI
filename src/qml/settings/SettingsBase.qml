import QtQuick 2.0
import "../component"

Item {
    id: root

    property url iconPath
    property string title

    signal prevClicked()

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_GO_BACK: tr(STRING.STR_GO_BACK)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_GO_BACK = tr(STRING.STR_GO_BACK)
        }
    }
    //-------------------------------------------------------------------------

    ButtonSmall {
        width: 196; height: 64
        x: 72
        y: 106

        iconPath: "qrc:/resources/images/arrow_back.png"
        buttonText: tr_GO_BACK
        onClicked: {
            root.prevClicked()
        }
    }
    Row {
        width: 233; height: 48
        x: 1018
        y: 114
        spacing: 20

        Item {
            width: 48; height: 48
            Image {
                anchors.centerIn: parent
                source: iconPath
            }
        }
        PretendardText {
            width: 165; height: 43
            anchors.verticalCenter: parent.verticalCenter
            fontWeight: 400
            size: 36
            color: "#FFFFFF"
            text: title
        }
    }
}
