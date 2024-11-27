#pragma once

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreCameraMan.h>
#include <OgreRTShaderSystem.h>
#include <functional>
#include <CameraController.h>
#include <ViewportGrid.h>
#include <OverlayDrawer.h>
#include <InputListenerChainExt.h>
namespace Ogre
{
    class GL3PlusFBORenderTexture;
}
class OgreEngine : public OgreBites::ApplicationContextBase
{
public:
    OgreEngine(bool useCurrentGLContext);
    ~OgreEngine();

    void setupScene();

    bool isInitialized();

    void getFrame(uint *texId, uint *width, uint *height);

    void renderOneFrame();
    void handleEvent(const OgreBites::Event &event);

private:
    void setup();
    void setupFBO();
    Ogre::Texture *m_Texture;
    Ogre::Root *root;
    Ogre::SceneManager *sceneManager;
    CameraController *m_mainCameraController;
    Ogre::ViewportGrid *grid;
    OverlayDrawer *overlayDrawer;
    InputListenerChainExt *m_inputLisChain;
    Ogre::GL3PlusFBORenderTexture *m_fbo;

    bool m_useCurrentGLContext;
    bool m_initialized;
};