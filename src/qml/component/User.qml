import QtQuick 2.0

Row {
    id: frame_29

    property string userName

    width: Math.max(userNameText.contentWidth+48+16, 260)
    height: 48
    spacing: 16

    Image {
        width: 48; height: 48
        source: "qrc:/resources/images/account.png"
    }
    PretendardText {
        id: userNameText

        width: 196; height: 43
        fontWeight: 600
        size: 36
        text: userName
        color: "#FFFFFF"
    }
}
