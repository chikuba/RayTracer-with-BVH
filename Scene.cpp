#ifndef SCENE_H_INCLUDED
#include "Scene.h"
#endif

Scene::Scene() {
	this->bvh_p    	   = new BoundingVolumeHierarchy();
	this->width_usi    = 800;
	this->height_usi   = 600;
	this->orthogonal_b = false;
	this->fov_f		   = 90.0f;
}

Scene::Scene(const unsigned short int &width, const unsigned short int &height, const bool &orthogonal, const float &fov) {
	this->bvh_p 	   = new BoundingVolumeHierarchy();
	this->width_usi    = width;
	this->height_usi   = height;
	this->orthogonal_b = orthogonal;
	this->fov_f 	   = fov;
}

Scene::~Scene() {}

void Scene::AddGraphicsFromFile(const char* file_name_cp) {
	FILE *file;
	
    if((file = fopen(file_name_cp, "r")) != NULL) {
		
    	float temp_x, temp_y, temp_z, temp_r;
		
        while(fscanf(file, "%f%f%f%f*[^\n]",  &temp_x, &temp_y, &temp_z, &temp_r) != EOF) { // radius
            this->AddGraphic(new Sphere(Vec3((temp_x * 1000 + 400), 
											 (temp_z * 1000 + 400), 
											 (temp_y * 1000 + 600)), 
										(temp_r * 1500)));
        }
		
        fclose(file);
		
    } else puts("error");
}

void Scene::Build() {
	if(bvh_p->Build()) {
		
		bvh_p->PrintPostorder();
		bvh_p->PrintDepth();
		
		puts("done");
		
	} else puts("could'nt build");
}

ColorRGB Scene::ColorAtIntersection(Ray &view_ray) {
    ColorRGB output_color = ColorRGB(); 
    float coef_f = 0.7f; // level of reflection
    unsigned short int number_of_reflections_usi = 0;
    
	
	// bounce the light until the MAX_LEVEL is reached or if the object isnt reflective (anymore)
	// while ((coef_f > 0.0f) && (number_of_reflections_usi < MAX_LEVEL));  
	
    do { 
		
    	//*** OBJECT ***//
    	float distance_f = 2000.0f; // longest accepted distance 
    	GraphicObject *current_graphic_object_p = this->bvh_p->GetIntersection(view_ray, distance_f);
		
    	if(current_graphic_object_p == NULL) break;
    	
		
		
    	//*** NORMAL ***//
        Vec3 intersection_point_v = view_ray.GetPosition() + (view_ray.GetDirection() * distance_f);
        Vec3 go_normal_v = current_graphic_object_p->GetNormalAt(intersection_point_v);
		
        if(go_normal_v == Vec3()) break;
        
		
		
        //*** MATERIAL ***//
        Material current_material = current_graphic_object_p->GetMaterial();
		
		
		
		//*** LIGHTS ***//
		bool in_shadow = true;
		
		for(unsigned short int i = 0; i < this->light_p_container.size(); ++i) {
			
			Light *current_light_p = this->light_p_container.at(i);
			Vec3 light_distance_v = current_light_p->GetPosition() - intersection_point_v;
			float light_distance_f = light_distance_v * light_distance_v;
			
			if(light_distance_f == 0.0f) continue;
			
			
			float light_projection_f = light_distance_v * go_normal_v;
			
			if(light_projection_f <= 0.0f) continue;
			
			Ray light_ray = Ray(intersection_point_v, light_distance_v * Math::InvSqrt(light_distance_f));
			
			light_projection_f *= Math::InvSqrt(light_distance_f);
			
			
			
			//*** SHADOWS ***//
			if(this->bvh_p->GetIntersection(light_ray, light_distance_f) == NULL) {
				
				in_shadow = false;
				
				
				//*** LAMBERT ***//
				float lambert_f = (light_ray.GetDirection() * go_normal_v) * coef_f;
				output_color += current_light_p->GetIntensity() * current_material.GetDiffuse() * lambert_f;
				
				
				//*** BLINN ***//
				Vec3 blinn_direction_v = light_ray.GetDirection() - view_ray.GetDirection();
				float temp_f = Math::Sqrt(blinn_direction_v * blinn_direction_v);
				
				
				if((temp_f != 0.0f) && (current_material.GetSpecular() != ColorRGB())) {
					
					blinn_direction_v = blinn_direction_v / temp_f;
					
					float blinn_f = Math::Max((blinn_direction_v * go_normal_v), 0.0f);
					
					blinn_f = coef_f * Math::Pow(blinn_f, current_material.GetPower());
					output_color += current_material.GetSpecular() * current_light_p->GetIntensity() * blinn_f;
					
				} 
				
			} else continue;
		}
		
		// VISIBLE OBJECTS //
		if(!in_shadow) {
			
			//*** REFLECTION ***//
			if(current_material.GetReflection() == 0.0f) break;
			
			coef_f *= current_material.GetReflection();
			float refl_f = (view_ray.GetDirection() * go_normal_v) * 2.0f;
			view_ray = Ray(intersection_point_v, view_ray.GetDirection() - (go_normal_v * refl_f));
			
			++number_of_reflections_usi;
			
		} else break;
		
    } while ((coef_f > 0.0f) && (number_of_reflections_usi < MAX_LEVEL));  
	
    return output_color;
}

void Scene::Print(const char *file_name_cp) {
	std::ofstream imageFile(file_name_cp, std::ios_base::binary);
	float projection_distance_f = (0.5f * this->width_usi) / Math::Tan(0.5f * this->fov_f);
    
    if(imageFile) {
		
		//*** TGA header ***//
    	imageFile.put(0).put(0);
		imageFile.put(2); // RGB not compressed
		imageFile.put(0).put(0);
		imageFile.put(0).put(0);
		imageFile.put(0);
		imageFile.put(0).put(0); // origin X 
		imageFile.put(0).put(0); // origin Y 
		imageFile.put((unsigned char)(this->width_usi & 0x00FF)).put((unsigned char)((this->width_usi & 0xFF00) / 256));
		imageFile.put((unsigned char)(this->height_usi & 0x00FF)).put((unsigned char)((this->height_usi & 0xFF00) / 256));
		imageFile.put(24); // 24 bit bitmap 
		imageFile.put(0); 
		
		ColorRGB output_color;
		
		for(unsigned short int y = 0; y < this->height_usi; ++y) 
		for(unsigned short int x = 0; x < this->width_usi;  ++x) {
			
			output_color = ColorRGB(); // empty
			
			ColorRGB temp_color;
			
			for(float fx = float(x); fx < (x + 1.0f); fx += 0.5f) 
			for(float fy = float(y); fy < (y + 1.0f); fy += 0.5f) {
				
				temp_color = ColorRGB();
				
				
				//*** ORTHOGONAL VIEW ***//
				if(this->orthogonal_b) { 
					
					Ray view_ray = Ray(Vec3(fx, fy, -10000.0f), Vec3(0.0f, 0.0f, 1.0f));
					temp_color += this->ColorAtIntersection(view_ray);
				
					
				//*** PERSPECTIVE VIEW ***//
				} else { 
					Vec3 direction_v = Vec3(((fx - (0.5f * this->width_usi)) / projection_distance_f), 
											((fy - (0.5f * this->height_usi)) / projection_distance_f), 1.0f); 
					

					float direction_normal_f = direction_v * direction_v;
					
					if(direction_normal_f == 0.0f) break;
					
					Ray view_ray = Ray(Vec3((0.5f * this->width_usi), 
											(0.5f * this->height_usi), 0.0f), 
									   (direction_v * Math::InvSqrt(direction_normal_f)));
					
					temp_color += this->ColorAtIntersection(view_ray);
				}
				
				output_color += temp_color;
			}
			
			output_color.Control();
			
			imageFile.put((unsigned char)(output_color.blue_f * 255.0f))
					 .put((unsigned char)(output_color.green_f * 255.0f))
					 .put((unsigned char)(output_color.red_f * 255.0f));
		}
		
		puts("done");
    }
}
