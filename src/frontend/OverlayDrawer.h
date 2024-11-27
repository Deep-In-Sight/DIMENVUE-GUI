#pragma once
#include <OgreRenderTargetListener.h>

class OverlayDrawer : public Ogre::RenderTargetListener
{
public:
    OverlayDrawer();
    ~OverlayDrawer();
    virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent &evt) override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};