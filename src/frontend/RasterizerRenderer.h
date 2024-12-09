#pragma once

#include <QQuickFramebufferObject>

class RasterizerRenderer : public QQuickFramebufferObject::Renderer
{
  public:
    RasterizerRenderer();
    void render() override;
};