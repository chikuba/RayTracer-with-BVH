#ifndef BVH_H_INCLUDED
#define BVH_H_INCLUDED

#ifndef SPHERE_H_INCLUDED
#include "Sphere.h"
#endif

#ifndef BOUNDINGBOX_H_INCLUDED
#include "BoundingBox.h"
#endif


/*
This is a simple tree-structure that might look like this:

	+----------------------------+
	|         |                  |
	+----------------------------+
	   ||                ||
	   \/                \/
	+-----+        +-----------+
    |  |  |        |     |     |
	+-----+        +-----------+
	 |   |           |      | 
	 O   O           O      O

First we create a bouding box around all of the objects. Then in a recurive matter
work ourself down to the leafs by splitting the bboxes in half, and the objects in it in
two piles. We then build a new box around the 2 new piles. This procedure comes to a 
halt when all the objects are alone, aka leaf-nodes. 

The user must first add the objects, then start bulding it. 

When intersecting it with a ray, it works down the tree by first check if it 
even hit the root-bbox. If it did, on which side of the center does it hit?
Continue on in like this until we find the leaf that is first hit by the ray.
*/

class BoundingVolumeHierarchy {
    private:
        struct NODE {
            NODE *left;
            NODE *right;
            GraphicObject *data;
        };
        NODE *root;
        std::vector<GraphicObject*> go_p_container;
	//
    public:
        BoundingVolumeHierarchy();
        ~BoundingVolumeHierarchy();
		
        bool Add(GraphicObject *go_p);
        bool Build();
        void Building(std::vector<GraphicObject*> *part_p_container_p);
        
        void InsertNode(GraphicObject *go_p);
        GraphicObject* GetIntersectionList(const Ray &view_ray, float &distance_f);
        GraphicObject* GetIntersection(const Ray &view_ray, float &distance_f);
        BoundingVolumeHierarchy::NODE* SearchForClosestObject(NODE *node_p, const Ray &view_ray, float &distance_f);
		
        void Preorder(NODE *node_p) const;
        void PrintPreorder();
        void Inorder(NODE *node_p) const;
        void PrintInorder();
        void Postorder(NODE *node_p) const;
        void PrintPostorder();
	
        unsigned short int GetDepth(NODE *node_p) const;
        void PrintDepth();
        
        bool IsEmpty() const;
        //
};

#endif

inline void BoundingVolumeHierarchy::PrintPreorder() {
    this->Preorder(this->root);
}

inline void BoundingVolumeHierarchy::PrintInorder() {
    this->Inorder(this->root);
}

inline void BoundingVolumeHierarchy::PrintPostorder() {
    this->Postorder(this->root);
}

inline void BoundingVolumeHierarchy::PrintDepth() {
    printf("\nDepth: %d \n", this->GetDepth(this->root));
}

inline bool BoundingVolumeHierarchy::IsEmpty() const { 
    return (this->root == NULL); 
}




