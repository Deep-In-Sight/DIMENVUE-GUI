#pragma once
#include <ImGuiItem.h>

class OverlayDrawer : public ImGuiOverlay
{
public:
    OverlayDrawer(ImGuiItem *parent);
    ~OverlayDrawer();

public slots:
    void onUpdateImGui() override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};