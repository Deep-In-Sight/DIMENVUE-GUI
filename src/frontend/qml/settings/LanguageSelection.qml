import QtQuick 2.0
import "../component"

Item {
    id: root

    property bool languageSelected: (db.language === 0 || db.language === 1)

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_SELECTION_COMPLETE: tr(STRING.STR_SELECTION_COMPLETE)
    property string tr_GO_PREVIOUS: tr(STRING.STR_GO_PREVIOUS)
    property string tr_SKIP: tr(STRING.STR_SKIP)
    property string tr_INPUT_WIFI_PASSWORD: tr(STRING.STR_INPUT_WIFI_PASSWORD)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_SELECTION_COMPLETE = tr(STRING.STR_SELECTION_COMPLETE)
            tr_GO_PREVIOUS = tr(STRING.STR_GO_PREVIOUS)
            tr_SKIP = tr(STRING.STR_SKIP)
            tr_INPUT_WIFI_PASSWORD = tr(STRING.STR_INPUT_WIFI_PASSWORD)
        }
    }
    //-------------------------------------------------------------------------

    Column {
        width: 1179; height: 168
        x: 545
        y: 494
        spacing: 24

        PretendardText {
            width: 683; height: 72
            fontWeight: 400
            size: 60
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: "사용할 언어를 선택해 주세요."
            color: "#FFFFFF"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        PretendardText {
            width: 1179; height: 72
            fontWeight: 400
            size: 60
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: "Please select the language you'd like to use."
            color: "#FFFFFF"
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Row {
        width: 720; height: 120
        x: 775
        y: 806
        spacing: 120

        LanguageButton {
            width: 320; height: 120
            state: db.language === 0 ? "selected" : "normal"
            text: "한국어"
            onSelected: app.changeLanguage(0)
        }

        LanguageButton {
            width: 320; height: 120
            state: db.language === 1 ? "selected" : "normal"
            text: "English"
            onSelected: app.changeLanguage(1)
        }
    }
    Rectangle {
        width: 800; height: 96
        x: 735
        y: 1138
        radius: 16
        color: "#FFFFFF"
        opacity: root.languageSelected ? 1.0 : 0.3
        PretendardText {
            //width: 163; height: 53
            anchors.centerIn: parent
            fontWeight: 700
            size: 44
            text: tr_SELECTION_COMPLETE
            //text: "선택 완료"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (root.languageSelected) {
                    settingsMain.setCurrentView("Network")
                }
            }
        }
    }
}
