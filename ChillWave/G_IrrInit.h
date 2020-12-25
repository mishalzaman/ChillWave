#ifndef G_IRRINIT_H
#define G_IRRINIT_H

#include <irrlicht.h>
#include "G_EventManager.h"

using namespace irr;

namespace G_IrrInit
{
	bool initialize(
        u32 S_WIDTH,
        u32 S_HEIGHT,
        IrrlichtDevice*& device,
        video::IVideoDriver*& driver,
        G_EventManager& eventReceiver
    ) {
        SIrrlichtCreationParameters params = SIrrlichtCreationParameters();
        params.AntiAlias = 2;
        params.DriverType = video::EDT_OPENGL;
        params.WindowSize = core::dimension2d<u32>(S_WIDTH, S_HEIGHT);
        params.Stencilbuffer = true;
        params.Fullscreen = false;
        params.EventReceiver = &eventReceiver;
        device = createDeviceEx(params);

        if (!device)
            return false;

        device->setWindowCaption(L"CHILL WAVE");

        driver = device->getVideoDriver();

        if (!driver)
            return false;

        return true;
	};

    void deinitialize(IrrlichtDevice* device) {
        device->drop();
    };
};

#endif

