#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#ifndef VEC3_H_INCLUDED
#include "Vec3.h"
#endif

class Ray {
    private:
        Vec3 position_v, direction_v;
    //
    public:
        Ray();
        Ray(const Vec3 &position, const Vec3 &direction);
        ~Ray();
		
        Vec3 GetPosition() const;
        void SetPosition(const Vec3 &new_position);
	
        Vec3 GetDirection() const;
        void SetDirection(const Vec3 &new_direction);
    //
};

#endif

inline Vec3 Ray::GetPosition() const {
    return this->position_v;
}

inline void Ray::SetPosition(const Vec3 &new_position) {
    this->position_v = new_position;
}

inline Vec3 Ray::GetDirection() const {
    return this->direction_v;
}

inline void Ray::SetDirection(const Vec3 &new_direction) {
    this->direction_v = new_direction;
}
