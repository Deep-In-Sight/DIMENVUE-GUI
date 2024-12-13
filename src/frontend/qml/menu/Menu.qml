import QtQuick 2.0
import "../component"

Item {
    id: root

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_SCANNING_THE_SPACE_GUIDE: tr(STRING.STR_SCANNING_THE_SPACE_GUIDE)
    property string tr_SPACE_DATA_LIST_GUIDE: tr(STRING.STR_SPACE_DATA_LIST_GUIDE)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_SCANNING_THE_SPACE_GUIDE = tr(STRING.STR_SCANNING_THE_SPACE_GUIDE)
            tr_SPACE_DATA_LIST_GUIDE = tr(STRING.STR_SPACE_DATA_LIST_GUIDE)
        }
    }
    //-------------------------------------------------------------------------

    property bool enableScanningTheSpace: db.sensorInitialized

    Component.onCompleted: {
        db.initializeSensor()
    }
    Connections {
        target: monitor
        onInitializeSensorDone: {
            console.log("onInitializeSensorDone: " + value)
            enableScanningTheSpace = value;
        }
    }

    Row {
        id: frame_200

        width: 435; height: 60
        x: 1787 + setting.offsetX
        y: 114
        spacing: 24

        User {
            anchors.right: setting.left
            anchors.rightMargin: 24
            userName: db.userName
        }

        Setting {
            id: setting
            anchors.right: parent.right
            onClicked: {
                mainLoader.stackedLoad("settings/Settings.qml")
            }
        }
    }

    Image {
        width: 400; height: 200
        x: 935
        y: 190
        source: "qrc:/resources/images/Logo_White_1.png"
    }
    Row {
        id: frame_8204

        width: 1480; height: 700
        x: 395
        y: 438
        spacing: 120

        MenuButton {
            width: 680; height: 700
            icon: enableScanningTheSpace ? "qrc:/resources/images/group_131.png" : ""
            mainText: "Scanning the space"
            subText: tr_SCANNING_THE_SPACE_GUIDE
            gradientBackground: enableScanningTheSpace
            imageWidth: enableScanningTheSpace ? 200 : 103
            imageHeight: enableScanningTheSpace ? 200 : 56

            Loading {
                id: loadingImage
                visible: !enableScanningTheSpace
                width: 233; height: 210
                x: 233
                y: 175

                Component.onCompleted: {
                    start()
                }
            }
            onClicked: {
                if (enableScanningTheSpace) {
                    mainLoader.source = "../scan/ScanReady.qml"
                }
            }
        }
        MenuButton {
            width: 680; height: 700
            imageWidth: 185
            imageHeight: 200
            icon: "qrc:/resources/images/group_124.png"
            mainText: "space data list"
            subText: tr_SPACE_DATA_LIST_GUIDE
            onClicked: {
                db.updateModelData(spaceModel)
                mainLoader.source = "../datalist/DataListMain.qml"
            }
        }
    } //frame_8204

    PretendardText {
        width: 276; height: 38
        x: 997
        y: 1312
        size: 32
        color: "#FFFFFF"
        text: "DIMENVUE V 1.8.16"
    }
}
