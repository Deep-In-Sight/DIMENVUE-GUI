import QtQuick 2.0

Item {
    property var line0: ListModel {
        ListElement { centerText: "ㅂ"; upperText: "ㅃ"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅈ"; upperText: "ㅉ"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㄷ"; upperText: "ㄸ"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㄱ"; upperText: "ㄲ"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅅ"; upperText: "ㅆ"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅛ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅕ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅑ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅐ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅔ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "";   upperText: "";  specialKey: "Back"; keyWidth: 140 }
    }
    property var line1: ListModel {
        ListElement { centerText: "ㅁ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㄴ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅇ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㄹ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅎ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅗ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅓ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅏ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅣ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "";   upperText: "";  specialKey: "Enter"; keyWidth: 280 }
    }
    property var line2 : ListModel {
        ListElement { centerText: "";   upperText: "";  specialKey: "Shift"; keyWidth: 140 }
        ListElement { centerText: "ㅋ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅌ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅊ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅍ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅠ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅜ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "ㅡ"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: ",";  upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: ".";  upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "";   upperText: "";  specialKey: "Shift"; keyWidth: 140 }
    }
    property var line3 : ListModel {
        ListElement { centerText: "";   upperText: "";  specialKey: "Numeric"; keyWidth: 280 }
        ListElement { centerText: "";   upperText: "";  specialKey: "International"; keyWidth: 140 }
        ListElement { centerText: "";   upperText: "";  specialKey: "Space"; keyWidth: 900 }
        ListElement { centerText: "'";  upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "";   upperText: "";  specialKey: "Hide"; keyWidth: 280 }
    }
}
