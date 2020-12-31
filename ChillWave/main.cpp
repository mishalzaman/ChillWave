/*
Game idea:

Play as an art curator who looks after an art gallery.
During a level segment, the player monster have been released and it is
up to the player to use frames (or different sizes) to capture monsters.
Then once captured, they need to put up the frames on the wall.
*/

#include <irrlicht.h>
#include "G_EventManager.h"
#include "G_IrrInit.h"
#include "SCN_Level.h"
#include <string>

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

    SCN_Level* level = new SCN_Level(S_WIDTH, S_HEIGHT, device, driver);

    io::path environmentFilename = "assets/world/world.obj";
    level->attacheEnvironment(environmentFilename);
    level->attachCamera(vector3df(0, 4, 30), -180.0f);
    level->attachPlayer(vector3df(0, 4, 30));
    level->attachLight(vector3df(0, 64, 32));
    level->resetView(device);

    float dt = 0.017f;
    
    while (device->run() && !quit) {
        if (device->isWindowActive()) {
            level->resetView(device);

            if (eventReceiver.isKeyPressed(KEY_ESCAPE)) { quit = true; }
            if (eventReceiver.isKeyDown(KEY_KEY_W)) { level->moveForward(dt); }
            if (eventReceiver.isKeyDown(KEY_KEY_S)) { level->moveBackward(dt); }
            if (eventReceiver.isKeyDown(KEY_KEY_D)) { level->strafeRight(dt); }
            if (eventReceiver.isKeyDown(KEY_KEY_A)) { level->strafeLeft(dt); }

            level->update(dt, eventReceiver.mouse_x() + 5, eventReceiver.mouse_y() + 5);

            driver->beginScene(true, true, video::SColor(255, 255, 100, 68));

            level->render();

            driver->endScene();

            eventReceiver.reset();
        }
    }
    
    return 0;
}