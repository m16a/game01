#pragma once

#include "Strategy.h"

class ActionFactory
{
public:
	ActionFactory(model::World* w): m_w(w){};
	~ActionFactory(void);
	
private:
	model::World* m_w; //weak
};
