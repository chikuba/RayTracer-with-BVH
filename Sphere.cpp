#ifndef SPHERE_H_INCLUDED
#include "Sphere.h"
#endif

#include <limits>

Sphere::Sphere() : GraphicObject() {}

Sphere::Sphere(const Vec3 &position, const float &radie) : GraphicObject(position, Vec3(radie, radie, radie)) {}

Sphere::Sphere(const Vec3 &position, const float &radie, const Material &shader) : GraphicObject(position, Vec3(radie, radie, radie), shader) {}

Sphere::~Sphere() {}

Vec3 Sphere::GetNormalAt(Vec3 &intersection_point_v) {
    float temp_f = (intersection_point_v - this->position_v) * (intersection_point_v - this->position_v);
	
    if(temp_f != 0.0f) { 
        temp_f = Math::InvSqrt(temp_f); 
        return (intersection_point_v - this->position_v) * temp_f;
    } else return Vec3();
}

// a simple ray - sphere intersection by using the spheres center and radius
bool Sphere::Intersect(const Ray &view_ray, float &distance_f) { 
    Vec3 distans = view_ray.GetPosition() - this->position_v; 
    float b_f = distans *  view_ray.GetDirection();
    float c_f = (distans * distans) - (this->side_v.x * this->side_v.x);
    float d_f = (b_f * b_f) - c_f; 
	
    if(((c_f > 0.0f) && (b_f > 0.0f)) || (d_f < 0.0f)) return false; 
	
    float t0_f = -b_f - Math::Sqrt(d_f); 
	
    if(t0_f < 0.0f) return false;
	
    if(t0_f <= distance_f) {
        distance_f = t0_f; // the distans for shading purposes		
        return true;
		
    } else return false;
}

void Sphere::Print() const {
    printf("\nSphere: \n");
	
    this->position_v.Print();
    this->side_v.Print();
}
