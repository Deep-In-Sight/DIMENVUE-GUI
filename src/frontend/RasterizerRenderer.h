#pragma once

#include <QQuickFramebufferObject>

class RasterizerRenderer : public QQuickFramebufferObject::Renderer
{
  public:
    RasterizerRenderer();
    void render() override;

  private:
    void initialize();
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_program;
};