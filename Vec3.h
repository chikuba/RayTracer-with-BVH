#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#ifndef MATH_H_INCLUDED
#include "Math.h"
#endif

#include <stdio.h>
#include <stdlib.h>

class Vec3 {
    public:
        float x, y, z;
		
        Vec3();
        Vec3(const float &x, const float &y, const float &z);
        ~Vec3();
		
        Vec3 operator=(const Vec3 &v);
        Vec3 operator+(const Vec3 &v);
        Vec3 operator-(const Vec3 &v);
        Vec3 operator/(const float &f);
        Vec3 operator/(const Vec3 &v);
        Vec3 operator*(const float &f);
        float operator*(const Vec3 &v);
		
        bool operator>(const Vec3 &v) const;
        bool operator<(const Vec3 &v) const;
        bool operator>=(const Vec3 &v) const;
        bool operator<=(const Vec3 &v) const;
        bool operator==(const Vec3 &v) const;
        bool operator!=(const Vec3 &v) const;
		
        Vec3 Normalize() const;
        float Length() const;
        void Print() const;
    //
};

#endif
