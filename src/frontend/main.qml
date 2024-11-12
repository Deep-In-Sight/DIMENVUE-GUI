import QtQuick 2.12          
import QtQuick.Controls 2.5  
import OgreComponents 1.0

Rectangle {
    visible: true
    width: 800
    height: 700

    Column {
        anchors.centerIn: parent
        anchors.fill: parent
        spacing: 20

        QOgreItem {
            anchors.horizontalCenter: parent.horizontalCenter
            id: customImageNode
            width: 800
            height: 600
        }

        Button {
            text: qsTr("Click me")
            anchors.horizontalCenter: parent.horizontalCenter

        }
    }
}
