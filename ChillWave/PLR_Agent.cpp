#include "PLR_Agent.h"

PLR_Agent::PLR_Agent(vector3df position):
	m_position(position)
{
}

PLR_Agent::~PLR_Agent()
{
}

vector3df PLR_Agent::getPosition()
{
	return m_position;
}
