import QtQuick 2.0
import "../component"

SettingsBase {
    id: root

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_GO_BACK: tr(STRING.STR_GO_BACK)
    property string tr_USER_INFORMATION: tr(STRING.STR_USER_INFORMATION)
    property string tr_NAME: tr(STRING.STR_NAME)
    property string tr_EMAIL: tr(STRING.STR_EMAIL)
    property string tr_LOGOUT: tr(STRING.STR_LOGOUT)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_GO_BACK = tr(STRING.STR_GO_BACK)
            tr_USER_INFORMATION = tr(STRING.STR_USER_INFORMATION)
            tr_NAME = tr(STRING.STR_NAME)
            tr_EMAIL = tr(STRING.STR_EMAIL)
            tr_LOGOUT = tr(STRING.STR_LOGOUT)
        }
    }
    //-------------------------------------------------------------------------

    property string name: db.userName // "딥인사이트"
    property string email: db.userEmail // "deep-insight@deepinsight.ai"

    iconPath: "qrc:/resources/images/person_outline.png"
    title: tr_USER_INFORMATION

    onPrevClicked: {
        mainLoader.source = "Settings.qml"
    }

    Column {
        id: frame_8214

        width: 800; height: 400
        x: 735
        y: 414
        spacing: 60

        SettingsDelegate2 {
            key: tr_NAME
            value: name
        }

        SettingsDelegate2 {
            key: tr_EMAIL
            value: email
        }
    }

    TextButton {
        width: 800; height: 96
        x: 735
        y: 1178
        buttonText: tr_LOGOUT
    }
}
