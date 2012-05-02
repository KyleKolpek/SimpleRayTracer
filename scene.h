#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "GLM/glm.hpp"
#include "sphere.h"
#include "triangle.h"
#include "light.h"

#define WIDTH  800
#define HEIGHT 800

class Scene
{
public:
    Scene();
    void printScenePPM();

private:
    std::vector<Sphere> spheres;
    std::vector<Triangle> triangles;
    std::vector<Light> lights;
    float image[3 * WIDTH * HEIGHT];
    float *imageRows[HEIGHT];
    glm::vec3 ambient;
    int aaFactor;
    int maxLevels;

    // Transforms from space of (0,0),(1,1) to (-1,-1),(1,1)
    glm::vec3 inverseViewport(glm::vec2 const &viewportCoords);
    glm::vec3 getFragmentColor(glm::vec3 const &eye,
                               glm::vec3 const &screen,
                               int level);
};

#endif
