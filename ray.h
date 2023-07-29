#ifndef RAY_h
#define RAY_H

#include "vec3.h"

class ray {
public:
    ray() {}
    ray(const vec3& origin, const vec3& direction) : orig(origin), dir(direction) { dir = unit_vector(dir); } 

    vec3 origin() const { return orig; }
    vec3 direction() const {return dir; }

    vec3 at(double t) const {
	return orig + t*dir;
    }

public:
    vec3 orig;
    vec3 dir;
};
#endif
