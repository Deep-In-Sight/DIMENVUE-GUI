#include <OverlayDrawer.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <MapVisualizer.h>
#include <OgreEngine.h>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>

struct OverlayDrawer::Impl
{
    Impl(OverlayDrawer *parent) : parent(parent)
    {
    }
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
                    ImGui::Text("%s", mat.c_str());
                }
            }
        }
        ImGui::End();

        if (ImGui::Begin("Test point cloud"))
        {
            static int numPoints = 1;
            static int numPointLog = 0;
            static float scale = 1.0;
            static std::vector<std::pair<Ogre::SceneNode *, bool>> pcds;
            ImGui::DragInt("x", &numPoints, 1, 0, 1000);
            ImGui::DragInt("log", &numPointLog, 1, 0, 6);
            ImGui::DragFloat("scale", &scale, 0.1, 0.1, 100);
            if (ImGui::Button("Add random cloud"))
            {
                auto *viz = MapVisualizer::getInstance();
                auto node = viz->addRandomCloud(numPoints * pow(10, numPointLog), scale);
                pcds.push_back({node, true});
            }

            static char path[1024] = "<>";
            ImGui::Text("%s", path);
            ImGui::SameLine();
            if (ImGui::Button("Browse"))
            {
            }
            ImGui::SameLine();
            if (ImGui::Button("OK"))
            {
                QFileInfo info(path);
                if (info.exists())
                {
                    auto *viz = MapVisualizer::getInstance();
                    auto node = viz->loadPCDFile(path);
                    pcds.push_back({node, true});
                }
            }

            ImGui::Text("Point clouds:");
            for (auto &p : pcds)
            {
                auto node = p.first;
                auto &visible = p.second;
                auto name = node->getName();
                if (name.empty())
                {
                    name = std::to_string(reinterpret_cast<uint64_t>(node));
                }
                if (ImGui::Checkbox(name.c_str(), &visible))
                {
                    node->setVisible(visible);
                }
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
    OverlayDrawer *parent;
};

OverlayDrawer::OverlayDrawer(ImGuiItem *parent) : ImGuiOverlay(parent)
{
    m_impl = std::make_unique<Impl>(this);
}

OverlayDrawer::~OverlayDrawer() = default;

void OverlayDrawer::onUpdateImGui()
{
    m_impl->update();
}
