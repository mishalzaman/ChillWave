#ifndef M_SHADER_GENERAL_UNIFORM_CALLBACK_H
#define M_SHADER_GENERAL_UNIFORM_CALLBACK_H

#include <irrlicht.h>

using namespace irr;
using namespace core;

class M_ShaderGeneralUniformCallback : public video::IShaderConstantSetCallBack
{
public:
    struct MatLight {
        vector3df position;
        vector3df ambient;
        vector3df diffuse;
        vector3df specular;
        vector3df direction;
    };

    struct MatMaterial {
        vector3df ambient;
        vector3df diffuse;
        vector3df specular;
        float shininess;
    };
    M_ShaderGeneralUniformCallback(irr::IrrlichtDevice* dev) { device = dev; };
    irr::IrrlichtDevice* device = 0;

    virtual void OnSetConstants(video::IMaterialRendererServices* services,
        s32 userData)
    {
        video::IVideoDriver* driver = services->getVideoDriver();

        MatMaterial m_material;
        m_material.ambient = vector3df(1.0f, 1.0f, 1.0f);
        m_material.diffuse = vector3df(0.8f, 0.8f, 0.8f);
        m_material.specular = vector3df(0.5f, 0.5f, 0.5f);
        m_material.shininess = 32.0f;

        MatLight m_light;
        m_light.position = vector3df(0, 64, 0);
        m_light.ambient = vector3df(0.8f, 0.8f, 0.8f);
        m_light.diffuse = vector3df(0.5f, 0.5f, 0.5f);
        m_light.specular = vector3df(1.0f, 1.0f, 1.0f);
        m_light.direction = vector3df(-0.2f, -1.0f, -0.3f);

        /*==============
        VIEW POSITION
        ===============*/
        core::vector3df pos = device->getSceneManager()->getActiveCamera()->getAbsolutePosition();
        pos = core::vector3df(0, 200, 0);
        services->setVertexShaderConstant("viewPos", reinterpret_cast<f32*>(&pos), 3);

        /*====================
        MATERIAL
        =====================*/
        services->setPixelShaderConstant("material.ambient", reinterpret_cast<f32*>(&m_material.ambient), 3);
        services->setPixelShaderConstant("material.diffuse", reinterpret_cast<f32*>(&m_material.diffuse), 3);
        services->setPixelShaderConstant("material.specular", reinterpret_cast<f32*>(&m_material.specular), 3);
        services->setPixelShaderConstant("material.shininess", &m_material.shininess, 1);

        /*====================
        LIGHT
        =====================*/
        services->setPixelShaderConstant("lightPos", reinterpret_cast<f32*>(&m_light.position), 3);
        services->setPixelShaderConstant("light.position", reinterpret_cast<f32*>(&m_light.position), 3);
        services->setPixelShaderConstant("light.ambient", reinterpret_cast<f32*>(&m_light.ambient), 3);
        services->setPixelShaderConstant("light.diffuse", reinterpret_cast<f32*>(&m_light.diffuse), 3);
        services->setPixelShaderConstant("light.specular", reinterpret_cast<f32*>(&m_light.specular), 3);
        services->setPixelShaderConstant("light.direction", reinterpret_cast<f32*>(&m_light.direction), 3);

        core::matrix4 projection = driver->getTransform(video::ETS_PROJECTION);
        core::matrix4 view  = driver->getTransform(video::ETS_VIEW);
        core::matrix4 model  = driver->getTransform(video::ETS_WORLD);
        core::matrix4 mvp = projection * view * model;

        services->setVertexShaderConstant("projection", projection.pointer(), 16);
        services->setVertexShaderConstant("view", view.pointer(), 16);
        services->setVertexShaderConstant("model", model.pointer(), 16);
        services->setVertexShaderConstant("mvp", mvp.pointer(), 16);


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
        LIGHT COLOUR
        ===============*/
        video::SColorf col(0.4f, 0.4f, 0.4f, 0.0f);
        services->setVertexShaderConstant("lightColor",
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

        /*========
        TIME
        =========*/
        s32 time = device->getTimer()->getTime();
        services->setPixelShaderConstant("iTime", &time, 1);
    }
};

#endif 