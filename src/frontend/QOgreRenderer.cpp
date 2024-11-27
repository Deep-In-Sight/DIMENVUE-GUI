#include "QOgreRenderer.h"
#include <OgreInput.h>

OgreBites::ButtonType qt2ogre(Qt::MouseButton button)
{
    switch (button)
    {
    case Qt::LeftButton:
        return OgreBites::BUTTON_LEFT;
    case Qt::RightButton:
        return OgreBites::BUTTON_RIGHT;
    case Qt::MiddleButton:
        return OgreBites::BUTTON_MIDDLE;
    default:
        return OgreBites::BUTTON_LEFT;
    }
}

OgreBites::Event convert(const QEvent *in)
{
    static QPoint lastMousePos;

    OgreBites::Event out;

    out.type = 0;

    switch (in->type())
    {
    case QEvent::KeyPress:
        out.type = OgreBites::KEYDOWN;
        OGRE_FALLTHROUGH;
    case QEvent::KeyRelease:
        // ignore auto repeated key-up events to match SDL
        if (!out.type && !static_cast<const QKeyEvent *>(in)->isAutoRepeat())
            out.type = OgreBites::KEYUP;
        {
            auto *key = static_cast<const QKeyEvent *>(in);
            out.key.repeat = key->isAutoRepeat();
            switch (key->key())
            {
            case Qt::Key_Escape:
                out.key.keysym.sym = OgreBites::SDLK_ESCAPE;
                break;
            case Qt::Key_Return:
                out.key.keysym.sym = OgreBites::SDLK_RETURN;
                break;
            default:
                out.key.keysym.sym = std::tolower(key->key());
                break;
            }
            // out.key.keysym.mod = key->modifiers();
        }
        break;
    case QEvent::MouseButtonRelease:
        out.type = OgreBites::MOUSEBUTTONUP;
        OGRE_FALLTHROUGH;
    case QEvent::MouseButtonPress:
        if (!out.type)
            out.type = OgreBites::MOUSEBUTTONDOWN;

        {
            auto *mouse = static_cast<const QMouseEvent *>(in);
            out.button.x = mouse->x();
            out.button.y = mouse->y();
            out.button.button = qt2ogre(mouse->button());
            lastMousePos = mouse->pos();
        }
        break;
    case QEvent::Wheel:
        out.type = OgreBites::MOUSEWHEEL;
        out.wheel.y = static_cast<const QWheelEvent *>(in)->angleDelta().y();
        out.wheel.y = out.wheel.y > 0 ? 1 : -1;
        break;
    case QEvent::MouseMove:
        out.type = OgreBites::MOUSEMOTION;
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
    default:
        break;
    }
    return out;
}

std::vector<OgreBites::Event> convertTouch(const QTouchEvent *in)
{
    std::vector<OgreBites::Event> out;
    for (const auto &p : in->touchPoints())
    {
        OgreBites::Event e;
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
    return out;
}

QOgreRenderer::event(QEvent *event)
{
    auto mouseEvent = dynamic_cast<QMouseEvent *>(event);
    auto wheelEvent = dynamic_cast<QWheelEvent *>(event);
    auto touchEvent = dynamic_cast<QTouchEvent *>(event);
    auto keyEvent = dynamic_cast<QKeyEvent *>(event);
    if (mouseEvent || wheelEvent || keyEvent)
    {
        handleEvent(convert(event));
    }
    if (touchEvent)
    {
        for (const auto &e : convertTouch(touchEvent))
        {
            handleEvent(e);
        }
    }

    return true;
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
