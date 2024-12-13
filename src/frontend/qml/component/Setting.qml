import QtQuick 2.0

Item {
    id: root

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_SETTING: tr(STRING.STR_SETTING)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_SETTING = tr(STRING.STR_SETTING)
        }
    }
    //-------------------------------------------------------------------------

    property int offsetX: Math.min(0, 63 - settingText.contentWidth)

    width: 127; height: 48

    signal clicked()

    Row {
        id: frame_30

        anchors.fill: parent
        spacing: 16
        Image {
            width: 48; height: 48
            source: "qrc:/resources/images/setting.png"
        }
        PretendardText {
            id: settingText

            width: 63; height: 43
            fontWeight: 600
            size: 36
            text: tr_SETTING
            color: "#FFFFFF"
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.clicked()
        }
    }
}
