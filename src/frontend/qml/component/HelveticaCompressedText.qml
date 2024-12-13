import QtQuick 2.0

Text {
    id: root

    property int size: 32
    property alias fontWeight: root.font.weight

    font.family: "Pretendard"
    font.pixelSize: root.size
}
