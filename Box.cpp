#ifndef BOX_H_INCLUDED
#include "Box.h"
#endif

Box::Box() : GraphicObject() {}

Box::Box(const Vec3 &position, const Vec3& side) : GraphicObject(position, side) {}

Box::Box(const Vec3& position, const float& side) : GraphicObject(position, Vec3(side, side, side)) {}

Box::Box(const Vec3& position, const Vec3& side, const Material& shader) : GraphicObject(position, side, shader) {}

Box::~Box() {}

// no fuzz here. just a straight normal that is ortogonal with the CLOSEST intersected plane
Vec3 Box::GetNormalAt(Vec3 &intersection_point_v) { 
    Vec3 normal = Vec3();
    float min = std::numeric_limits<float>::max();
    intersection_point_v = intersection_point_v - this->GetMid();
	
    // X //
    float distance = Math::Abs((this->GetMax().x - this->GetMin().x) - Math::Abs(intersection_point_v.x));
	
    // stepping through the different planes, looking for the first one that the ray is intersecting
    if(distance < min) {
        min = distance;
        normal = Vec3(1.0f, 0.0f, 0.0f) * Math::Sign(intersection_point_v.x);
    }
	
    // Y //
    distance = Math::Abs((this->GetMax().y - this->GetMin().y) - Math::Abs(intersection_point_v.y));
	
    if(distance < min) {
        min = distance;
        normal = Vec3(0.0f, 1.0f, 0.0f) * Math::Sign(intersection_point_v.y);
    }
	
    // Z //
    distance = Math::Abs((this->GetMax().z - this->GetMin().z) - Math::Abs(intersection_point_v.z));
	
    if(distance < min) {
        min = distance;
        normal = Vec3(0.0f, 0.0f, 1.0f) * Math::Sign(intersection_point_v.z);
    }
	
    return normal.Normalize();
}

// see bbox intersection for explantion 
bool Box::Intersect(const Ray &view_ray, float &distance_f) { 
    float t_near_f = 0.0f, t0_f, t1_f;
    float t_far_f = std::numeric_limits<float>::infinity();
	
    for(int i = 0; i < 3; i++) {
        switch(i) {
            case 0: // X
                if(view_ray.GetDirection().x == 0) {
                    if((view_ray.GetPosition().x < this->GetMin().x) || (view_ray.GetPosition().x > this->GetMax().x)) 
                        return false;
                } else {
                    t0_f = (this->GetMin().x - view_ray.GetPosition().x) / view_ray.GetDirection().x;
                    t1_f = (this->GetMax().x - view_ray.GetPosition().x) / view_ray.GetDirection().x;
                }
                break;
				
            case 1: // Y
                if(view_ray.GetDirection().y == 0) {
                    if((view_ray.GetPosition().y < this->GetMin().y) || (view_ray.GetPosition().y > this->GetMax().y)) 
                        return false;
                } else {
                    t0_f = (this->GetMin().y - view_ray.GetPosition().y) / view_ray.GetDirection().y;
                    t1_f = (this->GetMax().y - view_ray.GetPosition().y) / view_ray.GetDirection().y;
                }
                break;
				
            case 2: // Z
                if(view_ray.GetDirection().z == 0) {
                    if((view_ray.GetPosition().z < this->GetMin().z) || (view_ray.GetPosition().z > this->GetMax().z)) 
                        return false;
                } else {
                    t0_f = (this->GetMin().z - view_ray.GetPosition().z) / view_ray.GetDirection().z;
                    t1_f = (this->GetMax().z - view_ray.GetPosition().z) / view_ray.GetDirection().z;
                }
                break;
				
            default:
                break;
        }
		
        // setting up the planes 
		
        if(t0_f > t1_f) 
            Math::Swap(t0_f, t1_f);
		
        t_near_f = Math::Max(t_near_f, t0_f);
        t_far_f = Math::Min(t1_f, t_far_f);
		
        // out of range, but the set-up is correct
        if((t_near_f > t_far_f) || (t_far_f < 0.0f)) 
            return false;
    }
	
    // the distans to the intersection, for shading purposes
    if(t_near_f <= distance_f) {
        distance_f = t_near_f;		
        return true;
		
    } else return false;
}

void Box::Print() const {
    printf("\nBox: \n");
	
    this->position_v.Print();
    this->side_v.Print();
}
