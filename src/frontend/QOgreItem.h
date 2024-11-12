#pragma once

#include <QSGImageNode>
#include <QQuickItem>
#include <QSGTexture>
#include <QSGSimpleTextureNode>
#include <QQuickWindow>
#include <QOpenGLContext>
#include <thread>
#include <OgreEngine.h>

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

private slots:
    void onWindowChanged(QQuickWindow *window);
    void onBeforeRendering();

private:
    void _makeOgreCurrent();
    void _makeQtCurrent();
    bool event(QEvent *event) override;
    QOpenGLContext *m_qtcontext;
    QOpenGLContext *m_ogrecontext;
    QSGTexture *m_texture;
    OgreEngine *app;
};
