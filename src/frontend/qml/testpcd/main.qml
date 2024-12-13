import QtQuick 2.12          
import QtQuick.Controls 2.5  
import DimenvueComponents 1.0

Rectangle {
    visible: true
    width: 800
    height: 700

    ImGuiItem {
        id: imguiItem
        anchors.fill: parent
        visible: true
        z: 100
    }

    Column {
        anchors.centerIn: parent
        anchors.fill: parent
        spacing: 20

        // QOgreItem {
        //     anchors.horizontalCenter: parent.horizontalCenter
        //     id: customImageNode
        //     width: parent.width
        //     height: width * 0.75
        // }

        OpenGLItem {
            id: glItem
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: width * 0.75
            visible: true
            z: 0
        }

        Button {
            text: qsTr("Click me")
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
