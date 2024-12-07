import QtQuick 2.0

Item {
    function processKoreanKey(c) {
        var a

        switch (c) {
        case 'ㅂ': a = 'q';  break;  case 'ㅃ': a = 'Q';  break
        case 'ㅈ': a = 'w';  break;  case 'ㅉ': a = 'W';  break
        case 'ㄷ': a = 'e';  break;  case 'ㄸ': a = 'E';  break
        case 'ㄱ': a = 'r';  break;  case 'ㄲ': a = 'R';  break
        case 'ㅅ': a = 't';  break;  case 'ㅆ': a = 'T';  break
        case 'ㅛ': a = 'y';  break
        case 'ㅕ': a = 'u';  break
        case 'ㅑ': a = 'i';  break
        case 'ㅐ': a = 'o';  break
        case 'ㅔ': a = 'p';  break
        case 'ㅁ': a = 'a';  break
        case 'ㄴ': a = 's';  break
        case 'ㅇ': a = 'd';  break
        case 'ㄹ': a = 'f';  break
        case 'ㅎ': a = 'g';  break
        case 'ㅗ': a = 'h';  break
        case 'ㅓ': a = 'j';  break
        case 'ㅏ': a = 'k';  break
        case 'ㅣ': a = 'l';  break
        case 'ㅋ': a = 'z';  break
        case 'ㅌ': a = 'x';  break
        case 'ㅊ': a = 'c';  break
        case 'ㅍ': a = 'v';  break
        case 'ㅠ': a = 'b';  break
        case 'ㅜ': a = 'n';  break
        case 'ㅡ': a = 'm';  break
        default:
            return c
        }
        return a
    }
}
