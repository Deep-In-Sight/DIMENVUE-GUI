#ifndef HANGULSTATE_H
#define HANGULSTATE_H

#include "KoreanCharMaker.h"
#include <QScopedPointer>

namespace Automata
{
    enum HGState
    {
        TURN_INIT_SOUND, //초성을 기대
        TURN_VOWEL, //모음을 기대
        TURN_FINAL_CONSONANT //종성을 기대
    };

    class HangulState
    {
        QScopedPointer<KoreanCharMaker> kcm;

    public:
        const char VOWEL_INIT_CHAR = 0; //char.MinValue;//초성 초기 문자
        const char FINAL_INIT_CHAR = 0; //char.MinValue; //종성 초기 문자

        int init_sound;                 //초성
        int vowel;                       //중성(모음)
        char vowel_first;              //첫 모음
        bool vowelPossible;         //이중 모음이 가능 여부
        int final_conso;               //종성
        char final_consoFirst;       //종성의 첫 받침
        char final_consoLast;       //종성의 마지막 받침(이중 받침일 때 의미가 있음)
        bool final_consoPossible; //이중 받침 가능 여부

        HGState state;

        HGState getState() const
        {
            return state;
        }

        HangulState() : kcm(new KoreanCharMaker)
        {
            Init();
        }
        ~HangulState()
        {}

        void Init()
        {
            state = HGState::TURN_INIT_SOUND;

            init_sound = -1;
            vowel = -1;
            final_conso = -1;

            vowelPossible = false;
            final_consoPossible = false;
            vowel_first = VOWEL_INIT_CHAR;
            final_consoFirst = FINAL_INIT_CHAR;
            final_consoLast = FINAL_INIT_CHAR;
        }
        void SetStateInitSound()
        {
            state = HGState::TURN_INIT_SOUND;
        }

        void SetStateVowel()
        {
            state = HGState::TURN_VOWEL;

            vowel = -1;
            final_conso = -1;

            vowelPossible = false;
            final_consoFirst = FINAL_INIT_CHAR;
            final_consoLast = FINAL_INIT_CHAR;
        }

        void SetStateFinalConsonant()
        {
            state = HGState::TURN_FINAL_CONSONANT;
            final_conso = -1;
            final_consoFirst = FINAL_INIT_CHAR;
            final_consoLast = FINAL_INIT_CHAR;
        }

        QChar GetCompleteChar()
        {
            return kcm->GetCompleteChar(init_sound, vowel, final_conso);
        }

        bool IsDoubleVowel()
        {
            bool check = kcm->EnableDoubleVowel(vowel);

            return vowelPossible && (check == false) && (ExistFristFinalConsonant() == false);
        }

        bool ExistFristFinalConsonant()
        {
            return final_consoFirst != FINAL_INIT_CHAR;
        }
        bool ExistLastFinalConsonant()
        {
            return final_consoLast != FINAL_INIT_CHAR;
        }
        bool IsInitSound()
        {
            return state == HGState::TURN_VOWEL && !ExistVowel();
        }
        bool IsSingleVowel()
        {
            if (vowel != kcm->GetVowelCode(vowel_first))
            {
                return false;
            }
            return (state == HGState::TURN_VOWEL && ExistVowel()) || ((state == HGState::TURN_FINAL_CONSONANT) && (!ExistFinalConsonant()));
        }

        bool ExistVowel()
        {
            return (vowel != VOWEL_INIT_CHAR) && (vowel != -1);
        }
        bool ExistFinalConsonant()
        {
            return (final_conso != FINAL_INIT_CHAR) && (final_conso != -1);
        }
        bool IsSingleFinalConsonant()
        {
            return state == HGState::TURN_FINAL_CONSONANT && ExistFristFinalConsonant() && (!ExistLastFinalConsonant());
        }
        bool IsFull()
        {
            return ExistFristFinalConsonant() && ExistLastFinalConsonant();
        }
        bool EnableDoubleFinalConsonant()
        {
            return final_conso == 1 || final_conso == 4 || final_conso == 8 || final_conso == 17;
        }

        void SetVowel(char ch)
        {
            if (kcm->EnableDoubleVowel(ch))
            {
                vowelPossible = true;
                state = HGState::TURN_VOWEL;
            }
            else
            {
                state = HGState::TURN_FINAL_CONSONANT;
            }
            vowel_first = ch;
        }

        bool InputAtInitSound(QString& source, char ch)
        {
            state = HGState::TURN_VOWEL;
            init_sound = kcm->GetInitSoundCode(ch);
            if (init_sound >= 0)
            {
                source += kcm->GetSingleJa(init_sound);
                return true;
            }
            return false;
        }

        bool InputFirstVowel(QString& source, char ch)
        {
            vowel = kcm->GetVowelCode(ch);
            if (vowel < 0)//모음이 아닐 때
            {
                state = HGState::TURN_INIT_SOUND;
                return false;
            }

            if (init_sound < 0)//초성없이 모음을 먼저 입력
            {
                source += kcm->GetSingleVowel(kcm->GetVowelCode(ch));
                Init();
            }
            else
            {
                SetVowel(ch);
                source = source.mid(0, source.length() - 1);
                source += GetCompleteChar();
            }
            return true;
        }

        bool InputSecondVowel(QString& source, char ch)
        {
            QString tempvowel = "";// string.Empty;
            tempvowel += vowel_first;
            tempvowel += ch;

            int temp = kcm->GetVowelCode(tempvowel);
            if (temp >= 0)   //tempvowel이 모음
            {

                vowel = temp;
                source = source.mid(0, source.length() - 1);
                source += GetCompleteChar();
                SetStateFinalConsonant();
                return true;
            }
            else
            {
                SetStateFinalConsonant();
                return false;
            }
        }

        bool InputFirstFinalConsonant(QString& source, char ch)
        {
            final_conso = kcm->GetFinalConsonantCode(ch);

            if (final_conso > 0)
            {
                source = source.mid(0, source.length() - 1);
                source += GetCompleteChar();
                SetFirstFinalConsonant(ch);
                return true;
            }
            if (kcm->GetVowelCode(ch) >= 0)//모음이 들어왔을 때
            {
                Init();
                return false;
            }
            if (kcm->GetInitSoundCode(ch) >= 0)//받침으로 쓸 수 없는 자음이 들어왔을 때
            {
                Init();
                final_consoPossible = false;
                final_conso = 0;
                return false;
            }
            return false;
        }
        void SetFirstFinalConsonant(char ch)
        {
            final_consoFirst = ch;
            final_consoPossible = EnableDoubleFinalConsonant();
        }

        bool InputSecondFinalConsonant(QString& source, char ch)
        {
            if (final_consoPossible) //이중 받침이 가능할 때
            {
                return SetSecondFinalConsonant(source, ch);

            }
            else //받침이 완성이 되었을 경우
            {
                if (kcm->GetInitSoundCode(ch) >= 0)   //자음일 때
                {
                    Init();//초기 상태로 전이
                }
                else //모음일 때
                {
                    LastFinalConsonantToInitSound(source);

                }
            }
            return false;
        }

        bool SetSecondFinalConsonant(QString& source, char ch)
        {
            final_consoPossible = false;
            QString tempfinal_conso = "";
            tempfinal_conso += final_consoFirst;
            tempfinal_conso += ch;

            int temp = kcm->GetFinalConsonantCode(tempfinal_conso);

            if (temp > 0)   //이중 받침
            {
                final_consoLast = ch;
                final_conso = temp;
                source = source.mid(0, source.length() - 1);
                source += GetCompleteChar();
                return true;
            }
            //그 외가 들어왔을 때
            return false;

        }

        void LastFinalConsonantToInitSound(QString& source)
        {
            if (IsFull())
            //if (IsDobleFinalConsonant()) //이중 받침일 때
            {
                source = source.mid(0, source.length() - 1);
                final_conso = kcm->GetFinalConsonantCode(final_consoFirst); //첫번째 받침이 종성
                source += GetCompleteChar();
                init_sound = kcm->GetInitSoundCode(final_consoLast); //두번째 받침을 초성으로 전이
            }
            else
            {
                char tempinit_sound = final_consoFirst;
                source = source.mid(0, source.length() - 1);
                ClearFinalConsonant();
                source += GetCompleteChar();
                init_sound = kcm->GetInitSoundCode(tempinit_sound);
            }

            source += kcm->GetSingleJa(init_sound);
            SetStateVowel(); //상태를 중성 입력 대기로 전이

        }

        void ClearFinalConsonant()
        {
            SetStateFinalConsonant();
            SetVowel(vowel_first);
        }

        void ClearLastVowel()
        {
            state = HGState::TURN_VOWEL;
            vowel = kcm->GetVowelCode(vowel_first);
        }

        void ClearLastFinalConsonant()
        {
            state = HGState::TURN_FINAL_CONSONANT;
            final_consoLast = FINAL_INIT_CHAR;
            final_conso = kcm->GetFinalConsonantCode(final_consoFirst);
            final_consoPossible = true;
        }

        QChar GetJaFormInitSound()
        {
            return kcm->GetSingleJa(init_sound);
        }

        bool IsFirstFinalConsonant()
        {
            return final_conso > 0;
        }

    };
}

#endif // HANGULSTATE_H
