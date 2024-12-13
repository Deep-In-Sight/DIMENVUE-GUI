import QtQuick 2.0

SettingsBase {
    id: root

    property string modelName: db.modelName // "deep-insight01"
    property string serialNumber: db.serialNumber // "D123456789"
    property string version: db.firmwareVersion // "V 1.8.16"

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_PRODUCT_SETTING: tr(STRING.STR_PRODUCT_SETTING)
    property string tr_MODEL_NAME: tr(STRING.STR_MODEL_NAME)
    property string tr_SERIAL_NUMBER: tr(STRING.STR_SERIAL_NUMBER)
    property string tr_VERSION: tr(STRING.STR_VERSION)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_PRODUCT_SETTING = tr(STRING.STR_PRODUCT_SETTING)
            tr_MODEL_NAME = tr(STRING.STR_MODEL_NAME)
            tr_SERIAL_NUMBER = tr(STRING.STR_SERIAL_NUMBER)
            tr_VERSION = tr(STRING.STR_VERSION)
        }
    }
    //-------------------------------------------------------------------------

    iconPath: "qrc:/resources/images/settings_overscan.png"
    title: tr_PRODUCT_SETTING

    onPrevClicked: {
        mainLoader.source = "Settings.qml"
    }

    Column {
        width: 800; height: 630
        x: 735
        y: 414
        spacing: 60

        SettingsDelegate2 {
            key: tr_MODEL_NAME
            value: modelName
        }
        SettingsDelegate2 {
            key: tr_SERIAL_NUMBER
            value: serialNumber
        }
        SettingsDelegate2 {
            key: tr_VERSION
            value: version
        }
    }
}
