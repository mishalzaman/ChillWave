#include "M_ShaderGeneral.h" 

M_ShaderGeneral::M_ShaderGeneral(io::path vsFileName, io::path fsFileName, irr::IrrlichtDevice* device, video::IVideoDriver* driver):
    vsFileName(vsFileName),
    fsFileName(fsFileName)
{
    load(device, driver);
    createMaterial(device, driver);
}

M_ShaderGeneral::~M_ShaderGeneral()
{
}

void M_ShaderGeneral::load(irr::IrrlichtDevice* device, video::IVideoDriver* driver)
{
    if (!driver->queryFeature(video::EVDF_VERTEX_SHADER_3_0) &&
        !driver->queryFeature(video::EVDF_ARB_VERTEX_PROGRAM_1))
    {
        device->getLogger()->log("WARNING: Vertex shaders disabled "\
            "because of missing driver/hardware support.");
        this->vsFileName = "";
    }

    if (!driver->queryFeature(video::EVDF_PIXEL_SHADER_3_0) &&
        !driver->queryFeature(video::EVDF_ARB_FRAGMENT_PROGRAM_1))
    {
        device->getLogger()->log("WARNING: Pixel shaders disabled "\
            "because of missing driver/hardware support.");
        this->fsFileName = "";
    }
}

void M_ShaderGeneral::createMaterial(irr::IrrlichtDevice* device, video::IVideoDriver* driver)
{
    video::IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();

    M_ShaderGeneralUniformCallback* shaderCallback = new M_ShaderGeneralUniformCallback(device);

    const video::E_GPU_SHADING_LANGUAGE shadingLanguage = video::EGSL_DEFAULT;

    this->material1 = gpu->addHighLevelShaderMaterialFromFiles(
        this->vsFileName, "vertexMain", video::EVST_VS_1_1,
        this->fsFileName, "pixelMain", video::EPST_PS_1_1,
        shaderCallback, video::EMT_SOLID, 0, shadingLanguage);

    shaderCallback->drop();
}
