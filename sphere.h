#ifndef SPHERE_H
#define SPHERE_H

#include "GlM/glm.hpp"

class Sphere
{
public:
    float radius;
    glm::vec3 center;
    glm::vec3 diffColor;
    glm::vec3 specColor;
    float specCoef;

    Sphere(glm::vec3 const &center,
           float radius,
           glm::vec3 const &diffColor,
           glm::vec3 const &specColor,
           float specCoef);
    ~Sphere();

    bool intersects(glm::vec3 const &origin,
                    glm::vec3 const &direction,
                    float &t,
                    glm::vec3 &intersection,
                    glm::vec3 &normal);

private:
};

#endif
