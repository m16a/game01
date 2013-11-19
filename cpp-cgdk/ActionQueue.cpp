#include "ActionQueue.h"
#include "GeomMisc.h"
#include "PathFinder.h"
#include "ActionFactory.h"
#include "Tactician.h"
#include "Prophet.h"

ActionQueue::ActionQueue()
{
	m_currExecutorID = -1;
	m_chain = NULL;
}


ActionQueue::~ActionQueue()
{
}

void ActionQueue::createQueue(const model::World& w, const model::Game& g, const model::Trooper& trooper){
	//TODO: now action recalculates on every update. to optimize
	
	bool isFirstMove = false;
	
	if (trooper.getId() != m_currExecutorID){
		isFirstMove = true;
		m_currExecutorID = trooper.getId();
		}
	
	if (m_chain != NULL){
		delete m_chain;
		m_chain = NULL;
	}
	Tactician t(&w);
	std::list<Tactician::Tactic> tactics = t.getActions();
	t.makeSafityMap();

	ActionFactory af(&w, &g);
	std::list<ActionChain*> available_chains = af.createChains(w, trooper, tactics, isFirstMove);
		
	Prophet p;
	m_chain = p.chooseBest(available_chains);
}