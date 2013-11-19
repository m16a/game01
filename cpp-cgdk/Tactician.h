#pragma once
#include "Strategy.h"
#include <list>
#include <vector>
#include "GeomMisc.h"

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

	void makeSafityMap();

private:
	const model::World* m_w; //weak
	Matrix m_safity_map;
};