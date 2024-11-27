#include <iostream>

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreOverlaySystem.h>
#include <OgreImGuiOverlay.h>
#include <OgreGLRenderTexture.h>
#include <OgreGL3PlusFBORenderTexture.h>
#include <OgreGL3PlusTexture.h>
#include <OgreGLSupportPrerequisites.h>

using namespace Ogre;
using namespace OgreBites;

class App : public ApplicationContextBase,
            public RenderTargetListener
{
public:
    App() : ApplicationContextBase()
    {
    }
    ~App() = default;

    void test()
    {
        initApp();

        auto root = getRoot();
        auto sceneManager = root->createSceneManager();

        // Initialize RTShader system
        RTShader::ShaderGenerator *shadergen = RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(sceneManager);

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

        // something to render
        auto entity = sceneManager->createEntity("Sinbad.mesh");
        auto entityNode = sceneManager->getRootSceneNode()->createChildSceneNode();
        entityNode->attachObject(entity);

        // init overlay stuff
        auto overlaySystem = getOverlaySystem();
        sceneManager->addRenderQueueListener(overlaySystem);
        auto overlay = initialiseImGui();
        overlay->setZOrder(300);
        overlay->show();

        // m_Texture = Ogre::TextureManager::getSingleton().createManual(
        //                                                     "OffscreenTexture",
        //                                                     Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        //                                                     Ogre::TEX_TYPE_2D,
        //                                                     800,
        //                                                     600,
        //                                                     0,
        //                                                     Ogre::PF_BYTE_RGBA,
        //                                                     Ogre::TU_RENDERTARGET)
        //                 .get();

        // auto gl3plusTexture = dynamic_cast<GL3PlusTexture *>(m_Texture);
        // if (gl3plusTexture)
        // {
        //     std::cout << "GL3PlusTexture" << std::endl;
        // }

        // auto renderTexture = dynamic_cast<RenderTexture *>(m_Texture);
        // if (renderTexture)
        // {
        //     std::cout << "RenderTexture" << std::endl;
        // }

        // auto gl3plusFboTexture = dynamic_cast<GL3PlusFBORenderTexture *>(m_Texture);
        // if (gl3plusFboTexture)
        // {
        //     std::cout << "GL3PlusFBORenderTexture" << std::endl;
        // }

        auto rs = root->getRenderSystem();
        auto mrt = rs->createMultiRenderTarget("myRTT");
        GL3PlusFrameBufferObject *fbo = 0;
        mrt->getCustomAttribute("FBO", &fbo);
        auto fbom = dynamic_cast<GL3PlusFBOManager *>(fbo->getManager());
        auto sd = fbom->createNewRenderBuffer(GL_RGBA8, 800, 600, 4);
        auto tex = fbom->createRenderTexture("myRTT", sd, false, 4);
        auto vp = tex->addViewport(camera);
        vp->setClearEveryFrame(true);
        vp->setBackgroundColour(ColourValue::Black);
        vp->setOverlaysEnabled(true);
        tex->addListener(this);

        // auto rt1 = m_Texture->getBuffer()->getRenderTarget();
        // auto vp1 = rt1->addViewport(camera);
        // vp1->setClearEveryFrame(true);
        // vp1->setBackgroundColour(ColourValue::Black);
        // vp1->setOverlaysEnabled(true);

        // rt1->addListener(this);

        // auto rttm = static_cast<GL3PlusFBOManager *>(GL3PlusRTTManager::getSingletonPtr());
        // auto sd = rttm->requestRenderBuffer(GL_RGBA8, 800, 600, 4);
        // auto fbo = rttm->createRenderTexture("myRTT", sd, false, 4);
        // auto vp = fbo->addViewport(camera);
        // vp->setClearEveryFrame(true);
        // vp->setBackgroundColour(ColourValue::Black);
        // vp->setOverlaysEnabled(true);
        // fbo->addListener(this);

        for (int i = 0; i < 50; i++)
        {
            tex->getFBO()->bind(true);
            tex->update(true);
        }
    }

    void preRenderTargetUpdate(const RenderTargetEvent &evt)
    {
        ImGuiOverlay::NewFrame();
        ImGui::SetWindowPos(ImVec2(0, 0));
        ImGui::ShowDemoWindow();
    }

    void postRenderTargetUpdate(const RenderTargetEvent &evt)
    {
        auto rt = evt.source;
        rt->writeContentsToFile("rtt_screenshot.png");
    }

private:
    Ogre::Texture *m_Texture;
    Ogre::Root *root;
    Ogre::SceneManager *sceneManager;
};

int main()
{
    App app;
    app.test();

    return 0;
}