#ifndef SHADER_CALLBACK_H
#define SHADER_CALLBACK_H

#include <irrlicht.h>

using namespace irr;

class U_ShaderUniformCallback_Type1 : public video::IShaderConstantSetCallBack
{
public:
    U_ShaderUniformCallback_Type1(irr::IrrlichtDevice* dev) { device = dev; };
    irr::IrrlichtDevice* device = 0;

    virtual void OnSetConstants(video::IMaterialRendererServices* services,
        s32 userData)
    {
        video::IVideoDriver* driver = services->getVideoDriver();

        /*====================
        INVERTED WORLD MATRIX
        =====================*/
        core::matrix4 invWorld = driver->getTransform(video::ETS_WORLD);
        invWorld.makeInverse();

        services->setVertexShaderConstant("u_InverseWorld", invWorld.pointer(), 16);

        /*==========================
        WORLD VIEW PROJECTION MATRIX
        ============================*/
        core::matrix4 worldViewProj;
        worldViewProj = driver->getTransform(video::ETS_PROJECTION);
        worldViewProj *= driver->getTransform(video::ETS_VIEW);
        worldViewProj *= driver->getTransform(video::ETS_WORLD);

        services->setVertexShaderConstant("u_WorldViewProjection", worldViewProj.pointer(), 16);

        /*==============
        CAMERA POSITION
        ===============*/
        core::vector3df pos = device->getSceneManager()->getActiveCamera()->getAbsolutePosition();
        pos = core::vector3df(0, 200, 0);
        services->setVertexShaderConstant("u_CameraPos", reinterpret_cast<f32*>(&pos), 3);

        /*==============
        LIGHT COLOUR
        ===============*/
        video::SColorf col(0.4f, 0.4f, 0.4f, 0.0f);
        services->setVertexShaderConstant("u_LightColour",
                reinterpret_cast<f32*>(&col), 4);

        /*==============
        LIGHT POSITION
        ===============*/
        core::vector3df lPos = core::vector3df(0.0f, 8.0f, 8.0f);
        services->setVertexShaderConstant("lightPos",
            reinterpret_cast<f32*>(&lPos), 3);

        /*==============
        OBJECT COLOUR
        ===============*/
        video::SColorf ocol(0.4f, 0.4f, 0.4f, 0.0f);
        services->setVertexShaderConstant("objectColor",
            reinterpret_cast<f32*>(&ocol), 4);

        /*==============
        TRANSPOSED WORLD
        ===============*/
        core::matrix4 world = driver->getTransform(video::ETS_WORLD);
        world = world.getTransposed();
        services->setVertexShaderConstant("u_TransposedWorld", world.pointer(), 16);

        /*==============
        SCREEN RESOLUTION
        ===============*/
        core::dimension2du screenRes = driver->getScreenSize();
        core::vector2di res = core::vector2di(screenRes.Width, screenRes.Height);
        services->setVertexShaderConstant("u_Resolution", reinterpret_cast<f32*>(&res), 2);

        /*========
        TEXTURE
        =========*/
        s32 TextureLayerID = 0;
        services->setPixelShaderConstant("u_Texture1", &TextureLayerID, 1);

    }
};

#endif