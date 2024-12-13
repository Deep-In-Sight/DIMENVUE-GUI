#ifndef HANGUL_H
#define HANGUL_H

#include <QString>
#include <QScopedPointer>
#include "HangulState.h"
#include "KoreanCharMaker.h"

namespace Automata
{
    class Hangul
    {
        QScopedPointer<HangulState> hs;
        QScopedPointer<KoreanCharMaker> kcm;
        QString source;

    public:
        QString getText() const
        {
            return source;
        }
        void setText(const QString& value)
        {
            source = value;
        }

        Hangul() : hs(new HangulState)
                 , kcm(new KoreanCharMaker)
        {
        }

        void Reset()
        {
            hs->Init();
        }

        void Input(char c)
        {
            QChar ch = c;

            if (ch == '\b')
            {
                BackKeyProc();
                return;
            }

            if (!ch.isLetter())
            {
                source += ch;
                hs->Init();
                return;
            }

            ch = kcm->NonShiftKeyToLower(ch);

            switch (hs->getState())
            {
            case HGState::TURN_INIT_SOUND: InputInitSoundProc(c); break;
            case HGState::TURN_VOWEL: InputVowelProc(c); break;
            case HGState::TURN_FINAL_CONSONANT: InputFinalConsonantProc(c); break;
            }
        }

        void InputNoKorea(char ch)
        {
            Reset();
            source += ch;
        }

        void InputInitSoundProc(char ch)
        {
            if (!hs->InputAtInitSound(source, ch))
            {
                Input(ch);
            }
        }

        void InputVowelProc(char ch)
        {

            if (hs->ExistVowel() == false)
            {
                if (hs->InputFirstVowel(source, ch) == false)
                {
                    Input(ch);
                }
            }
            else
            {
                if (hs->InputSecondVowel(source, ch) == false)
                {
                    Input(ch);
                }
            }
        }

        void InputFinalConsonantProc(char ch)
        {
            if (hs->IsFirstFinalConsonant() == false)
            {
                if (hs->InputFirstFinalConsonant(source, ch) == false)
                {

                    Input(ch);
                }

            }
            else
            {
                if (hs->InputSecondFinalConsonant(source, ch) == false)
                {
                    Input(ch);
                }
            }
        }

        void BackKeyProc()
        {
            if (source.length() <= 0)
            {
                return;
            }

            if ((hs->getState() == HGState::TURN_INIT_SOUND) || hs->IsInitSound())
            {
                hs->SetStateInitSound();
                source = source.mid(0, source.length() - 1);
                return;
            }

            if (hs->IsSingleVowel())
            {
                hs->SetStateVowel();
                source = source.mid(0, source.length() - 1);
                source += hs->GetJaFormInitSound();
                return;
            }
            if (hs->IsDoubleVowel())
            {

                source = source.mid(0, source.length() - 1);
                hs->ClearLastVowel();
                source += hs->GetCompleteChar();
                return;
            }
            if (hs->IsSingleFinalConsonant())
            {
                hs->ClearFinalConsonant();
                source = source.mid(0, source.length() - 1);
                source += hs->GetCompleteChar();
                return;
            }
            else if (hs->IsFull())
            {

                hs->ClearLastFinalConsonant();
                source = source.mid(0, source.length() - 1);
                source += hs->GetCompleteChar();
            }
        }
    };
}

#endif // HANGUL_H
