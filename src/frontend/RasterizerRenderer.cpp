// #include <ComputeRasterizerWrapper.h>
#include <CameraController.h>
#include <ComputeRasterizerWrapper.h>
#include <GL/glew.h>
#include <OpenGLItem.h>
#include <QMimeData>
#include <QOpenGLFramebufferObject>
#include <QQuickWindow>
#include <RasterizerRenderer.h>
#include <global.h>
#include <iostream>

struct MyCameraController : public CameraController
{
  public:
    MyCameraController(Camera *camera = nullptr) : CameraController()
    {
        this->camera = camera;
    }

    void setTopView(Eigen::Vector3d center, float distance)
    {
        if (camera == nullptr)
        {
            return;
        }

        // Position the camera
        Eigen::Vector3d cameraPosition = center + Eigen::Vector3d(0, 0, distance);
        setPosition(cameraPosition);
        setLookAt(center);
    }

    void setCenterView(Eigen::Vector3d center)
    {
        if (camera == nullptr)
        {
            return;
        }

        setPosition(center);
        setEuler({0, 0, 3.14 / 2});
    }

    void update() override
    {
        if (camera == nullptr)
        {
            return;
        }
        // construct transform matrix from m_position and m_quaternion
        glm::dmat4 world = glm::translate(glm::dmat4(), glm::dvec3(m_position[0], m_position[1], m_position[2]));
        glm::dquat q(m_quaternion.w(), m_quaternion.x(), m_quaternion.y(), m_quaternion.z());
        world = world * glm::mat4_cast(q);
        camera->world = world;
        camera->update();
    }

    Camera *camera = nullptr;
};

RasterizerRenderer::RasterizerRenderer()
{
    initialize();
    renderer = std::make_shared<ComputeRenderer::Renderer>();
    cameraController = std::make_shared<MyCameraController>(renderer->camera.get());
    GlobalVar::cameraController = cameraController.get();
    lasLoader = std::make_shared<ComputeRenderer::LasLoaderSparse>();
    auto computeLoopLas = new ComputeRenderer::ComputeLoopLas(renderer.get(), lasLoader);
    ComputeRenderer::Runtime::addMethod(computeLoopLas);
    ComputeRenderer::Runtime::setSelectedMethod(computeLoopLas->name);
}

QEvent *clone(QEvent *e)
{
    if (dynamic_cast<QMouseEvent *>(e))
    {
        return new QMouseEvent(*static_cast<QMouseEvent *>(e));
    }
    if (dynamic_cast<QWheelEvent *>(e))
    {
        return new QWheelEvent(*static_cast<QWheelEvent *>(e));
    }
    if (dynamic_cast<QTouchEvent *>(e))
    {
        return new QTouchEvent(*static_cast<QTouchEvent *>(e));
    }
    if (dynamic_cast<QDragEnterEvent *>(e))
    {
        return new QDragEnterEvent(*static_cast<QDragEnterEvent *>(e));
    }
    if (dynamic_cast<QDragMoveEvent *>(e))
    {
        return new QDragMoveEvent(*static_cast<QDragMoveEvent *>(e));
    }
    if (dynamic_cast<QDropEvent *>(e))
    {
        return new QDropEvent(*static_cast<QDropEvent *>(e));
    }
    return nullptr;
}

void RasterizerRenderer::queueEvent(QEvent *event)
{
    eventQueueMutex.lock();
    // need some cloning? not sure
    qDebug() << "enqueue event type: " << event->type();
    auto cloned = clone(event);
    eventQueue.enqueue(cloned);
    eventQueueMutex.unlock();
}

void RasterizerRenderer::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::MouseButtonPress:
        mousePressEvent(static_cast<QMouseEvent *>(event));
        break;
    case QEvent::MouseButtonRelease:
        mouseReleaseEvent(static_cast<QMouseEvent *>(event));
        break;
    case QEvent::MouseMove:
        mouseMoveEvent(static_cast<QMouseEvent *>(event));
        break;
    case QEvent::Wheel:
        wheelEvent(static_cast<QWheelEvent *>(event));
        break;
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
        touchEvent(static_cast<QTouchEvent *>(event));
        break;
    case QEvent::DragEnter:
        dragEnterEvent(static_cast<QDragEnterEvent *>(event));
        break;
    case QEvent::DragMove:
        dragMoveEvent(static_cast<QDragMoveEvent *>(event));
        break;
    case QEvent::Drop:
        dropEvent(static_cast<QDropEvent *>(event));
        break;
    default:
        break;
    }
}

void RasterizerRenderer::synchronize(QQuickFramebufferObject *item)
{
    auto *openglItem = static_cast<OpenGLItem *>(item);

    if (openglItem->boundingRect().size() != viewportSize.size())
    {
        viewportSize = openglItem->boundingRect();
        renderer->setSize(viewportSize.width(), viewportSize.height());
    }

    if (framebufferObject() != nullptr)
    {
        renderer->setTargetFbo(framebufferObject()->handle());
    }

    window = openglItem->window();

    static bool loaded = false;
    if (framebufferObject() != nullptr && !loaded)
    {
        lasLoader->add({"/home/linh/cloud.las"});
        auto center = lasLoader->boxCenter;
        auto size = lasLoader->boxSize;
        Eigen::Vector3d extend(size[0] / 2, size[1] / 2, size[2] / 2);
        auto radius = extend.norm();
        float distance = radius / std::sin((cameraController->camera->fovy * 3.14 / 180) / 2.0f);

        cameraController->setCenterView({center[0], center[1], center[2]});
        loaded = true;
    }
    eventQueueMutex.lock();
    while (!eventQueue.isEmpty())
    {
        QEvent *ev = eventQueue.dequeue();
        qDebug() << "Dequeue Event type: " << ev->type() << " accepted: ", ev->isAccepted();
        event(ev);
    }
    eventQueueMutex.unlock();
}

void RasterizerRenderer::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void RasterizerRenderer::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void RasterizerRenderer::dropEvent(QDropEvent *event)
{
    auto urls = event->mimeData()->urls();
    if (urls.isEmpty())
    {
        return;
    }
    std::vector<std::string> lasPaths;
    for (const auto &url : urls)
    {
        auto path = url.toLocalFile();
        if (path.endsWith(".las"))
        {
            lasPaths.push_back(path.toStdString());
        }
    }
    if (!lasPaths.empty())
    {
        lasLoader->add(lasPaths);
    }
}

CameraController::MouseButton buttonMap(Qt::MouseButton b)
{
    switch (b)
    {
    case Qt::LeftButton:
        return CameraController::MouseButton::LEFT;
    case Qt::RightButton:
        return CameraController::MouseButton::RIGHT;
    default:
        return CameraController::MouseButton::NONE;
    }
}

void RasterizerRenderer::mousePressEvent(QMouseEvent *event)
{
    CameraController::MouseButton button = buttonMap(event->button());
    cameraController->mousePressed(button, event->x(), event->y());
}

void RasterizerRenderer::mouseReleaseEvent(QMouseEvent *event)
{
    CameraController::MouseButton button = buttonMap(event->button());
    cameraController->mouseReleased(button);
}

void RasterizerRenderer::mouseMoveEvent(QMouseEvent *event)
{
    cameraController->mouseMoved(event->x(), event->y());
}

void RasterizerRenderer::wheelEvent(QWheelEvent *event)
{
    cameraController->mouseWheelRolled(event->angleDelta().y());
}

void RasterizerRenderer::touchEvent(QTouchEvent *event)
{
    for (const auto &touchPoint : event->touchPoints())
    {
        switch (touchPoint.state())
        {
        case Qt::TouchPointPressed:
            cameraController->touchPressed(touchPoint.id(), touchPoint.pos().x(), touchPoint.pos().y());
            break;
        case Qt::TouchPointReleased:
            cameraController->touchReleased(touchPoint.id());
            break;
        case Qt::TouchPointMoved: {
            auto moved = touchPoint.pos() - touchPoint.lastPos();
            cameraController->touchMoved(touchPoint.id(), moved.x(), moved.y());
            break;
        }
        default:
            break;
        }
    }
}

static void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                   const GLchar *message, const void *userParam)
{

    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION || severity == GL_DEBUG_SEVERITY_LOW ||
        severity == GL_DEBUG_SEVERITY_MEDIUM)
    {
        return;
    }

    cout << "OPENGL DEBUG CALLBACK: " << message << endl;
}

void RasterizerRenderer::initialize()
{
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to initialize GLEW");
    }
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, NULL, GL_TRUE);
    glDebugMessageCallback(debugCallback, NULL);
}

void RasterizerRenderer::render()
{
    renderer->renderOneFrame();
}