#include <CameraController.h>
#include <iostream>

CameraController::CameraController(Ogre::SceneNode *cameraNode)
{
    // cameraNode = sm->getRootSceneNode()->createChildSceneNode();
    // cameraYawNode = cameraNode->createChildSceneNode();
    // cameraPitchNode = cameraYawNode->createChildSceneNode();
    // cameraRollNode = cameraPitchNode->createChildSceneNode();
    // cameraRollNode->attachObject(camera);
    // m_moving = false;
    this->cameraNode = cameraNode;
}

CameraController::~CameraController() = default;

bool CameraController::mousePressed(const OgreBites::MouseButtonEvent &evt)
{
    if (evt.button == OgreBites::BUTTON_LEFT)
    {
        m_orienting = true;
    }
    else if (evt.button == OgreBites::BUTTON_RIGHT)
    {
        m_moving = true;
    }
    return OgreBites::InputListener::mousePressed(evt);
}

bool CameraController::mouseReleased(const OgreBites::MouseButtonEvent &evt)
{
    m_orienting = false;
    m_moving = false;
    return OgreBites::InputListener::mouseReleased(evt);
}

bool CameraController::mouseMoved(const OgreBites::MouseMotionEvent &evt)
{
    if (m_orienting)
    {
        float yaw = -evt.xrel * 0.001;
        float pitch = -evt.yrel * 0.001;
        cameraNode->yaw(Ogre::Radian(yaw), Ogre::Node::TS_WORLD);
        cameraNode->pitch(Ogre::Radian(pitch), Ogre::Node::TS_WORLD);
    }
    if (m_moving)
    {
        Ogre::Vector2 dxdy(evt.xrel, evt.yrel);
        dxdy *= 0.01;
        cameraNode->translate(Ogre::Vector3(-dxdy[0], dxdy[1], 0), Ogre::Node::TS_LOCAL);
    }
    return OgreBites::InputListener::mouseMoved(evt);
}

bool CameraController::mouseWheelRolled(const OgreBites::MouseWheelEvent &evt)
{
    auto dz = evt.y;
    cameraNode->translate(Ogre::Vector3(0, 0, dz), Ogre::Node::TS_LOCAL);
    return OgreBites::InputListener::mouseWheelRolled(evt);
}

bool CameraController::touchPressed(const OgreBites::TouchFingerEvent &evt)
{
    auto found = std::find_if(touchEvents.begin(), touchEvents.end(), [evt](const OgreBites::TouchFingerEvent &e)
                              { return e.fingerId == evt.fingerId; });
    if (found == touchEvents.end())
    {
        touchEvents.push_back(evt);
    }
    if (touchEvents.size() == 2)
    {
        Ogre::Vector2 p1(touchEvents[0].x, touchEvents[0].y);
        Ogre::Vector2 p2(touchEvents[1].x, touchEvents[1].y);
        m_lastPinchDistance = p1.distance(p2);
        m_lastPinchPosition = (p1 + p2) / 2;
    }

    return OgreBites::InputListener::touchPressed(evt);
}

bool CameraController::touchReleased(const OgreBites::TouchFingerEvent &evt)
{
    touchEvents.erase(std::remove_if(touchEvents.begin(), touchEvents.end(), [evt](const OgreBites::TouchFingerEvent &e)
                                     { return e.fingerId == evt.fingerId; }),
                      touchEvents.end());
    return OgreBites::InputListener::touchReleased(evt);
}

bool CameraController::touchMoved(const OgreBites::TouchFingerEvent &evt)
{
    // update the stored touchEvents
    auto found = std::find_if(touchEvents.begin(), touchEvents.end(), [evt](const OgreBites::TouchFingerEvent &e)
                              { return e.fingerId == evt.fingerId; });
    if (found != touchEvents.end())
    {
        *found = evt;
    }

    if (touchEvents.size() == 1)
    {
        // single touch to change camera orientation
        float yaw = -evt.dx * 0.001;
        float pitch = -evt.dy * 0.001;
        cameraNode->yaw(Ogre::Radian(yaw), Ogre::Node::TS_WORLD);
        cameraNode->pitch(Ogre::Radian(pitch), Ogre::Node::TS_WORLD);
    }
    else if (touchEvents.size() == 2)
    {
        // two finger touch to move camera
        Ogre::Vector2 p1(touchEvents[0].x, touchEvents[0].y);
        Ogre::Vector2 p2(touchEvents[1].x, touchEvents[1].y);
        auto d = p1.distance(p2);
        auto p = (p1 + p2) / 2;
        auto dz = (m_lastPinchDistance - d) * 0.05;
        auto dxdy = (m_lastPinchPosition - p) * 0.05;
        cameraNode->translate(Ogre::Vector3(dxdy[0], -dxdy[1], dz), Ogre::Node::TS_LOCAL);
        m_lastPinchDistance = d;
        m_lastPinchPosition = p;
    }
    return OgreBites::InputListener::touchMoved(evt);
}