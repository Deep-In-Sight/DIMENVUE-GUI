import QtQuick 2.0
import "../component"

Item {
    id: root

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_RESTART: tr(STRING.STR_RESTART)
    property string tr_EXIT: tr(STRING.STR_EXIT)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_RESTART = tr(STRING.STR_RESTART)
            tr_EXIT = tr(STRING.STR_EXIT)
        }
    }
    //-------------------------------------------------------------------------

    Connections {
        target: modal
        onBgClicked: {
            disableBlur()
            modal.unload()
        }
    }

    //-------------------------------------------------------------------------

    Component.onCompleted: {
        enableBlur()
    }

    Rectangle {
        width: 2270; height: 1354
        y: 66
        color: Qt.rgba(0,0,0,0.6)
    }

    Rectangle {
        width: 384; height: 216
        x: 1854
        y: 118
        radius: 16
        color: "#1D2937"

        Column {
            width: 360; height: 192
            x: 12
            y: 12

            Item {
                width: 360; height: 96
                PretendardText {
                    anchors.centerIn: parent
                    fontWeight: 400
                    size: 36
                    color: "#FFFFFF"
                    text: tr_RESTART
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("Restart !!!")
                        modal.unload()

                        disableBlur()

                        //-----------------------------------------------------
                        //  for DEBUG
                        //-----------------------------------------------------
                        loadDebugvue()
                    }
                }
            }
            Item {
                width: 360; height: 96
                PretendardText {
                    anchors.centerIn: parent
                    fontWeight: 400
                    size: 36
                    color: "#FFFFFF"
                    text: tr_EXIT
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("Power Off !!!")
                        modal.unload()
                        app.quit()
                    }
                }
            }
        }
    }
}
