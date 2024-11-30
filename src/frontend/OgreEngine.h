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
    OgreEngine(const OgreEngine &) = delete;
    OgreEngine &operator=(const OgreEngine &) = delete;
    ~OgreEngine();

    static OgreEngine *getInstance();

    void initialize(bool useCurrentGLContext);
    bool isInitialized();

    uint createNewTexture(uint width, uint height);
    void renderOneFrame();
    void handleEvent(const OgreBites::Event &event);

private:
    OgreEngine();
    void setup();
    void setupBasicScene();
    Ogre::Texture *m_Texture;
    Ogre::Root *root;
    Ogre::SceneManager *sceneManager;
    CameraController *m_mainCameraController;
    Ogre::ViewportGrid *grid;
    InputListenerChainExt *m_inputLisChain;

    bool m_useCurrentGLContext;
    bool m_initialized;
    static OgreEngine *m_instance;
};