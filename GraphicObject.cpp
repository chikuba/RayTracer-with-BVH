#ifndef GraphicOBJECT_H_INCLUDED
#include "GraphicObject.h"
#endif

GraphicObject::GraphicObject() {
    this->position_v = Vec3();
    this->side_v     = Vec3();
    this->shader_m   = Material();
}

GraphicObject::GraphicObject(const Vec3 &position, const Vec3 &side) {
    this->position_v = position;
    this->side_v 	 = side;
    this->shader_m 	 = Material();
}

GraphicObject::GraphicObject(const Vec3 &position, const Vec3 &side, const Material &shader) {
    this->position_v = position;
    this->side_v 	 = side;
    this->shader_m   = shader;
}

GraphicObject::~GraphicObject() {}

Material GraphicObject::GetMaterial() const {
    return this->shader_m;
}

void GraphicObject::Print() const {
    printf("\nGraphic Object");
}
