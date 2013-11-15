#include "Tactician.h"

Tactician::~Tactician(void)
{
}

std::list<ActionType> Tactician::getActions() const{
	std::list<ActionType> res;
	const vector<Trooper>& troopers = m_w->getTroopers();
	vector<Trooper>::iterator it = troopers.begin();

	bool isEnemy = false;
	
	for(;it != troopers.end(); ++it){
		if (!(*it).isTeammate()){
			isEnemy = true;
			break;
		}
	}
	
	if (isEnemy)
		res.push_back(ATTACK);

	return res;
}