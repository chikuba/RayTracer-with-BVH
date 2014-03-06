RayTracer-with-BVH
==================

A RayTracer I made years ago from scratch. It uses BVH to speed things up (even though it's quite slow).

Just add the files to an XCode project or compile it in the terminal. When you have the executable, just run: 

# ./RayTracer allteapot.txt

...and wait. 

It will first build the hierarchy and then start generating the image. This might take a while :P (a few minutes or so). 

If you want to create your own .txt-file, just create rows that follows these guidelines: 

# x, y, z, radius

For every row, there will a sphere. You can redo the code so that you can draw boxes instead. 

DISCLAIMER: 
This is my very first C++ program. 
 
