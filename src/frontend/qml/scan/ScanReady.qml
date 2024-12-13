import QtQuick 2.0
import "../component"

Item {
    id: root

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_INPUT_SPACE_NAME: tr(STRING.STR_INPUT_SPACE_NAME)
    property string tr_SELECTION_COMPLETE: tr(STRING.STR_SELECTION_COMPLETE)
    property string tr_RETURN_TO_BACK: tr(STRING.STR_RETURN_TO_BACK)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_INPUT_SPACE_NAME = tr(STRING.STR_INPUT_SPACE_NAME)
            tr_SELECTION_COMPLETE = tr(STRING.STR_SELECTION_COMPLETE)
            tr_RETURN_TO_BACK = tr(STRING.STR_RETURN_TO_BACK)
        }
    }
    //-------------------------------------------------------------------------

    Component.onCompleted: {
        db.updateScanNameList()
    }

    PretendardText {
        width: 452; height: 53
        x: 909
        y: 250
        fontWeight: 400
        size: 44

        text: tr_INPUT_SPACE_NAME
        color: "#FFFFFF"
    }
    TextField {
        id: spaceName

        width: 800; height: 96
        x: 735
        y: 377
        icon: "qrc:/resources/images/add_box.png"
        displayText: "Untitle-01"

        onTextFieldClicked: {
            app.showKeyboard()
        }
    }
    IntroButton {
        x: 735
        y: 533
        enabled: db.isValidScanName(spaceName.inputText)
        buttonText: tr_SELECTION_COMPLETE
        onClicked: {
            db.createNewScan(spaceName.inputText, spaceModel)

            app.hideKeyboard()

            mainLoader.source = "ScanMain.qml"
            modal.load("qrc:/qml/scan/ScanningPopup.qml", 0, 0)
        }
    }
    PretendardText {
        width: 157; height: 43
        x: 95
        y: keyboard.visible ? 557 : 1257
        fontWeight: 400
        size: 36
        font.underline: true
        color: "#FFFFFF"
        text: "< " + tr_RETURN_TO_BACK

        MouseArea {
            anchors.fill: parent
            onClicked: {
                mainLoader.source = "../settings/LanguageSelection.qml"
                app.hideKeyboard()
            }
        }
    }
}
