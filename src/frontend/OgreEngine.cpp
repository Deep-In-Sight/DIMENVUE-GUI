#include <iostream>

#include <OgreEngine.h>
#include <RenderSystems/GL3Plus/OgreGL3PlusTexture.h>
#include <math.h>
#include <QOpenGLContext>
// later change this to OgrePresenter.h we want nothing to do with Qt here
#include <QOgreItem.h>
#include <CameraController.h>

using namespace Ogre;
using namespace OgreBites;

Ogre::PixelFormat pf;

OgreEngine::OgreEngine(bool useCurrentGLContext) : m_useCurrentGLContext(useCurrentGLContext),
                                                   m_initialized(false),
                                                   m_mainCameraController(nullptr),
                                                   ApplicationContextBase("OgreBackend")
{
}

OgreEngine::~OgreEngine() = default;

void OgreEngine::setup()
{
    LogManager::getSingletonPtr()->setMinLogLevel(Ogre::LogMessageLevel::LML_CRITICAL);
    mRoot->initialise(false);

    Ogre::NameValuePairList params;
    if (m_useCurrentGLContext)
    {
        params["currentGLContext"] = "true";
    }

    // modify this to add the current GL context
    auto w = createWindow(mAppName, 1, 1, params);
    w.render->setHidden(true);

    locateResources();
    initialiseRTShaderSystem();
    loadResources();

    // adds context as listener to process context-level (above the sample level) events
    mRoot->addFrameListener(this);

    m_Texture = Ogre::TextureManager::getSingleton().createManual(
                                                        "OffscreenTexture",
                                                        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                        Ogre::TEX_TYPE_2D,
                                                        800, 600,
                                                        0,
                                                        PF_A8R8G8B8,
                                                        Ogre::TU_RENDERTARGET)
                    .get();
    m_initialized = true;
}

void OgreEngine::setupScene()
{
    root = getRoot();
    sceneManager = root->createSceneManager();

    // Initialize RTShader system
    RTShader::ShaderGenerator *shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(sceneManager);

    // Set up the camera
    auto camNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    auto camera = sceneManager->createCamera("mainCam");

    camera->setNearClipDistance(5);
    camera->setAutoAspectRatio(true);

    // Position the camera
    camNode->setPosition(0, 10, 20);
    camNode->lookAt(Vector3(0, 0, 0), Node::TS_WORLD);
    camNode->attachObject(camera);

    // Create a light
    auto light = sceneManager->createLight("MainLight");
    light->setType(Light::LT_POINT);
    camNode->attachObject(light);

    // Create main camera controller
    m_mainCameraController = new CameraMan(camNode);
    m_mainCameraController->setStyle(CS_FREELOOK);
    m_mainCameraController->setTopSpeed(5);
    // m_mainCameraController = new CameraController(camNode);
    addInputListener(0, m_mainCameraController);

    // Create a basic entity
    auto entity = sceneManager->createEntity("Sinbad.mesh");
    auto entityNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    entityNode->attachObject(entity);

    auto rt = m_Texture->getBuffer()->getRenderTarget();
    auto vp = rt->addViewport(camera);
    vp->setClearEveryFrame(true);
    vp->setBackgroundColour(ColourValue::Green);
}

bool OgreEngine::isInitialized()
{
    return m_initialized;
}

void OgreEngine::getFrame(uint *texId, uint *width, uint *height)
{
    if (!texId | !width | !height)
    {
        throw std::runtime_error("Invalid arguments");
    }

    auto glTexture = dynamic_cast<Ogre::GL3PlusTexture *>(m_Texture);
    if (!glTexture)
    {
        throw std::runtime_error("Ogre not using GL3+ renderer");
    }
    *texId = glTexture->getGLID();
    *width = m_Texture->getWidth();
    *height = m_Texture->getHeight();
}

void OgreEngine::moveCamera()
{
    static int i = 0;
    float dt = 0.01;
    float omega = 2 * M_PI;
    float theta = omega * (i++) * dt;
    float R = 20;
    auto camera = sceneManager->getCamera("mainCam");
    auto camNode = camera->getParentSceneNode();
    auto position = camNode->getPosition();
    position.x = R * cos(theta);
    position.z = R * sin(theta);
    position.y = 10;
    camNode->setPosition(position);
    camNode->lookAt(Vector3(0, 0, 0), Node::TS_WORLD);
}

void OgreEngine::renderOneFrame()
{
    m_Texture->getBuffer()->getRenderTarget()->update();
}

void OgreEngine::handleEvent(const OgreBites::Event &event)
{
    ApplicationContextBase::_fireInputEvent(event, 0);
}