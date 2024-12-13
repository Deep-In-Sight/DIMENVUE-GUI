#ifndef KOREANCHARMAKER_H
#define KOREANCHARMAKER_H

#include <QString>
#include <QStringList>
#include <QTextCodec>

namespace Automata
{
    /// <summary>
    /// 문자의 키 값을 완성형 한글로 변형해주는 정적 클래스/
    /// </summary>
    class KoreanCharMaker
    {
    public:
        KoreanCharMaker()
        {}
        ~KoreanCharMaker()
        {}

        const int BASE_CODE = 0xAC00;
        const int BASE_INIT = 0x1100;
        const int BASE_VOWEL = 0x1161;
        QString nonshiftkey_str = "ABCDFGHIJKLMNSUVXYZ";

        QString nonshiftkey_kstr = "ㅁㅠㅊㅇㄹㅎㅗㅑㅓㅏㅣㅡㅜㄴㅕㅍㅌㅛㅋ";
        QString chostring = "rRseEfaqQtTdwWczxvg";
        QString chostring_k = "ㄱㄲㄴㄷㄸㄹㅁㅂㅃㅅㅆㅇㅈㅉㅊㅋㅌㅍㅎ";
        QStringList jungstrs = { "k", "o", "i", "O", "j", "p", "u", "P", "h", "hk", "ho", "hl", "y", "n", "nj", "np", "nl", "b", "m", "ml", "l" };
        QStringList jungstrs_k = {"ㅏ","ㅐ","ㅑ","ㅒ","ㅓ","ㅔ","ㅕ","ㅖ","ㅗ","ㅘ","ㅙ","ㅚ","ㅛ","ㅜ","ㅝ","ㅞ","ㅟ","ㅠ","ㅡ","ㅢ","ㅣ"};;
        QStringList jongstrs = { "", "r", "R", "rt", "s", "sw", "sg", "e", "f", "fr", "fa", "fq", "ft", "fx", "fv", "fg", "a", "q", "qt", "t", "T", "d", "w", "c", "z", "x", "v", "g" };
        QStringList jongstrs_k = { "", "ㄱ", "ㄲ", "ㄳ", "ㄴ", "ㄵ", "ㄶ", "ㄷ", "ㄹ", "ㄺ", "ㄻ", "ㄼ", "ㄽ", "ㄾ", "ㄿ", "ㅀ", "ㅁ", "ㅂ", "ㅄ", "ㅅ", "ㅆ", "ㅇ", "ㅈ", "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ" };

        /// <summary>
        /// 문자를 초성 코드 값으로 바꿔주는 메서드
        /// </summary>
        /// <param name="ch">문자</param>
        /// <returns>초성 코드 값</returns>
        int GetInitSoundCode(QChar c)
        {
            QString ch = QString{};
            ch += c;

            int index = chostring_k.indexOf(ch);
            if (index != -1)
            {
                return index;
            }
            return chostring.indexOf(ch);
        }


        /// <summary>
        /// 문자열을 중성(모음) 코드 값으로 바꿔주는 메서드
        /// </summary>
        /// <param name="str">문자열</param>
        /// <returns>중성(모음) 코드 값</returns>
        int GetVowelCode(QString str)
        {
            int cnt = jungstrs.length();
            for (int i = 0; i < cnt; i++)
            {
                if (jungstrs[i] == str)
                {
                    return i;
                }
            }
            for (int i = 0; i < cnt; i++)
            {
                if (jungstrs_k[i] == str)
                {
                    return i;
                }
            }
            return -1;
        }
        /// <summary>
        /// 문자의 중성 코드 값 바꿔주는 메서드
        /// </summary>
        /// <param name="ch">문자</param>
        /// <returns>중성 코드 값</returns>
        int GetVowelCode(QChar ch)
        {
            QString s;

            s += ch;

            return GetVowelCode(s);
        }
        /// <summary>
        /// 문자열을 종성 코드 값으로 바꿔주는 메서드
        /// </summary>
        /// <param name="str">문자열</param>
        /// <returns>종성 코드 값</returns>
        int GetFinalConsonantCode(QString str)
        {
            int cnt = jongstrs.length();
            for (int i = 0; i < cnt; i++)
            {
                if (jongstrs[i] == str)
                {
                    return i;
                }
            }
            for (int i = 0; i < cnt; i++)
            {
                if (jongstrs_k[i] == str)
                {
                    return i;
                }
            }
            return -1;
        }
        /// <summary>
        /// 문자를 종성 코드 값으로 바꿔주는 메서드
        /// </summary>
        /// <param name="ch">문자</param>
        /// <returns>종성 코드 값</returns>
        int GetFinalConsonantCode(QChar ch)
        {
            QString s;

            s += ch;

            return GetFinalConsonantCode(s);
        }

        QChar decodeUniCodeFromInt(unsigned short completeChar)
        {
#if (0)
            auto naeBytes = QByteArray::fromRawData((const char*)&completeChar, sizeof(short));
            QTextCodec* codec = QTextCodec::codecForName("eucKR");
            QString s = codec->toUnicode(naeBytes);
            QChar c = s[0];

            return c;
#else
            QChar c = completeChar;

            return c;
#endif
        }
        /// <summary>
        /// 하나의 자음으로 글자를 만드는 메서드
        /// </summary>
        /// <param name="value">키 값</param>
        /// <returns>완성형 글자</returns>
        QChar GetSingleJa(int value)
        {
//            byte[] bytes = BitConverter.GetBytes((short)(BASE_INIT + value));
//            return Char.Parse(Encoding.Unicode.GetString(bytes));

            return decodeUniCodeFromInt(BASE_INIT + value);
        }

        /// <summary>
        /// 하나의 모음으로 글자를 만드는 메서드
        /// </summary>
        /// <param name="value">키 값</param>
        /// <returns>완성형 글자</returns>
        QChar GetSingleVowel(int value)
        {
//            byte[] bytes = BitConverter.GetBytes((short)(BASE_VOWEL + value));
//            return Char.Parse(Encoding.Unicode.GetString(bytes));

            return decodeUniCodeFromInt(BASE_VOWEL + value);
        }

        /// <summary>
        /// 초성, 중성, 종성 코드로 하나의 글자를 만드는 메서드
        /// </summary>
        /// <param name="init_sound">초성</param>
        /// <param name="vowel">중성</param>
        /// <param name="final">종성</param>
        /// <returns>완성형 글자</returns>
        QChar GetCompleteChar(int init_sound, int vowel, int final)
        {
            int tempFinalConsonant = 0;
            if (final >= 0)
            {
                tempFinalConsonant = final;
            }

            int jungcnt = jungstrs.length();
            int jongcnt = jongstrs.length();
            int completeChar = init_sound * jungcnt * jongcnt + vowel * jongcnt + tempFinalConsonant + BASE_CODE;

//            byte[] naeBytes = BitConverter.GetBytes((short)(completeChar));
//            return Char.Parse(Encoding.Unicode.GetString(naeBytes));
            return decodeUniCodeFromInt(completeChar);
        }
        /// <summary>
        /// 쉬프트 키가 필요없는 문자를 소문자로 바꿔주는 메서드
        /// </summary>
        /// <param name="ch">문자</param>
        /// <returns>바뀐 문자</returns>
        QChar NonShiftKeyToLower(QChar ch)
        {
            QString s;

            s += ch;

            if (nonshiftkey_str.contains(s))
            {
                return ch.toLower();// Char.ToLower(ch);
            }
            int index =  nonshiftkey_kstr.indexOf(ch);
            if (index !=-1)
            {
                return tolower(nonshiftkey_str[index].toLatin1()); // Char.ToLower(nonshiftkey_str[index]);
            }
            return ch;
        }

        /// <summary>
        /// 이중 받침이 가능한 문자인지 확인하는 메서드
        /// </summary>
        /// <param name="ch">문자</param>
        /// <returns>이중 받침 가능 여부</returns>
        bool EnableDoubleFinalConsonant(char ch)
        {
            int code = GetFinalConsonantCode(ch);
            return code == 1 || code == 4 || code == 8 || code == 17;
        }
        /// <summary>
        /// 이중 모음이 가능한 문자인지 확인하는 메서드
        /// </summary>
        /// <param name="ch">문자</param>
        /// <returns>이중 모음 가능 여부</returns>
        bool EnableDoubleVowel(char ch)
        {
            int code = GetVowelCode(ch);
            return EnableDoubleVowel(code);
        }
        bool IsInitSound(char ch)
        {
            return GetInitSoundCode(ch) != -1;
        }
        bool IsVowel(QString str)
        {
            return GetVowelCode(str) != -1;
        }

        bool IsCharKey(QChar ch)
        {

            return ch.isLetter();// char.IsLetter(ch);
        }

        bool IsFinalConsonant(QChar ch)
        {
            return GetFinalConsonantCode(ch) != -1;
        }

        bool EnableDoubleVowel(int code)
        {
            return (code == 8) || (code == 13) || (code == 18);
        }
    };
}

#endif
