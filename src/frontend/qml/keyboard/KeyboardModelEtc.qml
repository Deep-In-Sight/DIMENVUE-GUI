import QtQuick 2.0

Item {
    property var line0: ListModel {
        ListElement { centerText: "1"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "2"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "3"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "4"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "5"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "6"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "7"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "8"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "9"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "0"; upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "";   upperText: "";  specialKey: "Back"; keyWidth: 140 }
    }
    property var line1: ListModel {
        ListElement { centerText: "@"; upperText: "$"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "#"; upperText: "€"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "\₩"; upperText: "¥"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "&"; upperText: "_"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "^"; upperText: "*"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "["; upperText: "("; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "]"; upperText: ")"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "'"; upperText: "{"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "\""; upperText: "}"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "";   upperText: "";  specialKey: "Enter"; keyWidth: 280 }
    }
    property var line2 : ListModel {
        ListElement { centerText: "";   upperText: "";  specialKey: "Shift"; keyWidth: 140 }
        ListElement { centerText: "%"; upperText: "&"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "-"; upperText: "|"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "+"; upperText: "~"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "="; upperText: "="; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "/"; upperText: "\\"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: ":"; upperText: "<"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: ";"; upperText: ">"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "`";  upperText: "!"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: ".";  upperText: "?"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "";   upperText: "";  specialKey: "Shift"; keyWidth: 140 }
    }
    property var line3 : ListModel {
        ListElement { centerText: "";   upperText: "";  specialKey: "Kor"; keyWidth: 280 }
        ListElement { centerText: "";   upperText: "";  specialKey: "International"; keyWidth: 140 }
        ListElement { centerText: "";   upperText: "";  specialKey: "Space"; keyWidth: 900 }
        ListElement { centerText: "'";  upperText: ""; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "";   upperText: "";  specialKey: "Hide"; keyWidth: 280 }
    }
}
