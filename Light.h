#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#ifndef VEC3_H_INCLUDED
#include "Vec3.h"
#endif

#ifndef COLOR_H_INCLUDED
#include "ColorRGB.h"
#endif

class Light {
    private:
        Vec3 position_v;
        ColorRGB intensity_c;
    //
    public:
        Light();
        Light(const Vec3 &position, const ColorRGB &intensity);
        ~Light();
		
        Vec3 GetPosition() const;
        ColorRGB GetIntensity() const;
    //
};

#endif

inline Vec3 Light::GetPosition() const {
    return this->position_v;
}

inline ColorRGB Light::GetIntensity() const {
    return this->intensity_c;
}
