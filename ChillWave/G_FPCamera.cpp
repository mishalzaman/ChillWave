#include "G_FPCamera.h"
#include "U_MathG.h"

G_FPCamera::G_FPCamera(u32 screenW, u32 screenH, vector3df position, float yAngle, ITriangleSelector* selector, ISceneManager* smgr):
    m_position(position),
    m_yaw(yAngle)
{
    /* Set screen mid points X, Y */
    m_mouseDefaultX = screenW / 2;
    m_mouseDefaultY = screenH / 2;

    /* Set camera position and target */
    m_camera_persp = smgr->addCameraSceneNode();
    m_camera_persp->setFOV(0.8);
    m_yaw = yAngle;

    irr::core::matrix4 MyMatrix;
    MyMatrix.buildProjectionMatrixOrthoLH(400.0f, 200.0f, 1.5f, 200.5f);
    m_camera_ortho = smgr->addCameraSceneNode(0, irr::core::vector3df(-14.0f, 14.0f, -14.0f), irr::core::vector3df(0, 0, 0));
    m_camera_ortho->setProjectionMatrix(MyMatrix);

    activatePerspective(smgr);


    /* Set triangle selector for collision */
    if (selector)
    {
        scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
            selector,
            m_camera_persp,
            m_ellipsoidRadius,
            m_gravity,
            m_ellipsoidTranslation
        );
        selector->drop();
        m_camera_persp->addAnimator(anim);
        anim->drop();
    }
}

G_FPCamera::~G_FPCamera()
{
    m_camera_persp->drop();
}

void G_FPCamera::forward(float dt)
{
    m_position = m_camera_persp->getPosition() + m_frontVector * MOVEMENT_SPEED * dt;
}

void G_FPCamera::reverse(float dt)
{
    m_position = m_camera_persp->getPosition() - m_frontVector * MOVEMENT_SPEED * dt;
}

void G_FPCamera::strafeLeft(float dt)
{
    m_position = m_camera_persp->getPosition() + m_rightVector * MOVEMENT_SPEED * dt;
}

void G_FPCamera::strafeRight(float dt)
{
    m_position = m_camera_persp->getPosition() - m_rightVector * MOVEMENT_SPEED * dt;
}

void G_FPCamera::view(float dt, int x, int y)
{
    int xOffset = m_mouseDefaultX - x;
    int yOffset = m_mouseDefaultY - y;

    xOffset *= MOUSE_SENSITIVITY;
    yOffset *= MOUSE_SENSITIVITY;

    m_yaw += xOffset * dt;
    m_pitch += yOffset * dt;

    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;
}

void G_FPCamera::recenterMouse(IrrlichtDevice* device)
{
    device->getCursorControl()->setPosition(m_mouseDefaultX, m_mouseDefaultY);
}

void G_FPCamera::activatePerspective(ISceneManager* smgr)
{
    smgr->setActiveCamera(m_camera_persp);
}

void G_FPCamera::activateOrtho(ISceneManager* smgr)
{
    smgr->setActiveCamera(m_camera_ortho);
}

vector3df G_FPCamera::getPosition()
{
    return m_camera_persp->getPosition();
}

void G_FPCamera::update(float dt)
{
    vector3df front;
    front.X = cos(U_MathG::degreesToRadians(m_yaw)) * cos(U_MathG::degreesToRadians(m_pitch));
    front.Y = sin(U_MathG::degreesToRadians(m_pitch));
    front.Z = sin(U_MathG::degreesToRadians(m_yaw)) * cos(U_MathG::degreesToRadians(m_pitch));

    m_frontVector = front.normalize();
    m_rightVector = (m_frontVector.crossProduct(m_up)).normalize();
    m_upVector = (m_rightVector.crossProduct(m_frontVector)).normalize();

    m_target = m_position + m_frontVector;

    m_camera_persp->setPosition(m_position);
    m_camera_persp->setTarget(m_target);
}
