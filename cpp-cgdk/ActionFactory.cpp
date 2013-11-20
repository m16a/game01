#include <algorithm>
#include <vector>

#include "ActionFactory.h"
#include "ActionChain.h"
#include "PathFinder.h"
#include "assert.h"

ActionFactory::~ActionFactory(void)
{
}

Vector2d gMainDst(-1,-1);
Vector2d gMediatorDst(-1, -1);

std::list<model::TrooperType> gMove_head;

std::list<Vector2d> gDirections;

const int kMinDist = 1;
const int kMaxDist = 4;

bool isFeetDirection(const Vector2d& v, int x, int y, const Vector2d& dir){
	bool res = false;

	int dx = x - v.x();
	int dy = y - v.y();

	if (dir.x())
		res = abs(dy) <= kMinDist && dx * dir.x() >= 0;
	else
		res = abs(dx) <= kMinDist && dy * dir.y() >= 0;

	return res;
}


std::vector<Vector2d> getDstsWithDir(const model::World& w, const Vector2d susanin_v, const Vector2d dir){
	std::vector<Vector2d> res;
	const std::vector<std::vector<model::CellType> >& cells = w.getCells();
	for (int i = 0; i < w.getWidth(); i++)
	for (int j = 0; j < w.getHeight(); j++){
		float d = dist(susanin_v, Vector2d(i, j));

		if (d > kMinDist && d < kMaxDist &&
			cells[i][j] == model::FREE &&
			!PathFinder::isTropperInCell(w, Vector2d(i, j)) &&
			isFeetDirection(susanin_v, i, j, dir))
			res.push_back(Vector2d(i, j));
	}
	return res;
}


bool isTypeAlive(const model::World& w, model::TrooperType type){
	bool res = false;
	const std::vector<model::Trooper> t = w.getTroopers();
	std::vector<model::Trooper>::const_iterator it = t.begin();

	for (; it != t.end(); ++it){
		if (!(it->isTeammate()))
			continue;

		if (it->getType() == type && it->getHitpoints() > 0){
			res = true;
			break;
		}
	}
	return res;
}

Vector2d findDest(const model::World& w, const Vector2d susanin_v){
	Vector2d res(susanin_v);
	do{
		if (gMainDst == Vector2d(-1, -1) && !isTypeAlive(w, model::COMMANDER)){
			if (gDirections.empty())
			{
				gDirections.push_back(Vector2d(1, 0));
				gDirections.push_back(Vector2d(0, 1));
				gDirections.push_back(Vector2d(-1, 0));
				gDirections.push_back(Vector2d(0, -1));
			}

			std::list<Vector2d>::iterator it = gDirections.begin();

			int cnt = 0;
			while (cnt < 8){
				std::vector<Vector2d> available_dst = getDstsWithDir(w, susanin_v, *(gDirections.begin()));
				size_t s = available_dst.size();
				if (s != 0){
					int rand_ind = rand() % s;
					gMainDst = available_dst[rand_ind];
					break;
				}
				else{
					gDirections.push_back(*(gDirections.begin()));
					gDirections.erase(gDirections.begin());
				}
				cnt++;
			}
		}
		if (gMainDst == Vector2d(-1, -1))
			break;

		if (dist(gMainDst, susanin_v) < 1.7){// :)
			gMainDst = Vector2d(-1, -1);
			break;
		}

		PathFinder pf;
		std::list<Vector2d> path = pf.calcOptimalPath(w, susanin_v, gMainDst);
		if (path.empty())
			break;
		
		path.pop_front();

		const int kStepCount = 4;
		int i = 1;
		while (i < kStepCount && !path.empty()){
			res = *(path.begin());
			path.pop_front();
			i++;
		}
	} while (0);
	
	return res;
}

Vector2d findNearestFree(const model::World& w, const Vector2d& src, const Vector2d& dst){//TODO: refactor, very ugly
	if (dist(src, dst) <= 1.1)
		return src;

	Vector2d res(0, 0);
	std::list<Vector2d> n = grabNeighbors(w, dst);
	std::list<Vector2d> neighborsOfNeighbors = n;

	PathFinder pf;
	std::list<Vector2d>::iterator it2 = neighborsOfNeighbors.begin();
	int min = 1000;
	for (; it2 != neighborsOfNeighbors.end(); ++it2){
		std::list<Vector2d> path = pf.calcOptimalPath(w, src, *it2);
		if (path.empty())
			continue;
		path.pop_front();
		int d = path.size();
		if (d < min){
			min = d;
			res = *it2;
		}
	}

	if (min > 7){
		std::list<Vector2d>::iterator it = n.begin();
		for (; it != n.end(); ++it){
			std::list<Vector2d> tmp = grabNeighbors(w, *it);
			neighborsOfNeighbors.insert(neighborsOfNeighbors.begin(), tmp.begin(), tmp.end());
		}
		neighborsOfNeighbors.unique();

		PathFinder pf;
		std::list<Vector2d>::iterator it2 = neighborsOfNeighbors.begin();
		int m = 1000;
		for (; it2 != neighborsOfNeighbors.end(); ++it2){
			std::list<Vector2d> path = pf.calcOptimalPath(w, src, *it2);
			if (path.empty())
				continue;
			path.pop_front();
			int d = path.size();
			if (d < m){
				min = d;
				res = *it2;
			}
		}
	}

	return res;
}

Vector2d processApproximate(const model::World& w, const Vector2d& appr){
	Vector2d res;
	const std::vector<std::vector<model::CellType> >& cells = w.getCells();
	float min = 1 << 20;
	for (int i = 0; i < w.getWidth(); i++)
	for (int j = 0; j < w.getHeight(); j++){
		float d = dist(appr, Vector2d(i, j));
		if (cells[i][j] == model::FREE && min > d){
			min = d;
			res = Vector2d (i, j);
		}
	}
	return res;
}

std::list<ActionChain*> ActionFactory::createChains(const model::World& w, const model::Trooper& trooper, std::list<Tactician::Tactic> tactics, bool isFirstMove){

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
				
				float priority_value = (d ? 0 : 50) + damage;//TODO: to consts
				if (priority_value > max){
					max = priority_value;
					trooperToHeal = &(*it);
				}
			}
		}
		//TODO: improve self healing
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
	
	if (gMainDst == Vector2d(-1, -1)){
		if (model::COMMANDER == trooper.getType()
			&& isActionAvailable(trooper, model::REQUEST_ENEMY_DISPOSITION)){

			const std::vector<model::Player>players = w.getPlayers();
			if (players[0].getApproximateX() != -1 && players[1].getApproximateX() != -1){
				//already we have this info
				std::vector<model::Player>::const_iterator it = players.begin();
				float min = 1 << 20;
				Vector2d approximate(-1, -1);
				for (; it != players.end(); ++it){
					if (it->getName() == "m16a")// || it->getName() == "MyStrategy")
						continue;
					Vector2d tmp(it->getApproximateX(), it->getApproximateY());
					float d = dist(tmp, Vector2d(trooper.getX(), trooper.getY()));
					if (min > d){
						min = d;
						approximate = tmp;
					}
				}
				gMainDst = processApproximate(w, approximate);
			}
			else{
				std::list<ActionChunk> c;
				ActionChunk chunk(model::REQUEST_ENEMY_DISPOSITION, Vector2d(-1, -1));
				c.push_back(chunk);
				ActionChain *new_chain = new ActionChain();
				new_chain->executor = &trooper;
				new_chain->chain = c;
				res_chains.push_back(new_chain);
			}
		}
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
				if (tr_it->isTeammate() && tr_it->getType() == *type_it){
					susanin = &(*tr_it);
				}
			}
		}

		Vector2d dst = Vector2d(susanin->getX(), susanin->getY());
		Vector2d src(trooper.getX(), trooper.getY());
		if (isFirstMove){
			if (trooper.getDistanceTo(*susanin) == 0)
					gMediatorDst = findDest(w, dst);
			else
				gMediatorDst = findNearestFree(w, src, dst);
		}
		dst = gMediatorDst;

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
		else{//try to change susanin
			gMove_head.push_back(*(gMove_head.begin()));
			gMove_head.erase(gMove_head.begin());
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
	case model::REQUEST_ENEMY_DISPOSITION:
		cost = m_game->getCommanderRequestEnemyDispositionCost();
		break;
		//TODO: add more actions
	default:
		assert(0);
		break;
	}



	return t.getActionPoints() >= cost;
}