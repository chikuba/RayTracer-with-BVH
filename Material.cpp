#ifndef MATERIAL_H_INCLUDED
#include "Material.h"
#endif

Material::Material() {
    this->diffuse_c    = ColorRGB(0.3f, 0.3f, 1.0f);
    this->specular_c   = ColorRGB(1.0f, 1.0f, 1.0f);
    this->reflection_f = 0.7f;
    this->power_usi    = 60;
}

Material::Material(const ColorRGB &diffuse, const ColorRGB &specular, const float &reflection, const unsigned short int &power) {
    this->diffuse_c    = diffuse;
    this->specular_c   = specular;
    this->reflection_f = reflection;
    this->power_usi    = power;
}

Material::~Material() {}
