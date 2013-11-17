#include "Tactician.h"
#include "model/Trooper.h"
#include "Strategy.h"

Tactician::~Tactician(void)
{
}

std::list<Tactician::Tactic> Tactician::getActions() const{
	std::list<Tactician::Tactic> res;
	const std::vector<model::Trooper>& troopers = m_w->getTroopers();
	std::vector<model::Trooper>::const_iterator it = troopers.begin();

	bool isEnemy = false;
	
	for(;it != troopers.end(); ++it){
		if (!(*it).isTeammate()){
			isEnemy = true;
			break;
		}
	}
	
	if (isEnemy)
		res.push_back(ATTACK);
	else
		res.push_back(MOVE);
	return res;
}