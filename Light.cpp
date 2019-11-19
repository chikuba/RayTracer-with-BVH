#ifndef LIGHT_H_INCLUDED
#include "Light.h"
#endif

Light::Light() {
    this->position_v  = Vec3(1.0f, 1.0f, 1.0f);
    this->intensity_c = ColorRGB(150.0f, 0.0f, 0.0f);
}

Light::Light(const Vec3 &position, const ColorRGB &intensity) {
    this->position_v  = position;
    this->intensity_c = intensity;
}

Light::~Light() {}


