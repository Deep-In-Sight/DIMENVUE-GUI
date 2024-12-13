import QtQuick 2.0
import "../component"
import com.dimenvue 1.0

Item {
    id: root

    property bool isListView: false

    function setSortRoleUp(role) {
        app.setSortRole(role, 1)
    }
    function setSortRoleDown(role) {
        app.setSortRole(role, 0)
    }

    Row {
        id: frame_182

        visible: isListView
        width: 196; height: 36
        x: 1681
        y: 403
        spacing: 16

        PretendardText {
            width: 156; height: 36
            fontWeight: 700
            size: 30
            color: "#FFFFFF"
            text: tr_SPACE_SCAN_TIME
        }
        SpinBox {
            anchors.verticalCenter: parent.verticalCenter
            onUpClicked: {
                setSortRoleUp(SpaceDataModel.SpaceScanTimeRole)
            }
            onDownClicked: {
                setSortRoleDown(SpaceDataModel.SpaceScanTimeRole)
            }
        }
    }
    Row {
        id: frame_183

        visible: isListView
        width: 92; height: 36
        x: 1495
        y: 403
        spacing: 16

        PretendardText {
            width: Math.max(52, contentWidth); height: 36
            fontWeight: 700
            size: 30
            color: "#FFFFFF"
            text: tr_AREA
        }
        SpinBox {
            anchors.verticalCenter: parent.verticalCenter
            onUpClicked: {
                setSortRoleUp(SpaceDataModel.SpaceAreaRole)
            }
            onDownClicked: {
                setSortRoleDown(SpaceDataModel.SpaceAreaRole)
            }
        }
    }
    Row {
        id: frame_187

        visible: isListView
        width: 118; height: 36
        x: 520
        y: 403
        spacing: 16

        PretendardText {
            width: Math.max(78, contentWidth); height: 36
            fontWeight: 700
            size: 30
            color: "#FFFFFF"
            text: tr_SPACE_NAME
        }
        SpinBox {
            anchors.verticalCenter: parent.verticalCenter
            onUpClicked: {
                setSortRoleUp(SpaceDataModel.SpaceNameRole)
            }
            onDownClicked: {
                setSortRoleDown(SpaceDataModel.SpaceNameRole)
            }
        }
    }
    PretendardText {
        visible: isListView
        width: 78; height: 36
        x: 321
        y: 403
        fontWeight: 700
        size: 30
        color: "#FFFFFF"
        text: tr_IMAGE
    }
    Row {
        width: 162; height: 48
        x: isListView ? 110 : 104
        y: 398
        spacing: 24

        CheckButton {
            id: checkAllBtn

            onClicked: {
                check = !check
                if (check) {
                    spaceModel.checkAll()
                } else {
                    spaceModel.uncheckAll()
                }
            }
        }

        PretendardText {
            width: 90; height: 36
            fontWeight: 700
            size: 36
            color: "#FFFFFF"
            text: isListView ? "No" : tr_SELECT_ALL

            SpinBox {
                visible: isListView
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                onUpClicked: {
                    setSortRoleUp(SpaceDataModel.IndexRole)
                }
                onDownClicked: {
                    setSortRoleDown(SpaceDataModel.IndexRole)
                }
            }
        }
    }
}
