#pragma once

#include <QQuickFramebufferObject>

class OpenGLItem : public QQuickFramebufferObject
{
    Q_OBJECT
  public:
    OpenGLItem(QQuickItem *parent = nullptr);
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    QQuickFramebufferObject::Renderer *createRenderer() const override;
};