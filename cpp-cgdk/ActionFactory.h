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
	std::list<ActionChain*> createChains(const model::World& w, const model::Trooper& t, std::list<Tactician::Tactic> tactics, bool isFirstMove);

	bool isActionAvailable(const model::Trooper& t, model::ActionType action);
private:
ActionChain* heal(const model::World& w, const model::Trooper& trooper, std::list<Tactician::Tactic> tactics, bool isFirstMove);

	const model::World* m_w; //weak
	const model::Game* m_game; //weak
};
