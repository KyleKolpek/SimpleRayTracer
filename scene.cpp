#include <iostream>
#include "scene.h"

using namespace std;

Scene::Scene():
    shapes(),
    lights(),
    ambient(0.2),
    aaFactor(1)
{
    // Set up an array of row pointers for convenience
    for(int i = 0; i < HEIGHT; ++i)
    {
        imageRows[i] = &image[3 * WIDTH * i];
    }
    
    // Create a sphere
    Sphere sphere1(glm::vec3(0, 0, -10), 2,
                   glm::vec3(0.0, 0.3, 0.3),
                   glm::vec3(0.5, 0.0, 0.5),
                   5);
    shapes.push_back(sphere1);

    // Create a light
    Light light1(glm::vec3(0.0, 10.0, -5.0), glm::vec3(1.0, 1.0, 1.0));
    lights.push_back(light1);

    glm::vec3 eyeCoord(0.0, 0.0, 1.5);

    // For each row
    for(int r = 0; r < HEIGHT; ++r)
    {
        // For each column
        for(int c = 0; c < WIDTH; ++c)
        {
            glm::vec3 planeCoord = inverseViewport(
                glm::vec2(1.0 * c / WIDTH, 1.0 * (HEIGHT - r) / HEIGHT));

            glm::vec3 fragColor = getFragmentColor(eyeCoord, planeCoord);

            imageRows[r][c * 3]     = fragColor.x;
            imageRows[r][c * 3 + 1] = fragColor.y;
            imageRows[r][c * 3 + 2] = fragColor.z;
            
        }
    }
}

void Scene::printScenePPM()
{
    cout << "P3" << endl;
    cout << WIDTH << " " << HEIGHT << endl;
    cout << 255 << endl;

    // For each row
    for(int r = 0; r < HEIGHT; ++r)
    {
        // For each column
        for(int c = 0; c < WIDTH; ++c)
        {
            // TODO: clamp to 0-255
            cout << (int)(imageRows[r][c * 3] * 255) << " ";
            cout << (int)(imageRows[r][c * 3 + 1] * 255) << " ";
            cout << (int)(imageRows[r][c * 3 + 2] * 255 ) << endl;
        }
    }
}

glm::vec3 Scene::inverseViewport(glm::vec2 const &viewportCoords)
{
    return glm::vec3(viewportCoords * 2.0f - glm::vec2(1.0f), 0.0f);
}

glm::vec3 Scene::getFragmentColor(glm::vec3 const &eye,
                                  glm::vec3 const &screen)
{
    glm::vec3 direction(glm::normalize(screen - eye));
    glm::vec3 normal;
    glm::vec3 normalMin;
    glm::vec3 fragPos;
    glm::vec3 fragPosMin;
    float t;
    float tMin = 0xffff;
    int iMin;
    bool intersects = false;

    for(int i = 0; i < shapes.size(); ++i)
    {
        if(shapes[i].intersects(eye, direction, t, fragPos, normal))
        {
            if(t < tMin)
            {
                tMin = t;
                normalMin = normal;
                iMin = i;
                fragPosMin = fragPos;
                intersects = true;
            }
        }
    }
    if(!intersects)
    {
        return glm::vec3(0.0);
    }

    glm::vec3 lightDir;
    glm::vec3 fragColor(0.0);

    // Ambient
    fragColor += ambient * shapes[iMin].diffColor;

    for(int i = 0; i < lights.size(); ++i)
    {
        lightDir = glm::normalize(lights[i].pos - fragPosMin);

        // Diffuse
        fragColor += lights[i].color * shapes[iMin].diffColor *
                     glm::max(0.0f, glm::dot(normalMin, lightDir));
        // Specular
        fragColor += lights[i].color * shapes[iMin].specColor *
                     glm::pow(glm::max(0.0f,
                         glm::dot(-direction,
                              glm::reflect(-lightDir, normalMin))),
                              shapes[iMin].specCoef);
    }

    return fragColor;
}
