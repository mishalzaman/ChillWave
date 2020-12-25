#include "G_Shader.h"

G_Shader::G_Shader(io::path vsFileName, io::path fsFileName, irr::IrrlichtDevice* device, video::IVideoDriver* driver):
    vsFileName(vsFileName),
    fsFileName(fsFileName)
{
    this->load(device, driver);
    this->material(device, driver);
}

G_Shader::~G_Shader()
{
}

void G_Shader::load(irr::IrrlichtDevice* device, video::IVideoDriver* driver)
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

void G_Shader::material(irr::IrrlichtDevice* device, video::IVideoDriver* driver)
{
    video::IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();

    U_ShaderUniformCallback_Type1* shaderCallback = new U_ShaderUniformCallback_Type1(device);

    const video::E_GPU_SHADING_LANGUAGE shadingLanguage = video::EGSL_DEFAULT;

    this->material1 = gpu->addHighLevelShaderMaterialFromFiles(
        this->vsFileName, "vertexMain", video::EVST_VS_4_1,
        this->fsFileName, "pixelMain", video::EPST_PS_4_1,
        shaderCallback, video::EMT_SOLID, 0, shadingLanguage);

    shaderCallback->drop();
}
