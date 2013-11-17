#include <algorithm>

#include "ActionFactory.h"
#include "ActionChain.h"
#include "PathFinder.h"
#include "assert.h"

ActionFactory::~ActionFactory(void)
{
}

std::list<ActionChain*> ActionFactory::createChains(const model::World& w, const model::Trooper& trooper, std::list<Tactician::Tactic> tactics){
	std::list<ActionChain*> res_chains;
	ActionChain* new_chain = NULL;
	
	const model::Trooper* enemyToAttack = NULL;
	if (tactics.end() != std::find(tactics.begin(), tactics.end(), Tactician::ATTACK) &&
		isActionAvailable(trooper, model::SHOOT)){
		const std::vector<model::Trooper>& troopers = w.getTroopers();
		std::vector<model::Trooper>::const_iterator it = troopers.begin();

		
		float min = 1 << 20;
		for (; it != troopers.end(); ++it){
			if (!(*it).isTeammate()){
				float d = trooper.getDistanceTo(*it);
				if (d <= min && w.isVisible(trooper.getShootingRange(), trooper.getX(), trooper.getY(), trooper.getStance(), it->getX(), it->getY(), it->getStance())){
					min = d;
					enemyToAttack = &(*it);
				}		
			}
		}
	}
	if (enemyToAttack){
		new_chain = new ActionChain();
		std::list<ActionChunk> c;
		ActionChunk chunk(model::SHOOT, Vector2d(enemyToAttack->getX(), enemyToAttack->getY()));
		c.push_back(chunk);
		c.push_back(chunk);
		c.push_back(chunk);
		new_chain->executor = &trooper;
		new_chain->chain = c;
		res_chains.push_back(new_chain);
	}
	
	if (tactics.end() != std::find(tactics.begin(), tactics.end(), Tactician::MOVE) && 
		isActionAvailable(trooper, model::MOVE))
	{
		Vector2d dst(1, 18);
		Vector2d src(trooper.getX(), trooper.getY());
		PathFinder pf;
		std::list<Vector2d> path = pf.calcOptimalPath(w, src, dst);
		path.pop_front();

		std::list<Vector2d>::iterator it = path.begin();

		std::list<ActionChunk> c;

		for (; it != path.end(); ++it){
			ActionChunk chunk(model::MOVE, *it);
			c.push_back(chunk);
		}
		new_chain = new ActionChain();
		new_chain->executor = &trooper;
		new_chain->chain = c;
		res_chains.push_back(new_chain);
	}


	return res_chains;

}

//MOVE = 1,
//SHOOT = 2,
//RAISE_STANCE = 3,
//LOWER_STANCE = 4,
//THROW_GRENADE = 5,
//USE_MEDIKIT = 6,
//EAT_FIELD_RATION = 7,
//HEAL = 8,
//REQUEST_ENEMY_DISPOSITION = 9

//PRONE = 0,
//KNEELING = 1,
//STANDING = 2,

bool ActionFactory::isActionAvailable(const model::Trooper& t, model::ActionType action){
	int cost = 0;
	switch (action)
	{
	case model::MOVE:
		if (t.getStance() == model::PRONE)
			cost = m_game->getProneMoveCost();
		else if (t.getStance() == model::KNEELING)
			cost = m_game->getKneelingMoveCost();
		else
			cost = m_game->getStandingMoveCost();
		break;
	case model::SHOOT:
		cost = t.getShootCost();
		break;
		//TODO: add more actions
	default:
		assert(0);
		break;
	}



	return t.getActionPoints() >= cost;
}