#include "SCN_Level.h"

SCN_Level::SCN_Level(u32 screenW, u32 screenH, IrrlichtDevice* device, IVideoDriver* driver):
	m_screenW(screenW),
	m_screenH(screenH)
{
	m_smgr = device->getSceneManager();
    m_shader = new G_Shader("shaders/opengl.vert", "shaders/opengl.frag", device, driver);
}

SCN_Level::~SCN_Level()
{
	delete(m_camera);
	delete(m_player);
    delete(m_shader);
    m_selector->drop();
    m_smgr->drop();
}

void SCN_Level::attachPlayer(vector3df position)
{
	m_player = new PLR_Agent(position);
}

void SCN_Level::attacheEnvironment(io::path& filename)
{
    scene::IMesh* envMesh = m_smgr->getMesh("assets/world/world.obj");
    if (!envMesh)
        printf("ERROR::SCN_LEVEL::attacheEnvironment() Could not load mesh");

    scene::IMeshSceneNode* env = 0;
    env = m_smgr->addOctreeSceneNode(envMesh, 0, 1);
    envMesh->drop();
    env->setMaterialFlag(video::EMF_LIGHTING, false);
    env->setMaterialFlag(video::EMF_BILINEAR_FILTER, false);
    env->setMaterialFlag(video::EMF_ANISOTROPIC_FILTER, true);
    env->setMaterialType((video::E_MATERIAL_TYPE)m_shader->material1);
    env->setScale(core::vector3df(1, 1, 1));

    m_selector = m_smgr->createOctreeTriangleSelector(
        env->getMesh(), env, 128);
}

void SCN_Level::attachCamera(vector3df position, float yAngle)
{
	m_camera = new G_FPCamera(m_screenW, m_screenW, position, yAngle, m_selector, m_smgr);
}

void SCN_Level::attachLight(vector3df position)
{
    m_light = m_smgr->addLightSceneNode();
    m_light->setPosition(core::vector3df(0, 64, 32));
}

void SCN_Level::resetView(IrrlichtDevice* device)
{
    m_camera->recenterMouse(device);
}

void SCN_Level::moveForward(float dt)
{
    m_camera->forward(dt);
}

void SCN_Level::moveBackward(float dt)
{
    m_camera->reverse(dt);
}

void SCN_Level::strafeLeft(float dt)
{
    m_camera->strafeLeft(dt);
}

void SCN_Level::strafeRight(float dt)
{
    m_camera->strafeRight(dt);
}

void SCN_Level::update(float dt, int mouseX, int mouseY)
{
    m_camera->view(dt, mouseX, mouseY);
    m_camera->update(dt);
}

void SCN_Level::render()
{
    m_smgr->drawAll();
}
