#include <OpenGLItem.h>
#include <QMimeData>
#include <QQuickWindow>
#include <RasterizerRenderer.h>

OpenGLItem::OpenGLItem(QQuickItem *parent) : QQuickFramebufferObject(parent)
{
    setFlag(ItemAcceptsDrops, true);
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
    return new RasterizerRenderer();
}

void OpenGLItem::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void OpenGLItem::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void OpenGLItem::dropEvent(QDropEvent *event)
{
    auto urls = event->mimeData()->urls();
    if (urls.isEmpty())
    {
        return;
    }
    auto path = urls.first().toLocalFile();
    if (path.isEmpty())
    {
        return;
    }
    qDebug() << "Dropped file:" << path;
}