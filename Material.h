#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#ifndef COLOR_H_INCLUDED
#include "ColorRGB.h"
#endif

class Material {
    private:
        ColorRGB diffuse_c, specular_c;
        float reflection_f;
        unsigned short int power_usi;
    //
    public:
        Material();
        Material(const ColorRGB &diffuse, const ColorRGB &specular, const float &reflection, const unsigned short int &power);
        ~Material();
		
        ColorRGB GetDiffuse() const;
        ColorRGB GetSpecular() const;
        float GetReflection() const;
        unsigned short int GetPower() const;
    //
};

#endif


inline ColorRGB Material::GetDiffuse() const {
    return this->diffuse_c;
}

inline ColorRGB Material::GetSpecular() const {
    return this->specular_c;
}

inline float Material::GetReflection() const {
    return this->reflection_f;
}

inline unsigned short int Material::GetPower() const {
    return this->power_usi;
}
