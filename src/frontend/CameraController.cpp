#include <CameraController.h>
#include <iostream>

CameraController::CameraController(Ogre::SceneManager *sm, Ogre::Camera *camera)
{
    cameraNode = sm->getRootSceneNode()->createChildSceneNode();
    cameraYawNode = cameraNode->createChildSceneNode();
    cameraPitchNode = cameraYawNode->createChildSceneNode();
    cameraRollNode = cameraPitchNode->createChildSceneNode();
    cameraRollNode->attachObject(camera);
    m_moving = false;
}

CameraController::~CameraController() = default;

bool CameraController::mousePressed(const OgreBites::MouseButtonEvent &evt)
{
    m_moving = true;
    return OgreBites::InputListener::mousePressed(evt);
}

bool CameraController::mouseReleased(const OgreBites::MouseButtonEvent &evt)
{
    m_moving = false;
    return OgreBites::InputListener::mouseReleased(evt);
}

bool CameraController::mouseMoved(const OgreBites::MouseMotionEvent &evt)
{
    if (m_moving)
    {
        float yaw = -evt.xrel * 0.001;
        float pitch = -evt.yrel * 0.001;
        cameraNode->yaw(Ogre::Radian(yaw), Ogre::Node::TS_WORLD);
        cameraNode->pitch(Ogre::Radian(pitch), Ogre::Node::TS_WORLD);
    }
    return OgreBites::InputListener::mouseMoved(evt);
}