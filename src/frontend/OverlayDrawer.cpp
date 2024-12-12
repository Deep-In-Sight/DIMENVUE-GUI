#include <OverlayDrawer.h>
#define IMGUI_DEFINE_MATH_OPERATORS
// #include <MapVisualizer.h>
// #include <OgreEngine.h>
#include <CameraController.h>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <global.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <implot.h>
#include <iostream>

struct OverlayDrawer::Impl
{
    struct ScrollingBuffer
    {
        int MaxSize;
        int Offset;
        ImVector<ImVec2> Data;
        ScrollingBuffer()
        {
            MaxSize = 2000;
            Offset = 0;
            Data.reserve(MaxSize);
        }
        void AddPoint(float x, float y)
        {
            if (Data.size() < MaxSize)
                Data.push_back(ImVec2(x, y));
            else
            {
                Data[Offset] = ImVec2(x, y);
                Offset = (Offset + 1) % MaxSize;
            }
        }
        void Erase()
        {
            if (Data.size() > 0)
            {
                Data.shrink(0);
                Offset = 0;
            }
        }
    };
    double Infinity = std::numeric_limits<double>::infinity();

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

    void showPerformanceWindow()
    {
        auto &io = ImGui::GetIO();
        if (ImGui::Begin("Performance"))
        {
            ImGui::Text("FPS: %.1f", io.Framerate);

            static float history = 2.0f; // plot last 2 seconds history
            static ScrollingBuffer sFrames;
            static ScrollingBuffer s60fps;
            static ScrollingBuffer s120fps;
            // get current time
            auto t = ImGui::GetTime();
            // auto t = std::chrono::duration_cast<std::chrono::milliseconds>(
            //              std::chrono::system_clock::now().time_since_epoch())
            //              .count() /
            //          1000.0;

            sFrames.AddPoint(t, 1000.0f * io.DeltaTime);
            s60fps.AddPoint(t, 1000.0f / 60.0f);
            s120fps.AddPoint(t, 1000.0f / 120.0f);

            static ImPlotAxisFlags rt_axis = ImPlotAxisFlags_NoTickLabels;
            // ImPlot::SetNextPlotLimitsX(t - history, t, ImGuiCond_Always);
            // ImPlot::SetNextPlotLimitsY(0, 30, ImGuiCond_Always);
            ImPlot::SetNextAxisLimits(ImAxis_X1, t - history, t, ImGuiCond_Always);
            ImPlot::SetNextAxisLimits(ImAxis_Y1, 0, 30, ImGuiCond_Always);

            if (ImPlot::BeginPlot("Timings"))
            {
                ImPlot::PlotShaded("frame time(ms)", &sFrames.Data[0].x, &sFrames.Data[0].y, sFrames.Data.size(),
                                   -Infinity, 0, sFrames.Offset, 2 * sizeof(float));

                ImPlot::PlotLine("16.6ms (60 FPS)", &s60fps.Data[0].x, &s60fps.Data[0].y, s60fps.Data.size(), 0,
                                 s60fps.Offset, 2 * sizeof(float));
                ImPlot::PlotLine(" 8.3ms (120 FPS)", &s120fps.Data[0].x, &s120fps.Data[0].y, s120fps.Data.size(), 0,
                                 s120fps.Offset, 2 * sizeof(float));

                ImPlot::EndPlot();
            }
        }
        ImGui::End();
    }

    void showCameraWindow()
    {
        auto cc = GlobalVar::cameraController;
        if (cc == nullptr)
        {
            return;
        }
        if (ImGui::Begin("camera controller"))
        {
            Eigen::Vector3f position = cc->getPosition().cast<float>();
            if (ImGui::DragFloat3("position", position.data(), 0.1))
                cc->setPosition(position.cast<double>());
            Eigen::Vector3f euler = cc->getEuler().cast<float>();
            if (ImGui::DragFloat3("euler", euler.data(), 0.1))
                cc->setEuler(euler.cast<double>());
            Eigen::Vector3f speed = cc->getSpeed().cast<float>();
            if (ImGui::DragFloat3("speed", speed.data(), 0.1))
                cc->setSpeed(speed.cast<double>());
        }
        ImGui::End();
    }
#if 0
    void showTestPointCloudWindow()
    {
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
#endif
    void update()
    {
        // if (!is_enabled())
        //     return;
        // ImGui::ShowDemoWindow();
        showPerformanceWindow();
        showCameraWindow();
#if 0
        showTestPointCloudWindow();
#endif
    }

#if 0
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
#endif
    bool overlay_enable = false;
    std::vector<std::string> m_materials;
    OverlayDrawer *parent;
};

OverlayDrawer::OverlayDrawer(ImGuiItem *parent) : ImGuiOverlay(parent)
{
    m_impl = std::make_unique<Impl>(this);
    ImPlot::CreateContext();
    ImPlot::StyleColorsDark();
}

OverlayDrawer::~OverlayDrawer()
{
    ImPlot::DestroyContext();
}

void OverlayDrawer::onUpdateImGui()
{
    m_impl->update();
}
