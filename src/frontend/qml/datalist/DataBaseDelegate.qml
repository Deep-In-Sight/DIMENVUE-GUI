import QtQuick 2.0

Item {
    property int index
    property string spaceName
    property url imageUrl
    property string areaText
    property string dateText
    property bool selected: false

    signal checkClicked()
}
