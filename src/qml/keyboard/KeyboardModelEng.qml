import QtQuick 2.0

Item {
    property var line0: ListModel {
        ListElement { centerText: "q"; upperText: "Q"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "w"; upperText: "W"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "e"; upperText: "E"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "r"; upperText: "R"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "t"; upperText: "T"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "y"; upperText: "Y"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "u"; upperText: "U"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "i"; upperText: "I"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "o"; upperText: "O"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "p"; upperText: "P"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "";   upperText: "";  specialKey: "Back"; keyWidth: 140 }
    }
    property var line1: ListModel {
        ListElement { centerText: "a"; upperText: "A"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "s"; upperText: "S"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "d"; upperText: "D"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "f"; upperText: "F"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "g"; upperText: "G"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "h"; upperText: "H"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "j"; upperText: "J"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "k"; upperText: "K"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "l"; upperText: "L"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "";   upperText: "";  specialKey: "Enter"; keyWidth: 280 }
    }
    property var line2 : ListModel {
        ListElement { centerText: "";   upperText: "";  specialKey: "Shift"; keyWidth: 140 }
        ListElement { centerText: "z"; upperText: "Z"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "x"; upperText: "X"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "c"; upperText: "C"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "v"; upperText: "V"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "b"; upperText: "B"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "n"; upperText: "N"; specialKey: ""; keyWidth: 140 }
        ListElement { centerText: "m"; upperText: "M"; specialKey: ""; keyWidth: 140 }
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
