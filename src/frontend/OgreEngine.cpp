#include <iostream>

#include <OgreEngine.h>
#include <math.h>
#include <CameraController.h>
#include <ViewportGrid.h>
#include <InputListenerChainExt.h>

using namespace Ogre;
using namespace OgreBites;

OgreEngine *OgreEngine::m_instance = nullptr;

OgreEngine *OgreEngine::getInstance()
{
    if (!m_instance)
    {
        m_instance = new OgreEngine();
    }
    return m_instance;
}

void OgreEngine::initialize(bool useCurrentGLContext)
{
    if (m_initialized)
    {
        return;
    }
    m_useCurrentGLContext = useCurrentGLContext;
    initApp();
    setupBasicScene();
    m_initialized = true;
}

bool OgreEngine::isInitialized()
{
    return m_initialized;
}

uint OgreEngine::createNewTexture(uint width, uint height)
{
    if (!m_initialized)
    {
        throw std::runtime_error("OgreEngine::initialize() must be called first");
    }
    if (m_Texture)
    {
        grid->detachFromViewport();
        Ogre::TextureManager::getSingleton().remove("OffscreenTexture");
    }
    m_Texture = Ogre::TextureManager::getSingleton().createManual(
                                                        "OffscreenTexture",
                                                        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                        Ogre::TEX_TYPE_2D,
                                                        width, height,
                                                        0,
                                                        PF_BYTE_RGBA,
                                                        Ogre::TU_RENDERTARGET,
                                                        0,
                                                        false,
                                                        16)
                    .get();
    auto rt = m_Texture->getBuffer()->getRenderTarget();
    auto vp = rt->addViewport(sceneManager->getCamera("mainCam"));
    vp->setClearEveryFrame(true);
    vp->setBackgroundColour(ColourValue::Black);
    grid->attachToViewport(vp);

    uint tid = 0;
    m_Texture->getCustomAttribute("GLID", &tid);
    return tid;
}

void OgreEngine::renderOneFrame()
{
    if (m_Texture)
    {
        m_Texture->getBuffer()->getRenderTarget()->update();
    }
}

void OgreEngine::handleEvent(const OgreBites::Event &event)
{
    ApplicationContextBase::_fireInputEvent(event, 0);
}

OgreEngine::OgreEngine() : m_initialized(false),
                           m_Texture(nullptr),
                           m_mainCameraController(nullptr),
                           ApplicationContextBase("OgreBackend")
{
}

OgreEngine::~OgreEngine()
{
    if (m_mainCameraController)
    {
        delete m_mainCameraController;
    }
    if (m_inputLisChain)
    {
        delete m_inputLisChain;
    }
    if (grid)
    {
        delete grid;
    }
};

void OgreEngine::setup()
{
    LogManager::getSingletonPtr()->setMinLogLevel(Ogre::LogMessageLevel::LML_CRITICAL);
    mRoot->initialise(false);

    Ogre::NameValuePairList params;
    if (m_useCurrentGLContext)
    {
        params["currentGLContext"] = "true";
    }

    auto w = createWindow(mAppName, 1, 1, params);
    w.render->setHidden(true);

    locateResources();
    initialiseRTShaderSystem();
    loadResources();

    root = getRoot();
    sceneManager = root->createSceneManager();

    // Initialize RTShader system
    RTShader::ShaderGenerator *shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(sceneManager);

    m_inputLisChain = new InputListenerChainExt();
    addInputListener(0, m_inputLisChain);
}

void OgreEngine::setupBasicScene()
{
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
    m_mainCameraController = new CameraController(camNode);
    m_inputLisChain->addListener(m_mainCameraController);

    // Create a basic entity
    auto entity = sceneManager->createEntity("Sinbad.mesh");
    auto entityNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    entityNode->attachObject(entity);

    grid = new ViewportGrid(sceneManager);
    grid->setColour(ColourValue(0.1, 0.1, 0.1, 1.0));
    grid->enable();
}
