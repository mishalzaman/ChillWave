#ifndef G_FPCAMERA_H
#define G_FPCAMERA_H

#include <irrlicht.h>
#include <math.h>

using namespace irr;
using namespace core;
using namespace scene;

class G_FPCamera
{
public:
	G_FPCamera(u32 screenW, u32 screenH, vector3df position, float yAngle, ITriangleSelector* selector, ISceneManager* smgr);
	~G_FPCamera();
	void forward(float dt);
	void reverse(float dt);
	void strafeLeft(float dt);
	void strafeRight(float dt);
	void view(float dt, int x, int y);

	void update(float dt);
	
	void recenterMouse(IrrlichtDevice* device);

	// helpers
	vector3df getPosition();
private:
	const float		  MOVEMENT_SPEED = 4.0;
	const float		  MOUSE_SENSITIVITY = 4.0f;

	// Camera positioning
	ICameraSceneNode* m_camera = 0;
	vector3df		  m_position = vector3df(0, 0, 0);
	vector3df		  m_target = vector3df(0, 0, 0);
	float			  m_yaw = -180.0f;
	float			  m_pitch = -20.f;
	vector3df		  m_up = vector3df(0, 1.0, 0);
	vector3df		  m_frontVector = vector3df(0, 0, 0);
	vector3df		  m_rightVector = vector3df(0, 0, 0);
	vector3df		  m_upVector = vector3df(0, 0, 0);
	
	// Mouse
	int				  m_mouseDefaultX = 0;
	int				  m_mouseDefaultY = 0;

	// Physics
	vector3df		  m_ellipsoidRadius = vector3df(1,2, 1);
	vector3df		  m_gravity = vector3df(0, -1, 0);
	vector3df		  m_ellipsoidTranslation = vector3df(0, 2, 0);
};

#endif

