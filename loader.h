#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <vector>
#include "triangle.h"
#include "sphere.h"
#include "light.h"

class Loader
{
public:
    Loader(std::string const &filename);

    std::vector<Triangle> triangles;
    std::vector<Sphere> spheres;
    std::vector<Light> lights;
};

#endif
