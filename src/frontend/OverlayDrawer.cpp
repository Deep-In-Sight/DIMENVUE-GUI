#include <OverlayDrawer.h>
#include <OgreImGuiOverlay.h>

struct OverlayDrawer::Impl
{
    void update()
    {
        Ogre::ImGuiOverlay::NewFrame();
        ImGui::ShowDemoWindow();
    }
};

OverlayDrawer::OverlayDrawer() : m_impl(std::make_unique<Impl>())
{
}

OverlayDrawer::~OverlayDrawer() = default;

void OverlayDrawer::preRenderTargetUpdate(const Ogre::RenderTargetEvent &evt)
{
    m_impl->update();
}