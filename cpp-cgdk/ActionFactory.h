#pragma once

#include <list>

#include "Strategy.h"
#include "Tactician.h"


class ActionChain;

class ActionFactory
{
public:
	ActionFactory(const model::World* w, const model::Game* g): m_w(w), m_game(g){};
	~ActionFactory(void);
	std::list<ActionChain*> createChains(const model::World& w, const model::Trooper& t, std::list<Tactician::Tactic> tactics);
private:

	bool isActionAvailable(const model::Trooper& t, model::ActionType action);

	const model::World* m_w; //weak
	const model::Game* m_game; //weak
};
