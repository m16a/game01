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
	if (1 || trooper.getId() != m_currExecutorID){

		if (m_chain != NULL){
			delete m_chain;
			m_chain = NULL;
		}

		Tactician t(&w);
		std::list<Tactician::Tactic> tactics = t.getActions();
		

		ActionFactory af(&w, &g);
		std::list<ActionChain*> available_chains = af.createChains(w, trooper, tactics);
		
		Prophet p;

		m_chain = p.chooseBest(available_chains);
	}
}