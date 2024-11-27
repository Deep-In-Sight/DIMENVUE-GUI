#include <iostream>

#include <OgreEngine.h>
#include <RenderSystems/GL3Plus/OgreGL3PlusTexture.h>
#include <math.h>
#include <QOpenGLContext>
// later change this to OgrePresenter.h we want nothing to do with Qt here
#include <QOgreItem.h>
#include <CameraController.h>
#include <ViewportGrid.h>
#include <OgreOverlaySystem.h>
#include <OgreImGuiOverlay.h>
#include <OverlayDrawer.h>
#include <InputListenerChainExt.h>
#include <RenderSystems/GL3Plus/OgreGL3PlusFBORenderTexture.h>

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
    if (overlayDrawer)
    {
        delete overlayDrawer;
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
                                                        true)
                    .get();

    root = getRoot();
    sceneManager = root->createSceneManager();

    // Initialize RTShader system
    RTShader::ShaderGenerator *shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(sceneManager);

    // imgui overlay setup
    auto overlaySystem = getOverlaySystem();
    sceneManager->addRenderQueueListener(overlaySystem);
    auto overlay = initialiseImGui();
    overlay->setZOrder(300);
    overlay->show();

    auto imguiListener = getImGuiInputListener();
    m_inputLisChain = new InputListenerChainExt();
    addInputListener(0, m_inputLisChain);
    m_inputLisChain->addListener(imguiListener);

    m_initialized = true;
}

void OgreEngine::setupFBO()
{
    // auto manager = GL3PlusFBOManager::getSingletonPtr();
    // auto gl3manager = dynamic_cast<GL3PlusFBOManager *>(manager);
    // auto buffer = gl3manager->requestRenderBuffer(
    //     GL_RGBA8, 800, 600, 4);
    // m_fbo = gl3manager->createRenderTexture("myRTT", buffer, false, 4);
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
    vp->setOverlaysEnabled(true);

    grid = new ViewportGrid(sceneManager, vp);
    grid->setColour(ColourValue(0.5, 0.5, 0.5, 0.5));
    grid->enable();

    overlayDrawer = new OverlayDrawer();
    rt->addListener(overlayDrawer);

    // getRenderWindow()->addViewport(camera);
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

void OgreEngine::renderOneFrame()
{
    getRoot()->renderOneFrame();
    // m_Texture->getBuffer()->getRenderTarget()->update();
    // m_Texture->getBuffer()->getRenderTarget()->writeContentsToFile("frame.png");
}

void OgreEngine::handleEvent(const OgreBites::Event &event)
{
    ApplicationContextBase::_fireInputEvent(event, 0);
}
