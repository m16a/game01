#include <list>
#include <algorithm>
#include "assert.h"
#include <string>

#include "PathFinder.h"
#include "GeomMisc.h"

PathFinder::PathFinder(void)
{
}

PathFinder::~PathFinder(void)
{
}


//Node for A* search
//f(x) = g(x) + h(x)
struct A_node{
	Vector2d _v;
	float _f,_g,_h;
	A_node* _prev;

	A_node(const Vector2d& v, float g = 0, float h = 0, A_node* prev = NULL):_v(v), _g(g), _h(h), _prev(prev){
		_f = _g +_h;
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


std::list<Vector2d> grabNeighbors(const model::World& w, const Vector2d& v){
	std::list<Vector2d> res;
	const std::vector<std::vector<model::CellType> >& cells = w.getCells();

	if (v.x()-1 >= 0 && model::FREE == cells[v.x()-1][v.y()])
		res.push_back(Vector2d(v.x()-1, v.y()));

	if (v.x()+1 < w.getWidth() && model::FREE == cells[v.x()+1][v.y()])
		res.push_back(Vector2d(v.x()+1, v.y()));

	if (v.y()-1 >= 0 && model::FREE == cells[v.x()][v.y()-1])
		res.push_back(Vector2d(v.x(), v.y()-1));

	if (v.y()+1 < w.getHeight() && model::FREE == cells[v.x()][v.y()+1])
		res.push_back(Vector2d(v.x(), v.y()+1));

	return res;
}

A_node* getVinNodes(std::list<A_node*>& set, const Vector2d& v){
	A_node* res = NULL;
	std::list<A_node*>::iterator tmp_it = set.begin();
	for(;tmp_it != set.end(); ++tmp_it){
		if (v == (*tmp_it)->_v)
			res = *tmp_it;
		break;
	}
	return res;
}


static bool deleteAll( A_node * theElement ) { delete theElement; return true; }

typedef float (*heuristic_cost_estimate)(const Vector2d& start, const Vector2d& finish);

std::list<Vector2d> PathFinder::calcOptimalPath(const model::World& world, const Vector2d& start, const Vector2d& finish){
	std::list<A_node*> closed_set;
	std::list<A_node*> open_set;

	heuristic_cost_estimate hce = dist;//let's choose the simplest heuristic - euclidean distance between two points

	A_node *start_node = new A_node(start, 0, hce(start, finish));
	open_set.push_back(start_node);

	while (!open_set.empty()){
		A_node* x = *min_element(open_set.begin(), open_set.end()); 

		if (x->_v == finish){
			std::list<Vector2d> res = reconstructPath(x);
			closed_set.remove_if(deleteAll);
			open_set.remove_if(deleteAll);
			return res;
		}

		closed_set.push_back(x);	
		open_set.remove(x);
		
		//grab neighbors for x
		std::list<Vector2d> neighbors = grabNeighbors(world, x->_v);
		std::list<Vector2d>::iterator it = neighbors.begin();

		for (;it != neighbors.end(); ++it){

			if (getVinNodes(closed_set, *it) != NULL)
				continue;

			float tentative_g = x->_g + dist(*it, x->_v);
			bool tentative_is_better = false;

			A_node* y = getVinNodes(open_set, *it);
			if (NULL != y){
				if (tentative_g < y->_g)
					y->_g = tentative_g;
					y->_h = hce(y->_v, finish);
					y->_f = y->_g + y->_h;
					y->_prev = x;
			}else{
				A_node *new_node = new A_node(*it, tentative_g, hce(*it, finish), x);
				open_set.push_back(new_node);
			}
		}
	}
	assert(0);
}