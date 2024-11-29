#include <iostream>

#include <OgreEngine.h>
#include <math.h>
#include <CameraController.h>
#include <ViewportGrid.h>
#include <InputListenerChainExt.h>

using namespace Ogre;
using namespace OgreBites;

OgreEngine::OgreEngine(bool useCurrentGLContext) : m_useCurrentGLContext(useCurrentGLContext),
                                                   m_initialized(false),
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
    // createWindow(mAppName);

    locateResources();
    initialiseRTShaderSystem();
    loadResources();

    m_Texture = Ogre::TextureManager::getSingleton().createManual(
                                                        "OffscreenTexture",
                                                        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                        Ogre::TEX_TYPE_2D,
                                                        800, 600,
                                                        0,
                                                        PF_BYTE_RGBA,
                                                        Ogre::TU_RENDERTARGET,
                                                        0,
                                                        false,
                                                        16)
                    .get();

    root = getRoot();
    sceneManager = root->createSceneManager();

    // Initialize RTShader system
    RTShader::ShaderGenerator *shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(sceneManager);

    m_inputLisChain = new InputListenerChainExt();
    addInputListener(0, m_inputLisChain);

    m_initialized = true;
}

void OgreEngine::setupScene()
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

    auto rt = m_Texture->getBuffer()->getRenderTarget();
    auto vp = rt->addViewport(camera);
    vp->setClearEveryFrame(true);
    vp->setBackgroundColour(ColourValue::Black);

    grid = new ViewportGrid(sceneManager, vp);
    grid->setColour(ColourValue(0.1, 0.1, 0.1, 1.0));
    grid->enable();
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
    uint tid = 0;
    m_Texture->getCustomAttribute("GLID", &tid);
    *texId = tid;
    *width = m_Texture->getWidth();
    *height = m_Texture->getHeight();
}

void OgreEngine::renderOneFrame()
{
    getRoot()->renderOneFrame();
}

void OgreEngine::handleEvent(const OgreBites::Event &event)
{
    ApplicationContextBase::_fireInputEvent(event, 0);
}
