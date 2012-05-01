#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "GLM/glm.hpp"

class Vertex
{
public:
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec3 diffColor;
    glm::vec3 specColor;
    glm::vec2 texCoords;
    float specCoef;

    Vertex(glm::vec3 const &pos,
           glm::vec3 const &normal,
           glm::vec3 const &diffColor,
           glm::vec3 const &specColor,
           glm::vec2 const &texCoords,
           float specCoef);
};

class Triangle
{
public:
    Vertex vert1;
    Vertex vert2;
    Vertex vert3;
    glm::vec3 normal;
    float area;
    
    Triangle(Vertex const &vert1,
             Vertex const &vert2,
             Vertex const &vert3);

    bool intersects(glm::vec3 const &orig,
                    glm::vec3 const &dir,
                    glm::vec3 &baryCoords,
                    float &t,
                    glm::vec3 &intersection);

    // Accessors via barycentric coords
    glm::vec3 getPos(glm::vec3 const &baryCoords);
    glm::vec3 getNormal(glm::vec3 const &baryCoords);
    glm::vec3 getDiffColor(glm::vec3 const &baryCoords);
    glm::vec3 getSpecColor(glm::vec3 const &baryCoords);
    glm::vec2 getTexCoords(glm::vec3 const &baryCoords);
    float getSpecCoef(glm::vec3 const &baryCoords);

private:
};

#endif
