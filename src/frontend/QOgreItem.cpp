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

namespace OgreBites
{
    Event convert(const QEvent *in)
    {
        static QPoint lastMousePos;

        Event out;

        out.type = 0;

        switch (in->type())
        {
        case QEvent::KeyPress:
            out.type = KEYDOWN;
            OGRE_FALLTHROUGH;
        case QEvent::KeyRelease:
            // ignore auto repeated key-up events to match SDL
            if (!out.type && !static_cast<const QKeyEvent *>(in)->isAutoRepeat())
                out.type = KEYUP;
            {
                auto *key = static_cast<const QKeyEvent *>(in);
                out.key.repeat = key->isAutoRepeat();
                switch (key->key())
                {
                case Qt::Key_Escape:
                    out.key.keysym.sym = SDLK_ESCAPE;
                    break;
                case Qt::Key_Return:
                    out.key.keysym.sym = SDLK_RETURN;
                    break;
                default:
                    out.key.keysym.sym = std::tolower(key->key());
                    break;
                }
                // out.key.keysym.mod = key->modifiers();
            }
            break;
        case QEvent::MouseButtonRelease:
            out.type = MOUSEBUTTONUP;
            OGRE_FALLTHROUGH;
        case QEvent::MouseButtonPress:
            if (!out.type)
                out.type = MOUSEBUTTONDOWN;

            {
                auto *mouse = static_cast<const QMouseEvent *>(in);
                out.button.x = mouse->x();
                out.button.y = mouse->y();
                out.button.button = mouse->button();
                lastMousePos = mouse->pos();

                if (out.button.button == Qt::RightButton)
                    out.button.button = BUTTON_RIGHT;
            }
            break;
        case QEvent::Wheel:
            out.type = MOUSEWHEEL;
            out.wheel.y = static_cast<const QWheelEvent *>(in)->angleDelta().y();
            out.wheel.y = out.wheel.y > 0 ? 1 : -1;
            break;
        case QEvent::MouseMove:
            out.type = MOUSEMOTION;
            {
                auto *mouse = static_cast<const QMouseEvent *>(in);
                out.motion.x = mouse->x();
                out.motion.y = mouse->y();
                out.motion.xrel = mouse->x() - lastMousePos.x();
                out.motion.yrel = mouse->y() - lastMousePos.y();

                lastMousePos = mouse->pos();

                // out.motion.windowID = in.motion.windowID;
            }
            break;
        case QEvent::TouchBegin:
            out.type = FINGERDOWN;
            OGRE_FALLTHROUGH;
        case QEvent::TouchEnd:
            if (!out.type)
                out.type = FINGERUP;
            OGRE_FALLTHROUGH;
        case QEvent::TouchUpdate:
            if (!out.type)
                out.type = FINGERMOTION;
            {
                auto *touch = static_cast<const QTouchEvent *>(in);
                out.tfinger.x = touch->touchPoints()[0].pos().x();
                out.tfinger.y = touch->touchPoints()[0].pos().y();
                // out.tfinger.dx = in.tfinger.dx;
                // out.tfinger.dy = in.tfinger.dy;
                out.tfinger.fingerId = touch->touchPoints()[0].id();
            }
            break;
        default:
            break;
        }
        return out;
    }
} // namespace OgreBites

QOgreItem::QOgreItem(QQuickItem *parent)
    : QQuickItem(parent), m_texture(nullptr)
{
    setFlag(ItemHasContents, true);
    setFlag(ItemAcceptsInputMethod, true);
    setAcceptedMouseButtons(Qt::AllButtons);
    // setAcceptHoverEvents(true);
    setAcceptTouchEvents(true);
    connect(this, &QQuickItem::windowChanged, this, &QOgreItem::onWindowChanged);
    setFocus(true);
    app = new OgreEngine(true);
}

void QOgreItem::onWindowChanged(QQuickWindow *window)
{
    connect(window, &QQuickWindow::beforeRendering, this, &QOgreItem::onBeforeRendering, Qt::DirectConnection);
}

uint texId, texWidth, texHeight;
void QOgreItem::onBeforeRendering()
{
    m_qtcontext = QOpenGLContext::currentContext();
    m_ogrecontext = new QOpenGLContext();
    m_ogrecontext->setFormat(m_qtcontext->format());
    m_ogrecontext->setShareContext(m_qtcontext);
    m_ogrecontext->create();
    _makeOgreCurrent();
    app->initApp();
    app->setupScene();
    app->getFrame(&texId, &texWidth, &texHeight);
    app->renderOneFrame();
    _makeQtCurrent();
    disconnect(window(), &QQuickWindow::beforeRendering, this, &QOgreItem::onBeforeRendering);
}

void QOgreItem::_makeOgreCurrent()
{
    if (!m_ogrecontext || !m_qtcontext || QOpenGLContext::currentContext() == m_ogrecontext)
    {
        return;
    }
    m_qtcontext->doneCurrent();
    m_ogrecontext->makeCurrent(window());
}

void QOgreItem::_makeQtCurrent()
{
    if (!m_ogrecontext || !m_qtcontext || QOpenGLContext::currentContext() == m_qtcontext)
    {
        return;
    }
    m_ogrecontext->doneCurrent();
    m_qtcontext->makeCurrent(window());
}

QSGNode *QOgreItem::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGImageNode *node = static_cast<QSGImageNode *>(oldNode);
    if (!node)
    {
        node = window()->createImageNode();
        node->setRect(boundingRect());
    }

    if (!m_texture && !texId)
    {
        // create a default texture for qsgimagenode in case ogre is not yet initialized
        m_texture = window()->createTextureFromImage(QImage(":/RenderOutput.png"));
        m_texture->bind();
    }

    if (app && app->isInitialized())
    {

        _makeOgreCurrent();
        // app->moveCamera();
        app->renderOneFrame();
        app->getFrame(&texId, &texWidth, &texHeight);
        _makeQtCurrent();
        if (m_texture)
        {
            delete m_texture;
        }
        m_texture = window()->createTextureFromNativeObject(
            QQuickWindow::NativeObjectTexture,
            &texId,
            0,
            QSize(texWidth, texHeight),
            QQuickWindow::TextureHasAlphaChannel);

        m_texture->bind();
    }

    node->setTexture(m_texture);
    node->markDirty(QSGNode::DirtyMaterial);
    update();

    return node;
}

bool QOgreItem::event(QEvent *event)
{
    app->handleEvent(OgreBites::convert(event));
    // event->accept();
    return true;
}