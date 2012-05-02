#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "GLM/glm.hpp"

class Image
{
public:
    int width;
    int height;
    int maxVal;
    float *image;
    float **imageRows;

    Image(std::string const &filename);
    ~Image();
    glm::vec3 getColor(glm::vec2 const &texCoords);
};

#endif
