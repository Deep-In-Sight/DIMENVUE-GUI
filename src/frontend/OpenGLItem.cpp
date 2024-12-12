#include <OpenGLItem.h>
#include <OrbitControls.h>
#include <QMimeData>
#include <QOpenGLContext>
#include <QQuickWindow>
#include <RasterizerRenderer.h>
#include <Renderer.h>

OpenGLItem::OpenGLItem(QQuickItem *parent) : QQuickFramebufferObject(parent)
{
    setFlag(ItemAcceptsDrops, true);
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton | Qt::MiddleButton);
    setAcceptTouchEvents(true);
    setMirrorVertically(true); // conform to opengl texture coordinates
    // continuous rendering
    connect(this, &QQuickItem::windowChanged, this, [this]() {
        if (window())
        {
            connect(window(), &QQuickWindow::beforeRendering, this, [this]() { this->update(); });
        }
    });
}

OpenGLItem::Renderer *OpenGLItem::createRenderer() const
{
    m_renderer = new RasterizerRenderer();
    return m_renderer;
}

bool OpenGLItem::event(QEvent *event)
{
    auto mouseEvent = dynamic_cast<QMouseEvent *>(event);
    auto wheelEvent = dynamic_cast<QWheelEvent *>(event);
    auto touchEvent = dynamic_cast<QTouchEvent *>(event);
    auto dragdropEvent = dynamic_cast<QDropEvent *>(event);
    if (mouseEvent)
    {
        qDebug() << "Mouse event detected" << event->type();
    }
    if (touchEvent)
    {
        qDebug() << "Touch event detected" << event->type();
    }
    if (wheelEvent)
    {
        qDebug() << "Wheel event detected" << event->type();
    }
    if (dragdropEvent)
    {
        qDebug() << "Drag and drop event detected" << event->type();
    }

    if (mouseEvent || wheelEvent || touchEvent || dragdropEvent)
    {
        event->setAccepted(true);
        m_renderer->queueEvent(event);
        return true;
    }
    return QQuickFramebufferObject::event(event);
}