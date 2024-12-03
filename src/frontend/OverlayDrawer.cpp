#include <OverlayDrawer.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>
#include <OgreEngine.h>
#include <MapVisualizer.h>

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
        // if (!is_enabled())
        //     return;
        ImGui::ShowDemoWindow();
        if (ImGui::Begin("Debug"))
        {
            ImGui::Text("FPS:%.2f", ImGui::GetIO().Framerate);
            if (m_materials.empty())
            {
                initializeMaterials();
            }
            else
            {
                ImGui::Text("Materials:");
                for (auto &mat : m_materials)
                {
                    ImGui::Text(mat.c_str());
                }
            }
        }
        ImGui::End();

        if (ImGui::Begin("Test point cloud"))
        {
            static int numPoints = 1;
            ImGui::DragInt("millions", &numPoints, 1, 0, 1000);
            if (ImGui::Button("Add random cloud"))
            {
                MapVisualizer *viz = MapVisualizer::getInstance();
                viz->addRandomCloud(numPoints * 1000000);
            }
        }
        ImGui::End();
    }

    void initializeMaterials()
    {
        auto ogre = OgreEngine::getInstance();
        if (!ogre->isInitialized())
        {
            return;
        }
        auto matMgr = Ogre::MaterialManager::getSingletonPtr();
        auto iter = matMgr->getResourceIterator();
        while (iter.hasMoreElements())
        {
            auto mat = iter.getNext();
            m_materials.push_back(mat->getName());
        }
    }

    bool overlay_enable = false;
    std::vector<std::string> m_materials;
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