#ifndef RAY_H_INCLUDED
#include "Ray.h"
#endif

Ray::Ray() {
    this->position_v  = Vec3();
    this->direction_v = Vec3(0.0f, 0.0f, 1.0f);
}

Ray::Ray(const Vec3 &position, const Vec3 &direction) {
    this->position_v  = position;
    this->direction_v = direction;
}

Ray::~Ray() {}

