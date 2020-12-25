#include <irrlicht.h>
#include "G_EventManager.h"
#include "G_IrrInit.h"
#include "G_FPCamera.h"
#include "G_Shader.h"

using namespace irr;
using namespace core;
using namespace scene;

const u32             S_WIDTH = 1280;
const u32             S_HEIGHT = 720;
G_EventManager        eventReceiver;
IrrlichtDevice*       device = 0;
video::IVideoDriver*  driver;
bool                  quit = false;

int main() {
    if (!G_IrrInit::initialize(S_WIDTH, S_HEIGHT, device, driver, eventReceiver))
        return -1;

    scene::ISceneManager* smgr = device->getSceneManager();
    G_Shader* shader = new G_Shader("shaders/opengl.vert", "shaders/opengl.frag", device, driver);

    /*---------
    ENVIRONMENT
    ----------*/
    scene::IMesh* envMesh = smgr->getMesh("assets/env/env.obj");
    if (!envMesh)
        return -2;

    scene::IMeshSceneNode* env = 0;
    env = smgr->addOctreeSceneNode(envMesh, 0, 1);
    envMesh->drop();
    env->setMaterialFlag(video::EMF_LIGHTING, false);
    env->setMaterialFlag(video::EMF_BILINEAR_FILTER, false);
    env->setMaterialType((video::E_MATERIAL_TYPE)shader->material1);
    env->setScale(core::vector3df(1, 1, 1));

    scene::ITriangleSelector* selector = 0;
    selector = smgr->createOctreeTriangleSelector(
        env->getMesh(), env, 128);

    /*---------
    CAMERA
    ----------*/
    G_FPCamera* camera = new G_FPCamera(S_WIDTH, S_HEIGHT, vector3df(0, 4, 30), -180.0f, selector, smgr);

    /*------------
    LIGHT
    ------------*/
    scene::ILightSceneNode* light = smgr->addLightSceneNode();
    light->setPosition(core::vector3df(0, 64, 32));

    float dt = 0.017f;

    while (device->run() && !quit) {
        if (device->isWindowActive()) {
            if (eventReceiver.isKeyPressed(KEY_ESCAPE)) { quit = true; }
            if (eventReceiver.isKeyDown(KEY_KEY_W)) { camera->forward(dt); }
            if (eventReceiver.isKeyDown(KEY_KEY_S)) { camera->reverse(dt); }
            if (eventReceiver.isKeyDown(KEY_KEY_D)) { camera->strafeRight(dt); }
            if (eventReceiver.isKeyDown(KEY_KEY_A)) { camera->strafeLeft(dt); }

            camera->recenterMouse(device);

            camera->view(dt, eventReceiver.mouse_x()+5, eventReceiver.mouse_y()+5);
            camera->update(dt);

            driver->beginScene(true, true, video::SColor(255, 255, 100, 68));

            smgr->drawAll(); 

            driver->endScene();

            eventReceiver.reset();
        }
    }
    
    delete(shader);
    delete(camera);
    return 0;
}