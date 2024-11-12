#pragma once

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreCameraMan.h>
#include <OgreRTShaderSystem.h>
#include <functional>
#include <CameraController.h>

class OgreEngine : public OgreBites::ApplicationContextBase
{
public:
    OgreEngine(bool useCurrentGLContext);
    ~OgreEngine();

    void setupScene();

    bool isInitialized();

    void getFrame(uint *texId, uint *width, uint *height);
    void moveCamera();

    void renderOneFrame();
    void handleEvent(const OgreBites::Event &event);

private:
    void setup();
    Ogre::Texture *m_Texture;
    Ogre::Root *root;
    Ogre::SceneManager *sceneManager;
    // OgreBites::CameraMan *m_mainCameraController;
    OgreBites::CameraMan *m_mainCameraController;
    bool m_useCurrentGLContext;
    bool m_initialized;
};