#ifndef LIGHT_H
#define LIGHT_H

#include "GLM/glm.hpp"

class Light
{
public:
    Light(glm::vec3 const &pos, glm::vec3 const &color);

    glm::vec3 pos;
    glm::vec3 color;
};

#endif
