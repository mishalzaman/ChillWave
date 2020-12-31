#ifndef SCN_LEVEL_H
#define SCN_LEVEL_H

#include <irrlicht.h>
#include "M_ShaderGeneral.h"
#include "G_FPCamera.h"
#include "PLR_Agent.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class SCN_Level
{
public:
	SCN_Level(u32 screenW, u32 screenH, IrrlichtDevice* device, IVideoDriver* driver);
	~SCN_Level();
	void attachPlayer(vector3df position);
	void attacheEnvironment(io::path& filename);
	void attachCamera(vector3df position, float yAngle);
	void attachLight(vector3df position);
	void resetView(IrrlichtDevice* device);

	/* Movement */
	void moveForward(float dt);
	void moveBackward(float dt);
	void strafeLeft(float dt);
	void strafeRight(float dt);

	// Main Flow
	void update(float dt, int mouseX, int mouseY);
	void render();

private:
	u32			       m_screenW = 0;
	u32				   m_screenH = 0;
	ISceneManager*	   m_smgr = 0;
	ITriangleSelector* m_selector = 0;
	G_FPCamera*		   m_camera = 0;
	M_ShaderGeneral*		   m_shader = 0;
	PLR_Agent*         m_player = 0;
	ILightSceneNode*   m_light = 0;
};

#endif

