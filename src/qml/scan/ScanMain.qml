import QtQuick 2.0

Item {
    id: scanMain

    objectName: "scanMain"

    property bool loaderVisible: true
    property alias mainSource: loader.source
    property alias popupSource: popupLoader.source
    property alias dataDensityVisible: statusBar.dataDensityVisible

    function load(url) {
        loader.source = url
    }

    Rectangle {
        anchors.fill: parent
        color: "#000000"
    }

    Image {
        id: sample
        width: 2100; height: 1316
        x: 170
        y: 8
        source: "qrc:/resources/images/image_2.png"
    }

    Loader {
        id: loader

        anchors.fill: parent
        source: "Scanning.qml"

        visible: loaderVisible
    }
    ScanControl {
        id: scanControl

        onZoomInClicked: {
            db.zoomIn()
        }
        onZoomOutClicked: {
            db.zoomOut()
        }
    }

    StatusBar {
        id: statusBar

        measureUnit: "10m"
        dataDensityVisible: true
    }

    Loader {
        id: popupLoader
        anchors.fill: parent
        //source: "ScanningCompletePopup.qml"
        //source: "ScanCompleteLoading.qml"
    }
}
