#include <algorithm>
#include <vector>

#include "ActionFactory.h"
#include "ActionChain.h"
#include "PathFinder.h"
#include "assert.h"

ActionFactory::~ActionFactory(void)
{
}

std::list<model::TrooperType> gMove_head;

std::list<Vector2d> gDirections;

std::vector<Vector2d> getDstsWithDir(const model::World& w, const Vector2d susanin_v, const Vector2d dir){
	std::vector<Vector2d> res;
	const std::vector<std::vector<model::CellType> >& cells = w.getCells();
	for (int i = 0; i < w.getWidth(); i++)
	for (int j = 0; j < w.getHeight(); j++){
		float d = dist(susanin_v, Vector2d(i, j));
		if (d >=1 && d <= 3 &&
			cells[i][j] == model::FREE &&
			!PathFinder::isTropperInCell(w, Vector2d(i, j)) &&
			susanin_v.x() * dir.x() >= i * dir.x() &&
			susanin_v.y() * dir.y() >= j * dir.y())
			res.push_back(Vector2d(i, j));
	}
	return res;
}


Vector2d findDest(const model::World& w, const Vector2d susanin_v){
	Vector2d res(1, 1);

	if (gDirections.empty())
	{
		gDirections.push_back(Vector2d(1, 0));
		gDirections.push_back(Vector2d(0, 1));
		gDirections.push_back(Vector2d(-1, 0));
		gDirections.push_back(Vector2d(0, -1));
	}

	std::list<Vector2d>::iterator it = gDirections.begin();

	//for (; it != gDirections.end(); ++it)
	int cnt = 0;
	while (cnt < 8){
		std::vector<Vector2d> available_dst = getDstsWithDir(w, susanin_v, *(gDirections.begin()));
		size_t s = available_dst.size();
		if (s != 0){
			int rand_ind = rand() % s;
			res = available_dst[rand_ind];
			break;
		}
		else{
			gDirections.push_back(*(gDirections.begin()));
			gDirections.erase(gDirections.begin());
		}
		cnt++;
	}

	return res;
}

std::list<ActionChain*> ActionFactory::createChains(const model::World& w, const model::Trooper& trooper, std::list<Tactician::Tactic> tactics){

	std::list<ActionChain*> res_chains;
	ActionChain* new_chain = NULL;
	const std::vector<model::Trooper>& troopers = w.getTroopers();

	if (model::FIELD_MEDIC == trooper.getType() &&
		isActionAvailable(trooper, model::HEAL)){
		const model::Trooper* trooperToHeal = NULL;
		std::vector<model::Trooper>::const_iterator it = troopers.begin();
		float max = 0;
		for (; it != troopers.end(); ++it){
			int damage = (*it).getMaximalHitpoints() - (*it).getHitpoints();
			if ((*it).isTeammate() && damage > 0){
				float d = trooper.getDistanceTo(*it);
				float priority_value = 20 * d + damage;//TODO: to consts
				if (priority_value > max){
					max = priority_value;
					trooperToHeal = &(*it);
				}
			}
		}
		//TODO: self healing
		if (NULL != trooperToHeal){
			std::list<ActionChunk> c;
			if (trooper.getDistanceTo(*trooperToHeal) > 1.1)
			{

				Vector2d pos(trooperToHeal->getX(), trooperToHeal->getY());
				std::list<Vector2d>neighbors = grabNeighbors(w, pos);
				PathFinder pf;

				std::list<Vector2d>::iterator it = neighbors.begin();

				std::list<Vector2d> bestPath;
				int minLengthPath = 1 << 20;
				for (; it != neighbors.end(); ++it){
					if (PathFinder::isTropperInCell(w, *it))
						continue;
					std::list<Vector2d> p = pf.calcOptimalPath(w, Vector2d(trooper.getX(), trooper.getY()), *it);
					if (p.empty())
						continue;
					p.pop_front();
					if (p.size() < minLengthPath){
						minLengthPath = p.size();
						bestPath = p;
					}
				}


				std::list<Vector2d>::iterator it2 = bestPath.begin();
				for (; it2 != bestPath.end(); ++it2){
					ActionChunk chunk(model::MOVE, *it2);
					c.push_back(chunk);
				}
			}
			ActionChunk chunk(model::HEAL, Vector2d(trooperToHeal->getX(), trooperToHeal->getY()));
			c.push_back(chunk);

			ActionChain *new_chain = new ActionChain();
			new_chain->executor = &trooper;
			new_chain->chain = c;


			ActionChunk first = *(c.begin());
			model::ActionType firstType = first.action_type;

			if (isActionAvailable(trooper, firstType))
				res_chains.push_back(new_chain);
			else
				delete new_chain;
		}
	}

	

	const model::Trooper* enemyToAttack = NULL;
	if (tactics.end() != std::find(tactics.begin(), tactics.end(), Tactician::ATTACK) &&
		isActionAvailable(trooper, model::SHOOT)){
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
		
		model::TrooperType Susanin_type = model::UNKNOWN_TROOPER;
		if (gMove_head.empty()){
			gMove_head.push_back(model::SOLDIER);
			gMove_head.push_back(model::COMMANDER);
			gMove_head.push_back(model::FIELD_MEDIC);
		}

		std::list<model::TrooperType>::iterator type_it = gMove_head.begin();
		const model::Trooper *susanin = NULL;
		for (; type_it != gMove_head.end() && susanin == NULL; ++type_it){
			std::vector<model::Trooper>::const_iterator tr_it = troopers.begin();
			for (; tr_it != troopers.end(); ++tr_it){
				if (tr_it->getType() == *type_it){
					susanin = &(*tr_it);
				}
			}
		}

		Vector2d dst(-1, -1);
		dst = Vector2d(susanin->getX(), susanin->getY());
		if (trooper.getDistanceTo(*susanin) == 0){
			//dst = Vector2d(1, 18);
			//TODO: where to go?
			dst = findDest(w, dst);
		}
		
		if (PathFinder::isTropperInCell(w, dst)){
			std::list<Vector2d> n = grabNeighbors(w, dst);
			std::list<Vector2d>::iterator it = n.begin();
			float min = 1 << 20;
			for (; it != n.end(); ++it){
				float d = trooper.getDistanceTo(it->x(), it->y());
				if (d < min){
					min = d;
					dst = *it;
				}
			}

		}


		Vector2d src(trooper.getX(), trooper.getY());
		PathFinder pf;
		std::list<Vector2d> path = pf.calcOptimalPath(w, src, dst);
		if (!path.empty()){
			path.pop_front();

			std::list<Vector2d>::iterator it = path.begin();

			std::list<ActionChunk> c;

			for (; it != path.end(); ++it){
				if (!PathFinder::isTropperInCell(w, *it)){//TODO: eliminate
					ActionChunk chunk(model::MOVE, *it);
					c.push_back(chunk);
				}
			}
			new_chain = new ActionChain();
			new_chain->executor = &trooper;
			new_chain->chain = c;
			res_chains.push_back(new_chain);
		}
	}


	return res_chains;

}


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
	case model::HEAL:
		cost = m_game->getFieldMedicHealCost();
		break;
		//TODO: add more actions
	default:
		assert(0);
		break;
	}



	return t.getActionPoints() >= cost;
}