#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <vector>

class CameraController
{
  public:
    enum MouseButton
    {
        LEFT = 0,
        RIGHT = 1,
        NONE = 2
    };

    CameraController();
    ~CameraController();

    void mousePressed(MouseButton button, float x, float y);
    void mouseMoved(float x, float y);
    void mouseReleased(MouseButton button);
    void mouseWheelRolled(float yangle);
    void touchPressed(int fingerId, float x, float y);
    void touchMoved(int fingerId, float dx, float dy);
    void touchReleased(int fingerId);

    Eigen::Vector3d getPosition();
    void setPosition(Eigen::Vector3d position);
    Eigen::Quaterniond getQuaternion();
    void setQuaternion(Eigen::Quaterniond quaternion);
    Eigen::Vector3d getEuler();
    void setEuler(Eigen::Vector3d euler);
    void setLookAt(Eigen::Vector3d target);
    // rotate speed, translate speed, zoom speed
    void setSpeed(Eigen::Vector3d speed);
    Eigen::Vector3d getSpeed();
    void lockYaw(bool enable);

    // add translate to current position in local frame
    void translateLocal(Eigen::Vector3d translation);
    // yaw, pitch, roll
    void rotateLocal(Eigen::Vector3d yawpitchroll);

    void reset();
    virtual void update() {};

  protected:
    bool m_moving;
    bool m_orienting;
    float m_rSpeed;
    float m_tSpeed;
    float m_zSpeed;
    bool m_yawLocked;
    Eigen::Vector2i m_lastMousePosition;
    Eigen::Vector2i m_fingerIds;
    Eigen::Vector2d m_fingerPositions[2];
    float m_lastPinchDistance;
    Eigen::Vector2d m_lastPinchPosition;
    Eigen::Vector3d m_position;
    Eigen::Quaterniond m_quaternion;
};