#pragma once
#include "Strategy.h"
#include <list>


class Tactician
{
public:
	enum Tactic{
		NONE,
		SURVIVE,
		ATTACK,
		MOVE,
		SPECIAL
	};


	Tactician(const model::World* w):m_w(w){};
	virtual ~Tactician(void);
	
	std::list<Tactic> getActions() const;

protected:
	const model::World* m_w; //weak

};
