#pragma once

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreInput.h>
#include <vector>

class CameraController : public OgreBites::InputListener
{
public:
    CameraController(Ogre::SceneNode *cameraNode);
    ~CameraController();

    bool mouseMoved(const OgreBites::MouseMotionEvent &evt) override;
    bool mousePressed(const OgreBites::MouseButtonEvent &evt) override;
    bool mouseReleased(const OgreBites::MouseButtonEvent &evt) override;
    bool mouseWheelRolled(const OgreBites::MouseWheelEvent &evt) override;
    bool touchPressed(const OgreBites::TouchFingerEvent &evt) override;
    bool touchMoved(const OgreBites::TouchFingerEvent &evt) override;
    bool touchReleased(const OgreBites::TouchFingerEvent &evt) override;

private:
    Ogre::SceneNode *cameraNode;
    Ogre::SceneNode *cameraYawNode;
    Ogre::SceneNode *cameraPitchNode;
    Ogre::SceneNode *cameraRollNode;
    bool m_moving;
    bool m_orienting;
    std::vector<OgreBites::TouchFingerEvent> touchEvents;
    float m_lastPinchDistance;
    Ogre::Vector2 m_lastPinchPosition;
};