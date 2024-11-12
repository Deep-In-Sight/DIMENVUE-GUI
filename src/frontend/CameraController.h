#pragma once

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreInput.h>

class CameraController : public OgreBites::InputListener
{
public:
    CameraController(Ogre::SceneManager *sm, Ogre::Camera *camera);
    ~CameraController();

    bool mouseMoved(const OgreBites::MouseMotionEvent &evt) override;
    bool mousePressed(const OgreBites::MouseButtonEvent &evt) override;
    bool mouseReleased(const OgreBites::MouseButtonEvent &evt) override;

private:
    Ogre::SceneNode *cameraNode;
    Ogre::SceneNode *cameraYawNode;
    Ogre::SceneNode *cameraPitchNode;
    Ogre::SceneNode *cameraRollNode;
    bool m_moving;
};