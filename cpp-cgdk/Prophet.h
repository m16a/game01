#pragma once
#include <list>

#include "Strategy.h"

class ActionChain;

class Prophet
{
public:
	Prophet();
	virtual ~Prophet();

	ActionChain* chooseBest(std::list<ActionChain*> chains);
};

