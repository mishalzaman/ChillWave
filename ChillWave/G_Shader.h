#include <irrlicht.h>
#include "U_ShaderUniformCallback_Type1.h"

using namespace irr;

class G_Shader
{
public:
	G_Shader(io::path vsFileName, io::path fsFileName, irr::IrrlichtDevice* device, video::IVideoDriver* driver);
	~G_Shader();
	s32 material1 = 0;
private:
	void load(irr::IrrlichtDevice* device, video::IVideoDriver* driver);
	void material(irr::IrrlichtDevice* device, video::IVideoDriver* driver);
	io::path vsFileName;
	io::path fsFileName;
};

