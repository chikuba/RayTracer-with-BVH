#ifndef GraphicOBJECT_H_INCLUDED
#define GraphicOBJECT_H_INCLUDED

#ifndef MATERIAL_H_INCLUDED
#include "Material.h"
#endif

#ifndef RAY_H_INCLUDED
#include "Ray.h"
#endif

/* This is the base class that bbox, box and sphere inherits most of its attributes from*/

class GraphicObject {
    protected:
        Vec3 position_v, side_v;
        Material shader_m;
    //
    public:
        GraphicObject();
        GraphicObject(const Vec3 &position, const Vec3 &side);
        GraphicObject(const Vec3 &position, const Vec3 &side, const Material &shader);
        virtual ~GraphicObject();
		
        virtual Vec3 GetMin() = 0;
        virtual Vec3 GetMid() = 0;
        virtual Vec3 GetMax() = 0;
        virtual Vec3 GetNormalAt(Vec3 &intersection_point) = 0;
		
        Material GetMaterial() const;
	
        virtual bool GetSideOfCenter(GraphicObject *go_p) { return false; }
        virtual bool Intersect(const Ray &view_ray, float &distance_t) { return false; }
        virtual unsigned short int Type() const { return 0; }
        virtual void Print() const;
    //
};

#endif
