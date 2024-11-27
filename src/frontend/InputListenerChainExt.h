#pragma once
#include <OgreInput.h>

class InputListenerChainExt : public OgreBites::InputListenerChain
{
public:
    InputListenerChainExt() : OgreBites::InputListenerChain() {}
    inline void addListener(OgreBites::InputListener *lis)
    {
        mListenerChain.push_back(lis);
    }
    inline void remove(OgreBites::InputListener *lis)
    {
        mListenerChain.erase(std::remove(mListenerChain.begin(), mListenerChain.end(), lis), mListenerChain.end());
    }
};