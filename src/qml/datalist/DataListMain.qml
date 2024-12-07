import QtQuick 2.0
import "../component"

Item {
    id: root

    //-------------------------------------------------------------------------
    //  Translations
    //-------------------------------------------------------------------------
    property string tr_SPACE_DATA_LIST: tr(STRING.STR_SPACE_DATA_LIST)
    property string tr_DATA_EXPORT: tr(STRING.STR_DATA_EXPORT)
    property string tr_IMAGE: tr(STRING.STR_IMAGE)
    property string tr_SPACE_NAME: tr(STRING.STR_SPACE_NAME)
    property string tr_AREA: tr(STRING.STR_AREA)
    property string tr_SPACE_SCAN_TIME: tr(STRING.STR_SPACE_SCAN_TIME)
    property string tr_SELECT_ALL: tr(STRING.STR_SELECT_ALL)
    property string tr_SELECT_DELETE: tr(STRING.STR_SELECT_DELETE)

    function tr(key) {
        return STRING.translate(key)
    }

    Connections {
        target: STRING
        onLanguageChanged: {
            tr_SPACE_DATA_LIST = tr(STRING.STR_SPACE_DATA_LIST)
            tr_DATA_EXPORT = tr(STRING.STR_DATA_EXPORT)
            tr_IMAGE = tr(STRING.STR_IMAGE)
            tr_SPACE_NAME = tr(STRING.STR_SPACE_NAME)
            tr_AREA = tr(STRING.STR_AREA)
            tr_SPACE_SCAN_TIME = tr(STRING.STR_SPACE_SCAN_TIME)
            tr_SELECT_ALL = tr(STRING.STR_SELECT_ALL)
            tr_SELECT_DELETE = tr(STRING.STR_SELECT_DELETE)
        }
    }
    //-------------------------------------------------------------------------

    property bool syncOk: false
    property bool deleting: false
    property int viewType: 0    //0: listView
                                //1: gridView

    Component.onCompleted: {
        if (viewType === 0) {
            listViewBtn.selected = true
        } else {
            gridViewBtn.selected = true
        }
    }
    Connections {
        target: monitor
        onDeleteScanDone: {
            console.log('onDeleteScanDone: ' + value)
            deleteButton.enabled = true
            deleting = false
            if (value) {
                spaceModel.removeChecked()
            }
        }
    }

    PretendardText {
        width: 393; height: 72
        x: 72
        y: 116
        fontWeight: 500
        size: 60
        text: tr_SPACE_DATA_LIST
        color: "#8E9DAF"
    }

    Row {
        id: frame_200

        width: 535; height: 60
        x: 1663 + setting.offsetX
        y: 114

        spacing: 24

        Image {
            width: 52; height: 48
            source: "qrc:/resources/images/home.png"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    mainLoader.source = "../menu/Menu.qml"
                }
            }
        }
        Rectangle {
            width: 3; height: 60
            color: "#313B47"
        }
        User {
            userName: db.userName
        }
        Rectangle {
            width: 3; height: 60
            color: "#313B47"
        }
        Setting {
            id: setting

            onClicked: {
                mainLoader.stackedLoad("settings/Settings.qml")
            }
        }
    }
    Row {
        id: frame_199

        width: 793; height: 64
        x: 1406
        y: 274
        spacing: 24

        Item {
            width: 64; height: 64
            Image {
                anchors.centerIn: parent
                width: 36; height: 36
                source: syncOk ? "qrc:/resources/images/cloud_done.png" : "qrc:/resources/images/sync_problem.png"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (!syncOk) {
                            modal.loadFullscreen("qrc:/qml/popup/DataListSyncPopup.qml", 0, 0)
                        }
                    }
                }
            }
        }
        Rectangle {
            width: 3; height: 60
            color: "#313B47"
        }
        Row {
            id: frame_180
            width: 144; height: 64
            spacing: 16

            Item {
                width: 64; height: 64
                IconButton {
                    id: listViewBtn

                    width: 64; height: 64
                    radius: 16
                    pressedColor: "#2079FF"
                    normalColor: Qt.rgba(1,1,1,0.1)
                    iconPath: "qrc:/resources/images/list_p.png"
                    onClicked: {
                        viewType = 0
                        gridViewBtn.selected = false
                    }
                }
            }
            Item {
                width: 64; height: 64
                IconButton {
                    id: gridViewBtn

                    width: 64; height: 64
                    radius: 16
                    pressedColor: "#2079FF"
                    normalColor: Qt.rgba(1,1,1,0.1)
                    iconPath: "qrc:/resources/images/grid.png"

                    onClicked: {
                        viewType = 1
                        listViewBtn.selected = false
                    }
                }
            }
        }
        Rectangle {
            width: 3; height: 60
            color: "#313B47"
        }
        ButtonList {
            id: deleteButton

            width: 192; height: 64
            iconPath: "qrc:/resources/images/delete_outline.png"
            buttonText: tr_SELECT_DELETE
            onClicked: {
                deleteButton.enabled = false
                deleting = true

                console.log(buttonText + " clicked.")
                //spaceModel.removeChecked()
                app.removeChecked()
            }
        }
        ButtonSmall {
            width: 273; height: 64
            iconPath: "qrc:/resources/images/file_upload.png"
            buttonText: tr_DATA_EXPORT
        }
    }
    //=========================================================================
    //  Header
    //=========================================================================
    DataListHeader {
        id: header
        isListView: viewType == 0
    }
    //=========================================================================
    //  List
    //=========================================================================
    ListView {
        id: listView
        visible: viewType == 0
        width: 2126; height: 904
        x: 72
        y: 482
        spacing: 16
        delegate: DataListDelegate {
            enabled: !deleting
        }
        model: proxyModel //spaceModel
        clip: true
    }
    GridView {
        id: gridView
        visible: viewType == 1
        width: 2127+24; height: 1152
        x: 71
        y: 482

        cellWidth: 694+12
        cellHeight: 482+24
        delegate: DataGridDelegate {
            enabled: !deleting
        }
        model: proxyModel //spaceModel
        clip: true

        footer: Item {
            width: parent.width; height: gridView.cellHeight/2
        }
    }

    //=========================================================================
    //  Footer
    //=========================================================================
    DataStorageInfo {
        usage: 270
    }
}
