import QtQuick 2.0
import "../component"

Item {
    id: root

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_DATA_LIST_SYNCHRONIZE: tr(STRING.STR_DATA_LIST_SYNCHRONIZE)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_DATA_LIST_SYNCHRONIZE = tr(STRING.STR_DATA_LIST_SYNCHRONIZE)

        }
    }
    //-------------------------------------------------------------------------

    property bool wip: true //organize the scan data

    function fadeOut() {
        dissolve.running = true
    }

    function close() {
        root.visible = false

        console.log("ScanCompleteLoading.qml closed")

        modal.unload()
    }

    width: 2270; height: 1420

    Component.onCompleted: {
        enableBlur()
    }

    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(0,0,0,0.6)
    }
    Item {
        width: 240; height: 240
        x: 1015
        y: 590

        Loading {
            id: loadingImage
            width: 233; height: 210
            anchors.centerIn: parent
            visible: wip
            type: 1

            Component.onCompleted: {
                start()
            }
        }
    }
    PretendardText {
        width: 735; height: 72
        x: 767
        y: 887
        color: "#FFFFFF"
        fontWeight: 400
        size: 60
        text: tr_DATA_LIST_SYNCHRONIZE
    }
    //=========================================================================
    //  Animation
    //=========================================================================
    SequentialAnimation {
        id: dissolve

        PauseAnimation {
            duration: 1500
        }
        NumberAnimation {
            target: root; properties: "opacity"; to: 0.0; duration: 100; easing: Easing.OutCubic
        }
        ScriptAction {
            script: {
                disableBlur()
                close()
            }
        }
    }
    //=========================================================================
    //  Debug (delete later)
    //=========================================================================
    MouseArea {
        anchors.fill: parent
        onClicked: {
            wip = false

            fadeOut()
        }
    }
}
