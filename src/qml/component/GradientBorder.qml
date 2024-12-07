import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: root
    //property Gradient borderGradient
    property int borderWidth: 0
    property int radius
    property alias start: linearGradient.start
    property alias end: linearGradient.end
    property alias gradient: linearGradient.gradient

    LinearGradient {
        id: linearGradient
        anchors.fill: parent
        visible: false
    }

    Rectangle {
        id: mask
        radius: root.radius
        border.width: root.borderWidth
        anchors.fill: parent
        color: 'transparent'
        visible: false
    }

    OpacityMask {
        id: opacityMask
        anchors.fill: parent
        source: linearGradient
        maskSource: mask
    }
}
