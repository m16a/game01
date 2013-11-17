#pragma once
#include <list>
#include "ActionChain.h"
#include "Strategy.h"


class ActionQueue
{
public:
	ActionQueue();
	virtual ~ActionQueue();
	ActionChain* m_chain;
	long long m_currExecutorID;

	void createQueue(const model::World& w, const model::Game& g, const model::Trooper& t);
};

