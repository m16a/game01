#pragma once

#include "math.h"

class Vector2d{
		int m_x;
		int m_y;
	public:
		Vector2d(int x, int y):m_x(x), m_y(y){};
		Vector2d(const Vector2d& v): m_x(v.m_x), m_y(v.m_y){};
		inline int x()const {return m_x;} 
		inline int y() const {return m_y;} 
		inline void setX(int x){m_x = x;}
		inline void setY(int y){m_y = y;}

		bool operator==(const Vector2d& rhs) const {
			return this->m_x == rhs.m_x && this->m_y == rhs.m_y; 
		}


};


inline float dist(const Vector2d& v1, const Vector2d& v2){
	return sqrt(float((v1.x() - v2.x())*(v1.x() - v2.x()) + (v1.y() - v2.y())*(v1.y() - v2.y())));
}