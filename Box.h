#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED

#ifndef GRAPHICOBJECT_H_INCLUDED
#include "GraphicObject.h"
#endif

#include <limits>

class Box : public GraphicObject {
    public:
        Box();
        Box(const Vec3 &position, const Vec3 &side);
        Box(const Vec3 &position, const float &side);
        Box(const Vec3 &position, const Vec3 &side, const Material &shader);
        virtual ~Box();
		
        Vec3 GetMin();
        Vec3 GetMid();
        Vec3 GetMax();
        Vec3 GetNormalAt(Vec3 &intersection_point_v);
		
        virtual bool GetSideOfCenter(GraphicObject *go_p);
        virtual bool Intersect(const Ray &view_ray, float &distance_f);
		
        virtual unsigned short int Type() const;
        virtual void Print() const;
    //
};

#endif

inline Vec3 Box::GetMin() {
    return this->position_v;
}

inline Vec3 Box::GetMid() {
    return (this->position_v + (this->side_v / 2.0f));
}

inline Vec3 Box::GetMax() {
    return (this->position_v + this->side_v);
}

inline bool Box::GetSideOfCenter(GraphicObject *go_p) { 
    return false; 
}

inline unsigned short int Box::Type() const { 
    return 1; 
}

