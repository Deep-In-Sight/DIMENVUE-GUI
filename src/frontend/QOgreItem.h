#pragma once

#include <QSGImageNode>
#include <QQuickItem>
#include <QSGTexture>
#include <QSGSimpleTextureNode>
#include <QQuickWindow>
#include <QOpenGLContext>
#include <thread>
#include <OgreEngine.h>
#include <QMutex>

class OgrePresenter
{
public:
    virtual void presentFrame() = 0;
};

class QOgreItem : public QQuickItem
{
    Q_OBJECT

public:
    QOgreItem(QQuickItem *parent = nullptr);
    ~QOgreItem() override = default;

signals:
    void ogreRendered();

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data) override;
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;

private slots:
    void onWindowChanged(QQuickWindow *window);
    void onBeforeRendering();

private:
    void resetTexture();
    QMutex m_mutex;
    uint texId;
    QOpenGLContext *_makeContextCurrent(QOpenGLContext *newCtx);
    bool event(QEvent *event) override;
    QOpenGLContext *m_qtcontext;
    QOpenGLContext *m_ogrecontext;
    QSGTexture *m_texture;
    OgreEngine *app;
    bool m_needResetTexture;
};
