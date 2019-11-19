#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#ifndef GRAPHICOBJECT_H_INCLUDED
#include "GraphicObject.h"
#endif

class Sphere : public GraphicObject {
    public:
        Sphere();
        Sphere(const Vec3 &position, const float &radie);
        Sphere(const Vec3 &position, const float &radie, const Material &shader);
        ~Sphere();
		
        Vec3 GetMin();
        Vec3 GetMid();
        Vec3 GetMax();
        Vec3 GetNormalAt(Vec3 &intersection_point_v);
		
        bool GetSideOfCenter(GraphicObject *go_p);
        bool Intersect(const Ray &view_ray, float &distance_f);
		
        unsigned short int Type() const;
        void Print() const;
    //
};

#endif

inline Vec3 Sphere::GetMin() {
    return (this->position_v - this->side_v);
}

inline Vec3 Sphere::GetMid() {
    return this->position_v;
}

inline Vec3 Sphere::GetMax() {
    return (this->position_v + this->side_v);
}

inline bool Sphere::GetSideOfCenter(GraphicObject *go_p) { 
    return false; 
}

inline unsigned short int Sphere::Type() const { 
    return 1; 
}



