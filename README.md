RayTracer with BVH
==================

A RayTracer I made years ago (2009 ish) from scratch. It uses BVH to speed things up (even though it's quite slow).

Just add the files to an XCode project or compile it in the terminal. When you have the executable, just run: 

$ ./RayTracer allteapot.txt

...and wait. 

It will first build the hierarchy and then start generating the image. This might take a while. (a few minutes or so). 

# Making your own file and other changes

If you want to create your own .txt-file, just create rows that follows these guidelines: 

x, y, z, radius

For every row, there will a sphere. You can redo the code so that you can draw boxes instead. Do this in Scene.cpp:

    void Scene::AddGraphicsFromFile(const char* file_name_cp) {
        FILE *file;
        
        if((file = fopen(file_name_cp, "r")) != NULL) {
            
            float temp_x, temp_y, temp_z, temp_r;
            
            while(fscanf(file, "%f%f%f%f*[^\n]",  &temp_x, &temp_y, &temp_z, &temp_r) != EOF) { 
                this->AddGraphic(new Sphere(Vec3((temp_x * 1000 + 400), // <<-- Type "new Box" instead
                                                 (temp_z * 1000 + 400), 
                                                 (temp_y * 1000 + 600)), 
                                            (temp_r * 1500)));
            }
            
            fclose(file);
            
        } else puts("error");
    }

# DISCLAIMER 
This is my very first C++ program. Written 2009. 
 
