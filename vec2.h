// linalg.h


#ifndef LINALG_H
#define LINALG_H


#include <iostream>
#include <math.h>

#ifdef _WIN32
  #pragma warning(disable : 4244 4305 4996)
#endif


// ---------------- vec2 ----------------

class vec2 {
public:
	float x,y;
	vec2() {}
	vec2(float xx, float yy) : x(xx), y(yy) {}

	bool operator == (const vec2 p){
		return x == p.x &&  y== p.y;
	}

	bool operator != (const vec2 p){
		return x != p.x || y != p.y;
	}

	vec2 operator + (const vec2 p) {
		return vec2(x+p.x, y+p.y);
	}

	vec2 operator - (const vec2 p) {	
		return vec2(x-p.x, y-p.y);
	}

		vec2 operator * (const float t) {
		return vec2(x*t, y*t);
	}

	float operator ^ (const vec2 p) {	/* dot product */
		return x*p.x + y*p.y;
	}

	vec2 normalize() {
		float length = sqrt(x*x + y*y);
		return vec2(this->x/length, this->y/length);
	}

	float length() {
		return sqrt(x*x + y*y);
	}


};
#endif
