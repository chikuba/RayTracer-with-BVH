#ifndef SCENE_H_INCLUDED
#include "Scene.h"
#endif

#include <time.h>

/** This is a basic ray tracer that use textfiles as input. It uses bounding volumes and a 
    tree hierarchy to store the objects. It can handle basic geometric shapes such as boxes 
    and spheres. 
 
    It can calculate reflections, shadows, blinn and lambert. Refractions are still
    something to be wished for and will be implemented in the next edition. 
 
    The ray tracer are not real time and it renders the image pixel per pixel as
    an uncompressed .tga-file (24 bit RGB). 

**/


int main (int argc, char * const argv[]) {
	clock_t start1, end1, start2, end2;
    Scene *scene = new Scene();
    
    if(argc <= 1) {
		
		fprintf(stderr, "No source file specified. (You need to specify a .txt-file.)\n");		
		
    } else {
		scene->AddGraphicsFromFile(argv[1]);
		scene->AddLight(new Light(Vec3(100.0f, 0.0f, -10000.0f), ColorRGB(0.6f, 0.2f, 0.0f)));
		scene->AddLight(new Light(Vec3(700.0f, 200.0f, -1000.0f), ColorRGB(0.2f, 0.3f, 0.1f)));
		scene->AddLight(new Light(Vec3(640.0f, 0.0f, 10000.0f), ColorRGB(0.1f, 0.3f, 0.4f)));
		
		start1 = clock();
		scene->Build();
		end1 = clock();
		printf("\nBuild time: %.4f sec\n", (double)(end1 - start1) / CLOCKS_PER_SEC);
		
		start2 = clock();
		scene->Print("./finalpicture.tga");
		end2 = clock();
		printf("\nPrint time: %.4f sec\n", (double)(end2 - start2) / CLOCKS_PER_SEC);
		
		delete scene;
    }
	
    return 0;
}
