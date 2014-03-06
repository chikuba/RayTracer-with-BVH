#ifndef BVH_H_INCLUDED
#include "BoundingVolumeHierarchy.h"
#endif

BoundingVolumeHierarchy::BoundingVolumeHierarchy() {
    this->root = NULL;
}

BoundingVolumeHierarchy::~BoundingVolumeHierarchy() {
	delete this->root;
}

bool BoundingVolumeHierarchy::Add(GraphicObject *go_p) {
	// prevents from adding an object at the same location as another object. 
    for(size_t i = 0; i < go_p_container.size(); i++) { 
        
		if(go_p->GetMid() == go_p_container.at(i)->GetMid()) {
			
        	if((go_p->GetMax() - go_p->GetMin()) > (go_p_container.at(i)->GetMax() - go_p_container.at(i)->GetMin())) {
        		go_p_container.at(i) = go_p;
				
        		return true;
				
        	} else return false;
        }
    }
	
    go_p_container.push_back(go_p); // adds all the objects to a vector first. 
    
    return true;
}

bool BoundingVolumeHierarchy::Build(void) {
    if(go_p_container.size() > 0) {
		
		this->Building(&go_p_container);
		
		return true;
		
    } else return false;
}

void BoundingVolumeHierarchy::Building(std::vector<GraphicObject*> *part_p_container_p) {
    std::vector<GraphicObject*> left_p_container, right_p_container; // we split the container in half. 
	
    if(part_p_container_p->size() == 1) {
		
        this->InsertNode(part_p_container_p->at(0)); // insert leaf-nodes
		
    } else {
		// sends a lift of object which you want to create a bbox around
    	BoundingBox *temp_p = new BoundingBox(part_p_container_p); 
		
		for(size_t i = 0; i < part_p_container_p->size(); i++) {
			
			// since the center is already created, we only need to devide the objects in to two containers
            if(temp_p->GetSideOfCenter(part_p_container_p->at(i))) { 
				
                left_p_container.push_back(part_p_container_p->at(i)); // left of center
				
            } else {
				// or right of center (there will be no objects that is on the center-line)
				right_p_container.push_back(part_p_container_p->at(i)); 
			}
        }
		
        this->InsertNode(temp_p); // we only insert the biggest suroinding bbox
        this->Building(&left_p_container);
        this->Building(&right_p_container); 
    }
}

void BoundingVolumeHierarchy::InsertNode(GraphicObject *go_p) {
    NODE *temp_p = new NODE;
    temp_p->data = go_p;
    temp_p->left = temp_p->right = NULL;
	
    NODE *parent_p = NULL;
	
    if(!this->IsEmpty()) {
		
        NODE *current_p = root;
		
		// stepping trough the tree for the right spot
        while(current_p) {
			
            parent_p = current_p;
			
            if(current_p->data->GetSideOfCenter(temp_p->data)) {
				
                current_p = current_p->left;
				
            } else current_p = current_p->right;
        }
		
		// adds a leaf
        if(parent_p->data->GetSideOfCenter(temp_p->data)) {
			
            parent_p->left = temp_p;
			
        } else parent_p->right = temp_p;
		
    } else this->root = temp_p;  // creates the root
}

// stepping trough all the objects and returns the closest object, since the distance_f will get smaller and smaller
// (just because we found an object before, we can still find one that is closer. The thing we cant do 
//  is to find objects that are farther away). 
GraphicObject* BoundingVolumeHierarchy::GetIntersectionList(const Ray &view_ray, float &distance_f) {
	int current = -1;
	
	for(unsigned int i = 0; i < go_p_container.size(); ++i) {
	
		if(go_p_container.at(i)->Intersect(view_ray, distance_f)) {
			
			current = i;
		}
	}
	
	if(current >= 0) { // means we found an object
		
		return go_p_container.at(current);
		
	} else return NULL;
}

GraphicObject* BoundingVolumeHierarchy::GetIntersection(const Ray &view_ray, float &distance_f) {
	NODE* temp_p = this->SearchForClosestObject(this->root, view_ray, distance_f);
	
	if(temp_p != NULL) {
		
		return temp_p->data;
		
	} else return NULL;
}

BoundingVolumeHierarchy::NODE* BoundingVolumeHierarchy::SearchForClosestObject(NODE *node_p, const Ray &view_ray, float &distance_f) {	
	if(node_p != NULL) {
		
		if(node_p->data->Intersect(view_ray, distance_f)) {
			
			if(node_p->data->Type() == 1) {
				
				return node_p;
				
			} else {
				NODE* right = this->SearchForClosestObject(node_p->right, view_ray, distance_f);
				NODE* left = this->SearchForClosestObject(node_p->left, view_ray, distance_f);
				
				if(left != NULL) return left;
				
				if(right != NULL) return right;
			}
			
		} else return NULL;
	} 
	
	return NULL;
}

void BoundingVolumeHierarchy::Preorder(NODE *node_p) const {
    if(node_p != NULL) {
		
        node_p->data->Print();
		
        if(node_p->left) this->Preorder(node_p->left);
		
        if(node_p->right) this->Preorder(node_p->right);
		
    } else return;
}

void BoundingVolumeHierarchy::Inorder(NODE *node_p) const {
    if(node_p != NULL) {
		
        if(node_p->left) this->Inorder(node_p->left);
		
        node_p->data->Print();
		
        if(node_p->right) this->Inorder(node_p->right);
		
    } else return;
}

void BoundingVolumeHierarchy::Postorder(NODE *node_p) const {
    if(node_p != NULL) {
		
        if(node_p->left) this->Postorder(node_p->left);
		
        if(node_p->right) this->Postorder(node_p->right);
		
        node_p->data->Print();
		
    } else return;
}

unsigned short int BoundingVolumeHierarchy::GetDepth(NODE *node_p) const {
    if(node_p != NULL) {
		
        int left_depth = this->GetDepth(node_p->left);
        int right_depth = this->GetDepth(node_p->right);
		
        if(left_depth > right_depth) {
			
            return (left_depth + 1);
			
        } else return (right_depth + 1);
		
    } else return 0;
}
