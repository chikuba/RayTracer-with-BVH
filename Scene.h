#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#ifndef BVH_H_INCLUDED
#include "BoundingVolumeHierarchy.h"
#endif

#ifndef RAY_H_INCLUDED
#include "Ray.h"
#endif

#ifndef LIGHT_H_INCLUDED
#include "Light.h"
#endif

#include <fstream>

#define MAX_LEVEL 3 // maximum : number of times each ray bounces (for reflection purposes)

class Scene {
    private:
		BoundingVolumeHierarchy *bvh_p;
		std::vector<Light*> light_p_container;
		unsigned short int width_usi, height_usi;
		bool orthogonal_b; // if the view is ortogonal or perspective
		float fov_f; // field of view
	//
	public:
		Scene();
		Scene(const unsigned short int &width, const unsigned short int &height, const bool &orthogonal, const float &fov);
		~Scene();
		
		void ChangePerspective();
		void AddGraphic(GraphicObject *new_graphic_object_p);
		void AddGraphicsFromFile(const char *file_name_cp);
		void AddLight(Light *new_light_p);
		
		void Build();
		ColorRGB ColorAtIntersection(Ray &view_ray);
		void Print(const char *file_name_cp);
	//
};

#endif

inline void Scene::ChangePerspective() {
	this->orthogonal_b ^= true; // XOR 
}

inline void Scene::AddGraphic(GraphicObject *new_graphic_object_p) {
	if(!bvh_p->Add(new_graphic_object_p)) {
		puts("error : couldnt add object to bounding volume hierarchy. ");
	}
}

inline void Scene::AddLight(Light *new_light_p) {
	light_p_container.push_back(new_light_p);
}




