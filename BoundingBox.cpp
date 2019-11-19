#ifndef BOUNDINGBOX_H_INCLUDED
#include "BoundingBox.h"
#endif

BoundingBox::BoundingBox(std::vector<GraphicObject*> *go_p_container_p) : Box() {
    Vec3 temp_min_v = go_p_container_p->at(0)->GetMin(); // temporary values that might be the max and min 
    Vec3 temp_max_v = go_p_container_p->at(0)->GetMax(); // ...
	
    // if its more than 1 object in the container, go through the process. otherwise, just do a simple box
    if(go_p_container_p->size() > 1) {
		
    	// goes trough all of the objects, looking for the max/min of all the axis
		
        for(size_t i = 0; i < go_p_container_p->size(); i++) {			
            temp_min_v.x = Math::Min(go_p_container_p->at(i)->GetMin().x, temp_min_v.x);
            temp_min_v.y = Math::Min(go_p_container_p->at(i)->GetMin().y, temp_min_v.y);
            temp_min_v.z = Math::Min(go_p_container_p->at(i)->GetMin().z, temp_min_v.z);
            temp_max_v.x = Math::Max(go_p_container_p->at(i)->GetMax().x, temp_max_v.x);
            temp_max_v.y = Math::Max(go_p_container_p->at(i)->GetMax().y, temp_max_v.y);
            temp_max_v.z = Math::Max(go_p_container_p->at(i)->GetMax().z, temp_max_v.z);
        }
        
      /* _____
	 /     /|
	+-----+ |
	|  |  |
	| /   | / 
	X-----+/ <-- where the X is */
        
        // the position is set to be in the corner closest to origon when dealing with positive numbers (O)
        this->position_v = temp_min_v; 
        this->side_v = temp_max_v - temp_min_v;
	
        // *** FIND THE CENTER *** //
        // trying out two different techniques and use the best one
        // 1. n = 0 : splits up the axis and checks so atleast one object gets on the oppiste side
        // 2. n = 1 : take object 1 and 2 and a center between them and check along which axis a cut is suited
		
        Vec3 temp_center_v; // temporary center
        unsigned short int count_usi; // number of object on one side of the center
		
        for(unsigned short int n = 0; n < 2; ++n) { 
            switch(n) {
                case 0:
                    temp_center_v = this->side_v / 2.0f;
                    break;
                case 1:
                    temp_center_v = (go_p_container_p->at(0)->GetMid() + ((go_p_container_p->at(1)->GetMid() -
                    go_p_container_p->at(0)->GetMid())) / 2.0f) - this->position_v;
                    break;
                default:
                    break;	
            }
			
            if(temp_center_v != Vec3()) { // != 0
                for(unsigned short int i = 0; i < 3; ++i) { // runs through the different axis from x-z
                    count_usi = 0;

                    for(size_t j = 0; j < go_p_container_p->size(); ++j) {
						
                        switch(i) {
                            case 0:
                                this->center_v.x = temp_center_v.x;
                                break;
								
                            case 1:
                                this->center_v.y = temp_center_v.y;
                                break;
								
                            case 2:
                                this->center_v.z = temp_center_v.z;
                                break;
								
                            default:
                                break;
                        }
                            
                        // collects all the objects the is on one of the sides of temp-center
                        count_usi += this->GetSideOfCenter(go_p_container_p->at(j)); 
                    }
					
                    // nothing on that side, or everything. both are useless
                    if((count_usi == 0) || (count_usi == go_p_container_p->size())) { 
                        this->center_v = Vec3(); // = 0,0,0 == go back from the beginning
                    } else break;
                }
            }
            // if we have a center, break and go on... 
            if(this->center_v != Vec3()) break; 
        }
		
    } else { 
        // creates a box around a object, but no center
        this->position_v = temp_min_v;
        this->side_v = temp_max_v - temp_min_v;
    }
	
    this->size_usi = go_p_container_p->size(); // for printing out. makes it easier to control that everything worked out
}

BoundingBox::~BoundingBox() {}

bool BoundingBox::GetSideOfCenter(GraphicObject *go_p) {
    if(this->center_v != Vec3()) {		
        if(go_p->GetMid() < (this->position_v + (this->side_v - this->center_v))) { // left of center			
            return true;
			
        } else return false; // right of center
		
    } else return false; // empty vector
}

bool BoundingBox::Intersect(const Ray &view_ray, float &distance_f) { 
    float t_near_f = 0.0f, t0_f, t1_f;
    float t_far_f = std::numeric_limits<float>::infinity();
	
    for(int i = 0; i < 3; ++i) {	
        switch(i) {
            case 0: // X
                if(view_ray.GetDirection().x == 0) { 
                    if((view_ray.GetPosition().x < this->GetMin().x) || (view_ray.GetPosition().x > this->GetMax().x)) 
                        return false; // way off
                } else {
                    t0_f = (this->GetMin().x - view_ray.GetPosition().x) / view_ray.GetDirection().x; // the first position for x, 
                    t1_f = (this->GetMax().x - view_ray.GetPosition().x) / view_ray.GetDirection().x; // second... 
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
	
    return true;
}

void BoundingBox::Print() const {
    printf("\nBoundingBox - %d: \n", this->size_usi);
	
    this->position_v.Print();
    this->side_v.Print();
    this->center_v.Print();
}
