#pragma once
#include <list>
#include "Trooper.h"
#include "GeomMisc.h"

struct ActionChunk{
	ActionChunk(model::ActionType type, Vector2d v): action_type(type), target(type){};

	model::ActionType action_type;
	Vector2d target;
};

class Action
{
public:
	Action(void);
	virtual ~Action(void);
	Trooper* executor;
	std::list<ActionChunk> chain;	
};
