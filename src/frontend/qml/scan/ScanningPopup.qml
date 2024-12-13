import QtQuick 2.0
import "../component"

Item {
    id: root

    width: 2270; height: 1420

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_SCANNING_GUIDE_0: tr(STRING.STR_SCANNING_GUIDE_0)
    property string tr_SCANNING_GUIDE_1: tr(STRING.STR_SCANNING_GUIDE_1)


    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_SCANNING_GUIDE_0 = tr(STRING.STR_SCANNING_GUIDE_0)
            tr_SCANNING_GUIDE_1 = tr(STRING.STR_SCANNING_GUIDE_1)
        }
    }
    //-------------------------------------------------------------------------
    Timer {
        interval: 3000
        running: true
        onTriggered: {
            ani.start()
        }
    }
    SequentialAnimation {
        id: ani
        PropertyAnimation {
            target: root
            duration: 100
            easing.type: Easing.OutCubic
            property: "opacity"
            from: 1.0
            to: 0.0
        }
        ScriptAction {
            script: modal.unload()
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "#FFFFFF"

        Rectangle {
            anchors.fill: parent
            color: "#000000"
            opacity: 0.6

        }
    }

    Loading {
        id: loading

        type: 2
        width: 363; height: 378
        x: 953
        y: 389
        interval: 200

        Component.onCompleted: {
            start()
        }
    }

    Column {
        width: 785; height: 144
        x: 742
        y: 887

        PretendardText {
            width: 785; height: 72
            fontWeight: 400
            size: 60
            color: "#FFFFFF"
            text: tr_SCANNING_GUIDE_0
            horizontalAlignment: Text.AlignHCenter
        }
        PretendardText {
            width: 785; height: 72
            fontWeight: 700
            size: 60
            color: "#FFFFFF"
            text: tr_SCANNING_GUIDE_1
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
