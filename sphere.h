#ifndef SPHERE_H
#define SPHERE_H

#include "GLM/glm.hpp"

class Sphere
{
public:
    float radius;
    glm::vec3 center;
    glm::vec3 diffColor;
    glm::vec3 specColor;
    float specCoef;
    float refFactor;

    Sphere(glm::vec3 const &center,
           float radius,
           glm::vec3 const &diffColor,
           glm::vec3 const &specColor,
           float specCoef,
           float refFactor);
    ~Sphere();

    bool intersects(glm::vec3 const &origin,
                    glm::vec3 const &direction,
                    float &t,
                    glm::vec3 &intersection,
                    glm::vec3 &normal);

private:
};

#endif
