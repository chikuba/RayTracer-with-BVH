#ifndef BOUNDINGBOX_H_INCLUDED
#define BOUNDINGBOX_H_INCLUDED

#ifndef BOX_H_INCLUDED
#include "Box.h"
#endif

#include <vector>

/* This is bounding box that is created by using a point(where the box begins) 
   _____
 /|    /|
+-----+ |
| |   | |
| /   | / 
X-----+/ <-- where the X is 

and the length of the sides. It also have one special feature and that is the center. 
This is used so when we later put theses boxes into in hierarchy of boxes 
and need to sort them in the following matter:

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

So when we are looking for the center, we need to be sure that the ratio of 
objects on either side is accurate so we get a nice tree-structure.
*/

class BoundingBox : public Box {
    private:
        Vec3 center_v;
        unsigned short int size_usi;
    //
    public:
        BoundingBox(std::vector<GraphicObject*> *go_p_container_p);
        ~BoundingBox();
		
        bool GetSideOfCenter(GraphicObject *go_p);
        bool Intersect(const Ray &view_ray, float &distance_f);
		
        unsigned short int Type() const;
        void Print() const;
    //
};

#endif

inline unsigned short int BoundingBox::Type() const { 
    return 2; 
}

