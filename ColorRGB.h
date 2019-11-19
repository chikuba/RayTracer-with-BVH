#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#ifndef MATH_H_INCLUDED
#include "Math.h"
#endif

class ColorRGB {
    public:
        float red_f, green_f, blue_f;
		
        ColorRGB();
        ColorRGB(const float &red, const float &green, const float &blue);
        ~ColorRGB();
		
        ColorRGB operator+=(const ColorRGB &color);
        bool operator!=(const ColorRGB &color) const;
        ColorRGB operator*(const ColorRGB &color);
        ColorRGB operator*(const float &f);
		
        void Control();
	
        float Encode(const float &color) const;
    //
};

#endif

inline float ColorRGB::Encode(const float &color) const { 
    return Math::Pow(color, 2); 
}

