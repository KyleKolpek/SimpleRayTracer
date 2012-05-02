#include <iostream>
#include "sphere.h"

using namespace std;

Sphere::Sphere(glm::vec3 const &center,
               float radius,
               glm::vec3 const &diffColor,
               glm::vec3 const &specColor,
               float specCoef,
               float refFactor):
    center(center),
    radius(radius), 
    diffColor(diffColor),
    specColor(specColor),
    specCoef(specCoef),
    refFactor(refFactor)
{
}

Sphere::~Sphere()
{
}

bool Sphere::intersects(glm::vec3 const &origin,
                        glm::vec3 const &direction,
                        float &t,
                        glm::vec3 &intersection,
                        glm::vec3 &normal)
{
    // a = 1
    float b = 2 * (glm::dot(direction, origin) - glm::dot(direction, center));
    float c = glm::dot(origin, origin) + glm::dot(center, center) -
              2 * glm::dot(origin, center) - radius * radius;
    float d = b * b - 4 * c; // Discriminant
    if(d < 0)
    {
        // No intersection
        //cerr << "No intersection" << endl;
        return false;
    }

    // Calculate small t
    t = (-b - glm::sqrt(d)) / 2;
    if(t <= 0)
    {
        // Calculate large t
        t = (-b + glm::sqrt(d)) / 2;
        if(t <= 0)
        {
            // Intersection is behind the ray
            //cerr << "Intersection is behind the ray" << endl;
            return false;
        }
    }
    
    intersection = t * direction + origin;
    normal = (intersection - center) / radius;

    return true;
    
}


