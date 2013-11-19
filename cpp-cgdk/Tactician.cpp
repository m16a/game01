#include "Tactician.h"

#include <fstream>
#include <iostream>

std::ofstream gOut("debug.txt");
void ddebugPrint(std::ofstream& outStream, const Matrix& m);
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

	res.push_back(MOVE);
	return res;
}

const int kMaxDistToSafityMap = 7;

void Tactician::makeSafityMap(){
	int width = m_w->getWidth();
	int height = m_w->getHeight();
	std::vector<int> tmp(height, 0);
	for (int i = 0; i < width; i++)
		m_safity_map.push_back(tmp);

	const std::vector<std::vector<model::CellType> >& cells = m_w->getCells();

	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			if (cells[i][j] != model::FREE)
				continue;

			for (int k = 0; k < width; k++){
				for (int l = 0; l < height; l++){
					if (i == k && j==l &&
						dist(Vector2d(i,j), Vector2d(k,l)) > kMaxDistToSafityMap)
						continue;
					//bool World::isVisible(double maxRange,
					//	int viewerX, int viewerY, TrooperStance viewerStance,
					//	int objectX, int objectY, TrooperStance objectStance)
					if (m_w->isVisible(kMaxDistToSafityMap, k, l, model::STANDING, i, j, model::STANDING))
						m_safity_map[i][j]++;
				}
			}
		}
	}


	ddebugPrint(gOut, m_safity_map);
}


void ddebugPrint(std::ofstream& outStream, const Matrix& m){
	int h = m[0].size();
	for(int j = 0; j < h; j++){
		for (int i = 0; i < m.size(); i++)
			outStream << m[i][j] <<'\t';

		outStream << '\n';
	}

	outStream << "--------------------------------------------------------------------------------\n";
}