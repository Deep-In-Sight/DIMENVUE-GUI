#include <CameraController.h>
#include <iostream>

CameraController::CameraController()
{
    reset();
}

CameraController::~CameraController() = default;

void CameraController::reset()
{
    m_moving = false;
    m_orienting = false;
    m_rSpeed = 0.001;
    m_tSpeed = 0.01;
    m_zSpeed = 0.1;
    m_yawLocked = false;
    m_fingerIds = Eigen::Vector2i(-1, -1);
    m_fingerPositions[0] = Eigen::Vector2d(0, 0);
    m_fingerPositions[1] = Eigen::Vector2d(0, 0);
    m_lastPinchDistance = 0;
    m_lastPinchPosition = Eigen::Vector2d(0, 0);
    m_position = Eigen::Vector3d(0, 0, 0);
    m_quaternion = Eigen::Quaterniond(1, 0, 0, 0);
}

void CameraController::mousePressed(MouseButton button, float x, float y)
{
    m_orienting = (button == LEFT);
    m_moving = (button == RIGHT);
    m_lastMousePosition = Eigen::Vector2i(x, y);
}

void CameraController::mouseReleased(MouseButton button)
{
    m_orienting = (button == LEFT);
    m_moving = (button == RIGHT);
}

void CameraController::mouseMoved(float x, float y)
{
    auto dx = x - m_lastMousePosition[0];
    auto dy = y - m_lastMousePosition[1];
    m_lastMousePosition = Eigen::Vector2i(x, y);
    if (m_orienting)
    {
        auto pitch = -dx * m_rSpeed;
        auto roll = -dy * m_rSpeed;
        std::cout << "pitch: " << pitch << " roll: " << roll << std::endl;
        rotateLocal(Eigen::Vector3d(0, pitch, roll));
    }
    if (m_moving)
    {
        translateLocal(Eigen::Vector3d(-dx * m_tSpeed, dy * m_tSpeed, 0));
    }
}

void CameraController::mouseWheelRolled(float yangle)
{
    float dz = (yangle > 0) ? 1 : -1;
    translateLocal(Eigen::Vector3d(0, 0, dz * m_zSpeed));
}

void CameraController::touchPressed(int fingerId, float x, float y)
{
    if (m_fingerIds[0] == -1)
    {
        m_fingerIds[0] = fingerId;
        m_fingerPositions[0] = Eigen::Vector2d(x, y);
    }
    else if (m_fingerIds[1] == -1)
    {
        m_fingerIds[1] = fingerId;
        m_fingerPositions[1] = Eigen::Vector2d(x, y);
        m_lastPinchDistance = (m_fingerPositions[0] - m_fingerPositions[2]).norm();
        m_lastPinchPosition = (m_fingerPositions[0] + m_fingerPositions[2]) / 2;
    }
}

void CameraController::touchReleased(int fingerId)
{
    if (m_fingerIds[0] == fingerId)
    {
        m_fingerIds[0] = -1;
    }
    else if (m_fingerIds[1] == fingerId)
    {
        m_fingerIds[1] = -1;
    }
}

void CameraController::touchMoved(int fingerId, float dx, float dy)
{
    // update the stored touchEvents
    if (m_fingerIds[0] == fingerId)
    {
        m_fingerPositions[0] += Eigen::Vector2d(dx, dy);
    }
    else if (m_fingerIds[1] == fingerId)
    {
        m_fingerPositions[1] += Eigen::Vector2d(dx, dy);
    }

    // single touch
    if (m_fingerIds[0] != -1 && m_fingerIds[1] == -1)
    {
        rotateLocal(Eigen::Vector3d(-dx * m_rSpeed, -dy * m_rSpeed, 0));
    }

    // two finger touch
    if (m_fingerIds[0] != -1 && m_fingerIds[1] != -1)
    {
        Eigen::Vector2d p1 = m_fingerPositions[0];
        Eigen::Vector2d p2 = m_fingerPositions[1];
        auto d = (p1 - p2).norm();
        auto p = (p1 + p2) / 2;
        auto dz = (m_lastPinchDistance - d);
        auto dxdy = (m_lastPinchPosition - p);
        m_lastPinchDistance = d;
        m_lastPinchPosition = p;
        translateLocal(Eigen::Vector3d(-dxdy[0] * m_tSpeed, -dxdy[1] * m_tSpeed, dz * m_zSpeed));
    }
}

void CameraController::lockYaw(bool enable)
{
    m_yawLocked = enable;
}

void CameraController::translateLocal(Eigen::Vector3d translation)
{
    m_position += m_quaternion * translation;
    update();
}

void CameraController::rotateLocal(Eigen::Vector3d angles)
{
    Eigen::Quaterniond yaw(Eigen::AngleAxisd(angles[0], Eigen::Vector3d::UnitZ()));
    Eigen::Quaterniond pitch(Eigen::AngleAxisd(angles[1], Eigen::Vector3d::UnitY()));
    Eigen::Quaterniond roll(Eigen::AngleAxisd(angles[2], Eigen::Vector3d::UnitX()));
    Eigen::Quaterniond q;
    q = (!m_yawLocked) ? yaw * pitch * roll : pitch * roll;

    m_quaternion = m_quaternion * q;
    m_quaternion.normalize();
    update();
}

void CameraController::setPosition(Eigen::Vector3d position)
{
    m_position = position;
    update();
}

Eigen::Vector3d CameraController::getPosition()
{
    return m_position;
}

void CameraController::setQuaternion(Eigen::Quaterniond quaternion)
{
    m_quaternion = quaternion;
    update();
}

Eigen::Quaterniond CameraController::getQuaternion()
{
    return m_quaternion;
}

void CameraController::setEuler(Eigen::Vector3d euler)
{
    Eigen::Quaterniond q;
    q = Eigen::AngleAxisd(euler[0], Eigen::Vector3d::UnitZ()) * Eigen::AngleAxisd(euler[1], Eigen::Vector3d::UnitY()) *
        Eigen::AngleAxisd(euler[2], Eigen::Vector3d::UnitX());
    m_quaternion = q;
    update();
}

Eigen::Vector3d CameraController::getEuler()
{
    return m_quaternion.toRotationMatrix().eulerAngles(2, 1, 0);
}

void CameraController::setLookAt(Eigen::Vector3d target)
{
    Eigen::Vector3d forward = (target - m_position).normalized();
    Eigen::Vector3d backward = -forward;
    Eigen::Vector3d worldUp = Eigen::Vector3d::UnitY();
    Eigen::Vector3d right = worldUp.cross(backward).normalized(); // x = y cross z
    Eigen::Vector3d up = backward.cross(right).normalized();      // y = z cross x
    Eigen::Matrix3d rot;
    rot.col(0) = right;    // x
    rot.col(1) = up;       // y
    rot.col(2) = backward; // z

    m_quaternion = Eigen::Quaterniond(rot);
    update();
}

void CameraController::setSpeed(Eigen::Vector3d speed)
{
    m_rSpeed = speed[0];
    m_tSpeed = speed[1];
    m_zSpeed = speed[2];
}

Eigen::Vector3d CameraController::getSpeed()
{
    return Eigen::Vector3d(m_rSpeed, m_tSpeed, m_zSpeed);
}
