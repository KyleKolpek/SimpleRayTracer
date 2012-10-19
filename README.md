# Ray Tracer
## UKY - CS 535: Intermediate Computer Graphics

This program implements all of the basic requirements of the program
specifications. This includes:

* Triangle Intersection
* Sphere Intersection
* Anti-Aliasing
* Phong Shading
* Point Lighting
* Reflective Surfaces
* Textured Triangles

I also implemented the following extra requirements:

* Shadow Rays

I have included various images of my progress in the image directory  as
progress*.png. My final scenes are available in the same directory as scene*.png

My texture images are loaded as a subset of PPM images. I make use of
imagemagick's `convert` tool to create these from other images.

The program writes the result image as a PPM to stdout. The `run` and `buildrun`
tools included are bash scripts that run the tool and pipe the output into
`convert` in order to write any kind of image out.

The implementation of the ray tracer is pretty straightforward. The Scene class
contains most of the code for setting up the scene and managing all of the
spheres, triangles, and lights. It performs the most of the logic, but calls out
to Triangle's and Sphere's intersection methods to get intersection data. The
Scene::getFragmentColor(..) function is used as the recursive ray tracing
function. 

I also used the GLM library for it's vector utilities. It has flaws
(sphere intersection code doesn't work, for example) but it provides a generally
solid, readable set of utilities to work with.
