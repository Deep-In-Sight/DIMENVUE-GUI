#pragma once

#include <QQuickFramebufferObject>

class OgreRenderer : public QQuickFramebufferObject::Renderer
{
public:
    OgreRenderer();
    void render() override;
    bool event(QEvent *event) override;

private:
    void _makeOgreCurrent();
    void _makeQtCurrent();
    QOpenGLContext *m_qtcontext;
    QOpenGLContext *m_ogrecontext;
}