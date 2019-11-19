#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#include <math.h>

#define pi 3.14159265

class Math {
    public:
        static float Tan(const float &a);
        static float Sqrt(const float &a);
        static float InvSqrt(const float &a);
        static float Pow(const float &a,  const unsigned short int &b);
        static float Abs(const float &a);
        static float Sign(const float &a);
		
        static float Max(const float &a, const float &b);
        static float Min(const float &a, const float &b);
        static void Swap(float &a, float &b);
    //
};

#endif

inline float Math::Tan(const float &a) { 
    return tan((a * pi) / 180); 
}

inline float Math::Sqrt(const float &a) { 
    return sqrt(a); 
}

inline float Math::InvSqrt(const float &a) {
    return (1.0f / sqrt(a));
}

inline float Math::Pow(const float &a, const unsigned short int &b) { 
    return pow(a, float(b)); 
}

inline float Math::Abs(const float &a) {
    return fabsf(a);
}

inline float Math::Sign(const float &a) {
    return (a / fabsf(a));
}

inline float Math::Max(const float &a, const float &b) {
    return (a > b ? a : b);
}

inline float Math::Min(const float &a, const float &b) {
    return (a < b ? a : b);
}

inline void Math::Swap(float &a, float &b) {
    float temp = a;
    a = b;
    b = temp;
}
