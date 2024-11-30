#include "QOgreItem.h"
#include <QSGSimpleTextureNode>
#include <QSGImageNode>
#include <QSGSimpleRectNode>
#include <QQuickWindow>
#include <QImage>
#include <iostream>
#include <OgreEngine.h>
#include <QThread>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <OgreInput.h>
#include <QEvent>
#include <QTime>
#include <QMutexLocker>

std::vector<OgreBites::Event> convert(const QEvent *in)
{
    static QPoint lastMousePos;
    std::vector<OgreBites::Event> out;
    OgreBites::Event e;
    e.type = 0;

    switch (in->type())
    {
    case QEvent::MouseButtonRelease:
        e.type = OgreBites::MOUSEBUTTONUP;
        OGRE_FALLTHROUGH;
    case QEvent::MouseButtonPress:
        if (!e.type)
            e.type = OgreBites::MOUSEBUTTONDOWN;
        {
            auto *mouse = static_cast<const QMouseEvent *>(in);
            e.button.x = mouse->x();
            e.button.y = mouse->y();
            e.button.button = mouse->button();
            lastMousePos = mouse->pos();

            if (e.button.button == Qt::RightButton)
                e.button.button = OgreBites::BUTTON_RIGHT;
        }
        out.push_back(e);
        break;
    case QEvent::Wheel:
        e.type = OgreBites::MOUSEWHEEL;
        e.wheel.y = static_cast<const QWheelEvent *>(in)->angleDelta().y();
        e.wheel.y = e.wheel.y > 0 ? 1 : -1;
        out.push_back(e);
        break;
    case QEvent::MouseMove:
        e.type = OgreBites::MOUSEMOTION;
        {
            auto *mouse = static_cast<const QMouseEvent *>(in);
            e.motion.x = mouse->x();
            e.motion.y = mouse->y();
            e.motion.xrel = mouse->x() - lastMousePos.x();
            e.motion.yrel = mouse->y() - lastMousePos.y();
            lastMousePos = mouse->pos();
        }
        out.push_back(e);
        break;
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {
        auto touchEvent = static_cast<const QTouchEvent *>(in);
        for (const auto &p : touchEvent->touchPoints())
        {
            e.type = 0;
            if (p.state() == Qt::TouchPointPressed)
            {
                e.type = OgreBites::FINGERDOWN;
            }
            else if (p.state() == Qt::TouchPointReleased)
            {
                e.type = OgreBites::FINGERUP;
            }
            else if (p.state() == Qt::TouchPointMoved)
            {
                e.type = OgreBites::FINGERMOTION;
            }
            else if (p.state() == Qt::TouchPointStationary)
            {
                continue;
            }
            e.tfinger.fingerId = p.id();
            e.tfinger.x = p.pos().x();
            e.tfinger.y = p.pos().y();
            e.tfinger.dx = p.pos().x() - p.lastPos().x();
            e.tfinger.dy = p.pos().y() - p.lastPos().y();
            out.push_back(e);
        }
    }
    break;
    default:
        break;
    }
    return out;
}

QOgreItem::QOgreItem(QQuickItem *parent)
    : QQuickItem(parent),
      m_texture(nullptr),
      texId(0),
      m_qtcontext(nullptr),
      m_ogrecontext(nullptr),
      app(nullptr)
{
    setFlag(ItemHasContents, true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptTouchEvents(true);
    connect(this, &QQuickItem::windowChanged, this, &QOgreItem::onWindowChanged);
    setFocus(true);
}

void QOgreItem::onWindowChanged(QQuickWindow *window)
{
    connect(window, &QQuickWindow::beforeRendering, this, &QOgreItem::onBeforeRendering, Qt::DirectConnection);
}

void QOgreItem::onBeforeRendering()
{
    if (!m_ogrecontext)
    {
        m_qtcontext = QOpenGLContext::currentContext();
        m_ogrecontext = new QOpenGLContext();
        m_ogrecontext->setFormat(m_qtcontext->format());
        m_ogrecontext->setShareContext(m_qtcontext);
        m_ogrecontext->create();
    }
    auto lastCtx = _makeContextCurrent(m_ogrecontext);
    app = OgreEngine::getInstance();
    app->initialize(true);
    if (!texId)
    {
        resetTexture();
    }
    app->renderOneFrame();
    _makeContextCurrent(lastCtx);
}

QOpenGLContext *QOgreItem::_makeContextCurrent(QOpenGLContext *newCtx)
{
    auto lastCtx = QOpenGLContext::currentContext();
    newCtx->makeCurrent(window());
    return lastCtx;
}

void QOgreItem::resetTexture()
{
    if (!app || !app->isInitialized())
    {
        return;
    }
    auto lastCtx = QOpenGLContext::currentContext();
    _makeContextCurrent(m_ogrecontext);
    texId = app->createNewTexture(width(), height());
    _makeContextCurrent(m_qtcontext);
    if (m_texture)
    {
        delete m_texture;
    }
    m_texture = window()->createTextureFromNativeObject(
        QQuickWindow::NativeObjectTexture,
        &texId,
        0,
        QSize(width(), height()),
        QQuickWindow::TextureHasAlphaChannel);
    m_texture->bind();
    _makeContextCurrent(lastCtx);
}

QSGNode *QOgreItem::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGImageNode *node = static_cast<QSGImageNode *>(oldNode);
    if (!node)
    {
        node = window()->createImageNode();
        node->setRect(boundingRect());
        // TODO add other default texture
        m_texture = window()->createTextureFromImage(QImage(":/RenderOutput.png"));
        m_texture->bind();
        node->setTexture(m_texture);
    }

    {
        // QMutexLocker locker(&m_mutex); //not really needed
        if (m_needResetTexture)
        {
            resetTexture();
            node->setTexture(m_texture);
            node->setRect(boundingRect());
            m_needResetTexture = false;
        }
    }

    node->markDirty(QSGNode::DirtyMaterial);
    update();

    return node;
}

void QOgreItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    {
        // QMutexLocker locker(&m_mutex);
        m_needResetTexture = true;
    }
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}

bool QOgreItem::event(QEvent *event)
{
    auto mouseEvent = dynamic_cast<QMouseEvent *>(event);
    auto wheelEvent = dynamic_cast<QWheelEvent *>(event);
    auto touchEvent = dynamic_cast<QTouchEvent *>(event);
    if (mouseEvent || wheelEvent || touchEvent)
    {
        for (const auto &e : convert(event))
        {
            app->handleEvent(e);
        }
    }
    return true;
}