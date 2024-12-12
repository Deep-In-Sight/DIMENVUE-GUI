#pragma once

#include <QQuickFramebufferObject>

namespace ComputeRenderer
{
struct Renderer;
struct LasLoaderSparse;
} // namespace ComputeRenderer

struct MyCameraController;

class RasterizerRenderer : public QQuickFramebufferObject::Renderer
{
  public:
    RasterizerRenderer();
    void queueEvent(QEvent *event);

  private:
    void render() override;
    void synchronize(QQuickFramebufferObject *item) override;
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void touchEvent(QTouchEvent *event);

    void event(QEvent *event);

  public:
    void initialize();
    QQuickWindow *window;
    QRectF viewportSize;
    std::shared_ptr<ComputeRenderer::Renderer> renderer;
    std::shared_ptr<ComputeRenderer::LasLoaderSparse> lasLoader;
    std::shared_ptr<MyCameraController> cameraController;
    QQueue<QEvent *> eventQueue;
    QMutex eventQueueMutex;
};