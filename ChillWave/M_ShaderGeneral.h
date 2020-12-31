#ifndef M_SHADER_GENERAL_H
#define M_SHADER_GENERAL_H

#include <irrlicht.h>
#include "M_ShaderGeneralUniformCallback.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class M_ShaderGeneral
{
public:
	M_ShaderGeneral(
		io::path vsFileName,
		io::path fsFileName,
		irr::IrrlichtDevice* device,
		video::IVideoDriver* driver
	);
	~M_ShaderGeneral();
	s32 material1 = 0;
private:
	void load(irr::IrrlichtDevice* device, video::IVideoDriver* driver);
	void createMaterial(irr::IrrlichtDevice* device, video::IVideoDriver* driver);
	io::path vsFileName;
	io::path fsFileName;
};

#endif

