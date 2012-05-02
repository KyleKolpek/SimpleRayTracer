#include "triangle.h"
#include "GLM/gtx/intersect.hpp"
#include "image.h"

Vertex::Vertex(glm::vec3 const &pos,
               glm::vec3 const &normal,
               glm::vec3 const &diffColor,
               glm::vec3 const &specColor,
               glm::vec2 const &texCoords,
               float specCoef,
               float refFactor):
    pos(pos),
    normal(normal),
    diffColor(diffColor),
    specColor(specColor),
    texCoords(texCoords),
    specCoef(specCoef),
    refFactor(refFactor)
{
}

Triangle::Triangle(Vertex const &vert1,
                   Vertex const &vert2,
                   Vertex const &vert3):
    vert1(vert1),
    vert2(vert2),
    vert3(vert3),
    image(NULL)
{
    // TODO: check if this is the correct direction
    normal = glm::normalize(
             glm::cross(vert2.pos - vert1.pos, vert3.pos - vert1.pos));
    area = glm::dot(
           glm::cross(vert3.pos - vert2.pos, vert1.pos - vert2.pos ), normal);
}

Triangle::~Triangle()
{
    //TODO: deallocate image
}

// Intersection as described at
// http://www.cs.washington.edu/education/courses/csep557/10au/lectures/triangle_intersection.pdf
bool Triangle::intersects(glm::vec3 const &orig,
                          glm::vec3 const &dir,
                          glm::vec3 &baryCoords,
                          float &t,
                          glm::vec3 &intersection)
{
    float nd = glm::dot(normal, dir);

    // Intersection is at infinity
    if(nd == 0)
    {
        return false;
    }

    t = (glm::dot(normal, vert1.pos) - glm::dot(normal, orig))/ 
        nd;

    // If the intersection is behind the ray
    if(t <= 0)
    {
        return false;
    }
    
    // Check that the point is contained in the triangle
    glm::vec3 q = orig + dir * t;
    glm::vec3 lengths;

    lengths.x = glm::dot(glm::cross(vert3.pos - vert2.pos, q - vert2.pos),
                normal); 
    lengths.y = glm::dot(glm::cross(vert1.pos - vert3.pos, q - vert3.pos),
                normal); 
    lengths.z = glm::dot(glm::cross(vert2.pos - vert1.pos, q - vert1.pos),
                normal);

    if(lengths.x < 0 || lengths.y < 0 || lengths.z < 0)
    {
        return false;
    }

    // Compute barycentric coods
    baryCoords = lengths / area;
    
    intersection = q;
    return true;
}

glm::vec3 Triangle::getPos(glm::vec3 const &baryCoords)
{
    return vert1.pos * baryCoords.x +
           vert2.pos * baryCoords.y +
           vert3.pos * baryCoords.z;
}

glm::vec3 Triangle::getNormal(glm::vec3 const &baryCoords)
{
    return glm::normalize(vert1.normal * baryCoords.x +
                          vert2.normal * baryCoords.y +
                          vert3.normal * baryCoords.z);
}

glm::vec3 Triangle::getDiffColor(glm::vec3 const &baryCoords)
{
    return vert1.diffColor * baryCoords.x +
           vert2.diffColor * baryCoords.y +
           vert3.diffColor * baryCoords.z;
}

glm::vec3 Triangle::getSpecColor(glm::vec3 const &baryCoords)
{
    return vert1.specColor * baryCoords.x +
           vert2.specColor * baryCoords.y +
           vert3.specColor * baryCoords.z;
}

glm::vec2 Triangle::getTexCoords(glm::vec3 const &baryCoords)
{
    return vert1.texCoords * baryCoords.x +
           vert2.texCoords * baryCoords.y +
           vert3.texCoords * baryCoords.z;
}

float Triangle::getSpecCoef(glm::vec3 const &baryCoords)
{
    return vert1.specCoef * baryCoords.x +
           vert2.specCoef * baryCoords.y +
           vert3.specCoef * baryCoords.z;
}

float Triangle::getRefFactor(glm::vec3 const &baryCoords)
{
    return vert1.refFactor * baryCoords.x +
           vert2.refFactor * baryCoords.y +
           vert3.refFactor * baryCoords.z;
}
