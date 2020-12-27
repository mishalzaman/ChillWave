#ifndef PLR_AGENT_H
#define PLR_AGENT_H

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;

class PLR_Agent
{
public:
	PLR_Agent(vector3df position);
	~PLR_Agent();
	vector3df getPosition();
private:
	vector3df m_position = vector3df(0,0,0);
};

#endif
