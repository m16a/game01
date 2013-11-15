#pragma once
#include "Strategy.h"
#include <list>

enum ActionType{
	NONE,
	SURVIVE,
	ATTACK,
	MOVE,
	SPECIAL
};

class Tactician
{
public:
	Tactician(model::World* w):m_w(w){};
	virtual ~Tactician(void);
	
	std::list<ActionType> getActions() const;

protected:
	model::World* m_w; //weak

};
