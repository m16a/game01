#include <list>
#include <algorithm>
#include "assert.h"
#include <string>

#include <fstream>
#include <iostream>
#include <math.h>

#include "PathFinder.h"
#include "GeomMisc.h"


//Node for A* search
//f(x) = g(x) + h(x)
struct A_node{
	Vector2d _v;
	float _f,_g,_h;
	A_node* _prev;

	A_node(const Vector2d& v, float g = 0, float h = 0, A_node* prev = NULL):_v(v), _g(g), _h(h), _prev(prev){
		_f = _g +_h;
	}

	A_node& operator=(A_node other){
		this->_v = other._v;
		this->_f = other._f;
		this->_g = other._g;
		this->_h = other._h;
		this->_prev = other._prev;

		return *this;
	}


	friend bool operator< (const A_node& a, const A_node& b){
		return a._f < b._f;
	}

	bool operator==(const A_node& rhs)const{
		return rhs._v == this->_v;
	}

};


std::list<Vector2d> reconstructPath(const A_node* end){
	const A_node* cur_node = end;
	std::list<Vector2d> result;
	while (NULL != cur_node){
		result.push_front(cur_node->_v);
		cur_node = cur_node->_prev;
	}
	return result;
}
bool PathFinder::isTropperInCell(const model::World& w, const Vector2d& v){
	const std::vector<model::Trooper>& troopers = w.getTroopers();
	bool res = false;
	std::vector<model::Trooper>::const_iterator it = troopers.begin();
	for (; it != troopers.end(); ++it){
		if (Vector2d(it->getX(), it->getY()) == v){
			res = true;
			break;
		}
	}

	return res;
}

std::list<Vector2d> grabNeighbors(const model::World& w, const Vector2d& v){
	std::list<Vector2d> res;
	const std::vector<std::vector<model::CellType> >& cells = w.getCells();

	if (v.x() - 1 >= 0 && model::FREE == cells[v.x() - 1][v.y()] && !PathFinder::isTropperInCell(w, Vector2d(v.x() - 1, v.y())))
		res.push_back(Vector2d(v.x()-1, v.y()));

	if (v.x() + 1 < w.getWidth() && model::FREE == cells[v.x() + 1][v.y()] && !PathFinder::isTropperInCell(w, Vector2d(v.x() + 1, v.y())))
		res.push_back(Vector2d(v.x()+1, v.y()));

	if (v.y() - 1 >= 0 && model::FREE == cells[v.x()][v.y() - 1] && !PathFinder::isTropperInCell(w, Vector2d(v.x(), v.y() - 1)))
		res.push_back(Vector2d(v.x(), v.y()-1));

	if (v.y() + 1 < w.getHeight() && model::FREE == cells[v.x()][v.y() + 1] && !PathFinder::isTropperInCell(w, Vector2d(v.x(), v.y()+1)))
		res.push_back(Vector2d(v.x(), v.y()+1));

	return res;
}


A_node* getVinNodes(std::list<A_node*>& set, const Vector2d& v){
	A_node* res = NULL;
	std::list<A_node*>::iterator tmp_it = set.begin();
	for(;tmp_it != set.end(); ++tmp_it){
		if (v == (*tmp_it)->_v){
			res = *tmp_it;
			break;
		}
	}
	return res;
}


bool min_for_A_nodes(A_node* a, A_node*b){
	return a->_f < b->_f;
}


static bool deleteAll( A_node * theElement ) { delete theElement; return true; }

typedef float (*heuristic_cost_estimate)(const Vector2d& start, const Vector2d& finish);

float newHeuristic(const Vector2d& start, const Vector2d& finish){
	return (float)abs(start.x() - finish.x()) + abs(start.y() - finish.y());
}

void debugPrint(const model::World& world, std::list<A_node*>& closed_set, std::list<A_node*>& open_set);
void debugPrintPath(const model::World& world, std::list<Vector2d>& path);


std::list<Vector2d> PathFinder::calcOptimalPath(const model::World& world, const Vector2d& start, const Vector2d& finish){
	std::list<A_node*> closed_set;
	std::list<A_node*> open_set;

	heuristic_cost_estimate hce = dist;//let's choose the simplest heuristic - euclidean distance between two points

	A_node *start_node = new A_node(start, 0, hce(start, finish));
	open_set.push_back(start_node);

	while (!open_set.empty()){
		A_node* x = *min_element(open_set.begin(), open_set.end(), min_for_A_nodes);
		//debugPrint(world, closed_set, open_set);

		if (x->_v == finish){
			std::list<Vector2d> res = reconstructPath(x);
			closed_set.remove_if(deleteAll);
			open_set.remove_if(deleteAll);
			//debugPrintPath(world, res);
			return res;
		}
	
		open_set.remove(x);
		closed_set.push_back(x);

		//grab neighbors for x
		std::list<Vector2d> neighbors = grabNeighbors(world, x->_v);
		std::list<Vector2d>::iterator it = neighbors.begin();

		for (;it != neighbors.end(); ++it){

			if (getVinNodes(closed_set, *it) != NULL)
				continue;

			float tentative_g = x->_g + dist(*it, x->_v);

			A_node* y = getVinNodes(open_set, *it);
			if (NULL != y){
				if (tentative_g < y->_g){
					y->_g = tentative_g;
					y->_h = hce(y->_v, finish);
					y->_f = y->_g + y->_h;
					y->_prev = x;
				}
			}else{
				A_node *new_node = new A_node(*it, tentative_g, hce(*it, finish), x);
				open_set.push_back(new_node);
			}
		}
	}
	std::list<Vector2d> empty;
	return empty;
}


//std::ofstream gOut("debug.txt");

//void debugPrintPath(const model::World& world, std::list<Vector2d>& path){
//	for (int j = 0; j < world.getHeight(); ++j){
//		for (int i = 0; i < world.getWidth(); ++i){
//			Vector2d t(i, j);
//			if (path.end() != std::find(path.begin(), path.end(), t))
//				gOut << '1';
//			else
//				gOut << '*';
//		}
//		gOut << '\n';
//	}
//
//	gOut << "\n\n";
//}
//
//void debugPrint(const model::World& world, std::list<A_node*>& closed_set, std::list<A_node*>& open_set){
//	for (int j = 0; j < world.getHeight(); ++j){
//		for (int i = 0; i < world.getWidth(); ++i){
//			Vector2d t(i, j);
//			if (NULL != getVinNodes(closed_set, t))
//				gOut << '1';
//			else if (NULL != getVinNodes(open_set, t))
//				gOut << '?';
//			else 
//				gOut << '*';
//
//		}
//		gOut << '\n';
//	}
//	
//	gOut << "\n\n";
//}