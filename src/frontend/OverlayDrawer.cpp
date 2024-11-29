#include <OverlayDrawer.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>
struct OverlayDrawer::Impl
{
    /***
     * @brief Check if the overlay is enabled
     * enable/disable the entire imgui overlay by long pressing for 3seconds in the 10% top left corner of the window
     */
    bool is_enabled()
    {
        auto &io = ImGui::GetIO();
        auto clickPos = io.MouseClickedPos[0];
        auto vp = ImGui::GetMainViewport();
        ImRect clickRect(vp->WorkPos, vp->WorkPos + vp->WorkSize / 10);
        if (io.MouseReleased[0] && io.MouseDownDurationPrev[0] > 3.0 && clickRect.Contains(clickPos))
        {
            overlay_enable = !overlay_enable;
        }
        return overlay_enable;
    }

    void update()
    {
        if (!is_enabled())
            return;
        ImGui::ShowDemoWindow();
    }

    bool overlay_enable = false;
};

OverlayDrawer::OverlayDrawer(ImGuiItem *parent) : ImGuiOverlay(parent)
{
    m_impl = std::make_unique<Impl>();
}

OverlayDrawer::~OverlayDrawer() = default;

void OverlayDrawer::onUpdateImGui()
{
    m_impl->update();
}