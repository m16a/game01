#pragma once
#include <list>
#include "model/Trooper.h"
#include "GeomMisc.h"
#include "Strategy.h"

struct ActionChunk{
	ActionChunk(model::ActionType type, Vector2d v): action_type(type), target(v){};

	model::ActionType action_type;
	Vector2d target;
};

class ActionChain
{
public:
	ActionChain(void);
	virtual ~ActionChain(void);
	const model::Trooper* executor; //weak
	std::list<ActionChunk> chain;	
};
