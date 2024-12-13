import QtQuick 2.0
import "component"

Item {
    id: root

    ListModel {
        id: viewModel

        ListElement {
            name: "1. Intro"
            main: "intro/Intro.qml"
            popup: ""
        }
        ListElement {
            name: "2.1 언어 설정"
            main: "settings/SettingsMain.qml"
            popup: ""
        }
        ListElement {
            name: "2.2 네트워크 설정"
            main: "settings/SettingsMain22.qml"
            popup: ""
        }
        ListElement {
            name: "2.3 로그인"
            main: "settings/SettingsMain23.qml"
            popup: ""
        }
        ListElement {
            name: "3.1 라이다 부팅"
            main: "menu/Menu.qml"
            popup: ""
        }
        ListElement {
            name: "4.1 스캔 시작 전"
            main: "scan/ScanReady.qml"
            popup: ""
        }
        ListElement {
            name: "4.2 스캔 중 시작 팝업"
            main: "scan/ScanningPopup.qml"
            popup: ""
        }
        ListElement {
            name: "4.2 (2) 스캔 중"
            main: "scan/ScanMain.qml"
            popup: ""
        }
        ListElement {
            name: "4.2 (4) 스캔 완료"
            main: "scan/ScanMain.qml"
            popup: "qrc:/qml/scan/ScanningLowDensityPopup.qml"
        }
        ListElement {
            name: "4.3 스캔 완료"
            main: "scan/ScanMain43.qml"
            popup: "qrc:/qml/scan/ScanCompleteLoading.qml"
        }
        ListElement {
            name: "5. 데이터 리스트"
            main: "datalist/DataListMain.qml"
            popup: ""
        }
        ListElement {
            name: "5.1 데이터 전송"
            main: "datalist/DataTransfer.qml"
            popup: ""
        }
        ListElement {
            name: "6. 설정"
            main: "settings/Settings.qml"
            popup: ""
        }
    }
    ListView {
        id: view

        width: parent.width; height: parent.height - 66
        y: 66

        spacing: 8

        model: viewModel

        delegate: Rectangle {
            width: parent.width - 64; height: 64
            x: 32
            y: 64
            radius: 4
            color: "lightsteelblue"

            PretendardText {
                height: parent.height
                verticalAlignment: Text.AlignVCenter
                x: 16
                fontWeight: 400
                size: 48
                text: name
                color: "#D20103"
            }
            PretendardText {
                height: parent.height
                verticalAlignment: Text.AlignVCenter
                x: 16+512
                fontWeight: 400
                size: 40
                text: "qrc:/qml/" + main
                color: "black"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    mainLoader.source = main
                    if (popup.length) {
                        modal.load(popup, 0, 0)
                    } else {
                        modal.unload()
                    }
                }
            }
        }
    }
}
