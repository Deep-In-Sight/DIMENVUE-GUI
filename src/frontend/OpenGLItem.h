#pragma once

#include <QMutex>
#include <QQueue>
#include <QQuickFramebufferObject>

struct RasterizerRenderer;

class OpenGLItem : public QQuickFramebufferObject
{
    Q_OBJECT
  public:
    OpenGLItem(QQuickItem *parent = nullptr);
    bool event(QEvent *event) override;

    QQuickFramebufferObject::Renderer *createRenderer() const override;

  private:
    mutable RasterizerRenderer *m_renderer = nullptr;
};