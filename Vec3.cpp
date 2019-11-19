#ifndef VECTOR_H_INCLUDED
#include "Vec3.h"
#endif

Vec3::Vec3() {
    this->x =
    this->y =
    this->z = 0.0f;
}

Vec3::Vec3(const float &x, const float &y, const float &z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3::~Vec3() {}

Vec3 Vec3::operator=(const Vec3 &v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
	
    return *this;
}

Vec3 Vec3::operator+(const Vec3 &v) {
    Vec3 temp(*this);
	
    temp.x += v.x;
    temp.y += v.y;
    temp.z += v.z;
	
    return temp;
}

Vec3 Vec3::operator-(const Vec3 &v) {
    Vec3 temp(*this);
	
    temp.x -= v.x;
    temp.y -= v.y;
    temp.z -= v.z;
	
    return temp;
}

Vec3 Vec3::operator/(const float &f) {
    Vec3 temp(*this);
	
    temp.x /= f;
    temp.y /= f;
    temp.z /= f;
	
    return temp;
}

Vec3 Vec3::operator/(const Vec3 &v) {
    Vec3 temp(*this);
	
    temp.x /= v.x;
    temp.y /= v.y;
    temp.z /= v.z;
	
    return temp;
}

Vec3 Vec3::operator*(const float &f) {
    Vec3 temp(*this);
	
    temp.x *= f;
    temp.y *= f;
    temp.z *= f;
	
    return temp;
}

float Vec3::operator*(const Vec3 &v) {
    return ((this->x * v.x) + (this->y * v.y) + (this->z * v.z));
}

bool Vec3::operator>(const Vec3 &v) const {
    if((this->x > v.x) && (this->y > v.y) && (this->z > v.z)) { 
        return true;
		
    } else return false;
}

bool Vec3::operator<(const Vec3 &v) const {
    if((this->x < v.x) && (this->y < v.y) && (this->z < v.z)) { 
        return true;
		
    } else return false;
}

bool Vec3::operator>=(const Vec3 &v) const {
    if((this->x >= v.x) && (this->y >= v.y) && (this->z >= v.z)) {
        return true;
		
    } else return false;
}

bool Vec3::operator<=(const Vec3 &v) const {
    if((this->x <= v.x) && (this->y <= v.y) && (this->z <= v.z)) {
        return true;
		
    } else return false;
}

bool Vec3::operator==(const Vec3 &v) const {
    if((this->x == v.x) && (this->y == v.y) && (this->z == v.z)) {
        return true;
		
    } else return false;
}

bool Vec3::operator!=(const Vec3 &v) const {
    if((this->x != v.x) || (this->y != v.y) || (this->z != v.z)) {
        return true;
		
    } else return false;
}

Vec3 Vec3::Normalize() const {
    Vec3 temp(*this);
	
    temp = temp / temp.Length();
	
    return temp;
}

float Vec3::Length() const {
    return Math::Sqrt(Math::Pow(this->x, 2) + Math::Pow(this->y, 2) + Math::Pow(this->z, 2));
}

void Vec3::Print() const {
    printf("Vec3(%.2f, %.2f, %.2f)\n", this->x, this->y, this->z);
}
