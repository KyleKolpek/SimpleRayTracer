#include <iostream>
#include "scene.h"
#include "image.h"
#include "GLM/gtx/norm.hpp"

using namespace std;

Scene::Scene():
    spheres(),
    triangles(),
    lights(),
    ambient(0.5),
    aaFactor(4),
    maxLevels(4)
{
    // Set up an array of row pointers for convenience
    for(int i = 0; i < HEIGHT; ++i)
    {
        imageRows[i] = &image[3 * WIDTH * i];
    }
    
    // Create some spheres
    Sphere sphere1(glm::vec3(0, 0, -5), 2,
                   glm::vec3(0.0, 0.3, 0.3),
                   glm::vec3(0.5, 0.0, 0.5),
                   4.0,
                   1.0);
    spheres.push_back(sphere1);

    // Create the back 
    Triangle triangle1(
        Vertex(glm::vec3(-5.0, -5.0, -10.0),
               glm::vec3(0.0, 0.0, 1.0),
               glm::vec3(1.0, 1.0, 1.0),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(0.0, 0.0),
               2.0,
               0.0),
        Vertex(glm::vec3(5.0, -5.0, -10.0),
               glm::vec3(0.0, 0.0, 1.0),
               glm::vec3(1.0, 1.0, 1.0),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(1.0, 0.0),
               2.0,
               0.0),
        Vertex(glm::vec3(5.0, 5.0, -10.0),
               glm::vec3(0.0, 0.0, 1.0),
               glm::vec3(1.0, 1.0, 1.0),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(1.0, 1.0),
               2.0,
               0.0));
    triangles.push_back(triangle1);
    triangles.back().image = new Image("waves.ppm");

    Triangle triangle2(
        Vertex(glm::vec3(-5.0, -5.0, -10.0),
               glm::vec3(0.0, 0.0, 1.0),
               glm::vec3(1.0, 1.0, 1.0),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(0.0, 0.0),
               2.0,
               0.0),
        Vertex(glm::vec3(5.0, 5.0, -10.0),
               glm::vec3(0.0, 0.0, 1.0),
               glm::vec3(1.0, 1.0, 1.0),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(1.0, 1.0),
               2.0,
               0.0),
        Vertex(glm::vec3(-5.0, 5.0, -10.0),
               glm::vec3(0.0, 0.0, 1.0),
               glm::vec3(1.0, 1.0, 1.0),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(0.0, 1.0),
               2.0,
               0.0));
    triangles.push_back(triangle2);
    triangles.back().image = new Image("waves.ppm");

    // Create the right side
    Triangle triangle3(
        Vertex(glm::vec3(5.0, -5.0, -10.0),
               glm::vec3(-1.0, 0.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(0.0, 0.0),
               2.0,
               0.5),
        Vertex(glm::vec3(5.0, -5.0, 0.0),
               glm::vec3(-1.0, 0.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(0.0, 1.0),
               2.0,
               0.5),
        Vertex(glm::vec3(5.0, 5.0, 0.0),
               glm::vec3(-1.0, 0.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(1.0, 1.0),
               2.0,
               0.5));
    triangles.push_back(triangle3);

    Triangle triangle4(
        Vertex(glm::vec3(5.0, -5.0, -10.0),
               glm::vec3(-1.0, 0.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(0.0, 0.0),
               2.0,
               0.5),
        Vertex(glm::vec3(5.0, 5.0, 0.0),
               glm::vec3(-1.0, 0.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(1.0, 1.0),
               2.0,
               0.5),
        Vertex(glm::vec3(5.0, 5.0, -10.0),
               glm::vec3(-1.0, 0.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(1.0, 0.0),
               2.0,
               0.5));
    triangles.push_back(triangle4);

    // Create the bottom 
    Triangle triangle5(
        Vertex(glm::vec3(-5.0, -5.0, -10.0),
               glm::vec3(0.0, 1.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(0.0, 0.0),
               2.0,
               0.5),
        Vertex(glm::vec3(-5.0, -5.0, 0.0),
               glm::vec3(0.0, 1.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(0.0, 1.0),
               2.0,
               0.5),
        Vertex(glm::vec3(5.0, -5.0, 0.0),
               glm::vec3(0.0, 1.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(1.0, 1.0),
               2.0,
               0.5));
    triangles.push_back(triangle5);

    Triangle triangle6(
        Vertex(glm::vec3(-5.0, -5.0, -10.0),
               glm::vec3(0.0, 1.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(0.0, 0.0),
               2.0,
               0.5),
        Vertex(glm::vec3(5.0, -5.0, 0.0),
               glm::vec3(0.0, 1.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(1.0, 1.0),
               2.0,
               0.5),
        Vertex(glm::vec3(5.0, -5.0, -10.0),
               glm::vec3(0.0, 1.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(1.0, 0.0),
               2.0,
               0.5));
    triangles.push_back(triangle6);

    // Create the left
    Triangle triangle7(
        Vertex(glm::vec3(-5.0, -5.0, 0.0),
               glm::vec3(1.0, 0.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(0.0, 0.0),
               2.0,
               0.5),
        Vertex(glm::vec3(-5.0, -5.0, -10.0),
               glm::vec3(1.0, 0.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(0.0, 1.0),
               2.0,
               0.5),
        Vertex(glm::vec3(-5.0, 5.0, -10.0),
               glm::vec3(1.0, 0.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(1.0, 1.0),
               2.0,
               0.5));
    triangles.push_back(triangle7);

    Triangle triangle8(
        Vertex(glm::vec3(-5.0, -5.0, 0.0),
               glm::vec3(1.0, 0.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(0.0, 0.0),
               2.0,
               0.5),
        Vertex(glm::vec3(-5.0, 5.0, -10.0),
               glm::vec3(1.0, 0.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(1.0, 1.0),
               2.0,
               0.5),
        Vertex(glm::vec3(-5.0, 5.0, 0.0),
               glm::vec3(1.0, 0.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(1.0, 0.0),
               2.0,
               0.5));
    triangles.push_back(triangle8);

    // Create the top
    Triangle triangle9(
        Vertex(glm::vec3(-5.0, 5.0, -10.0),
               glm::vec3(0.0, -1.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(0.0, 0.0),
               2.0,
               0.5),
        Vertex(glm::vec3(5.0, 5.0, -10.0),
               glm::vec3(0.0, -1.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(0.0, 1.0),
               2.0,
               0.5),
        Vertex(glm::vec3(5.0, 5.0, 0.0),
               glm::vec3(0.0, -1.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(1.0, 1.0),
               2.0,
               0.5));
    triangles.push_back(triangle9);

    Triangle triangle10(
        Vertex(glm::vec3(-5.0, 5.0, -10.0),
               glm::vec3(0.0, -1.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(0.0, 0.0),
               2.0,
               0.5),
        Vertex(glm::vec3(5.0, 5.0, 0.0),
               glm::vec3(0.0, -1.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(1.0, 1.0),
               2.0,
               0.5),
        Vertex(glm::vec3(-5.0, 5.0, 0.0),
               glm::vec3(0.0, -1.0, 0.0),
               glm::vec3(0.3, 0.3, 0.5),
               glm::vec3(0.5, 0.5, 0.5),
               glm::vec2(1.0, 0.0),
               2.0,
               0.5));
    triangles.push_back(triangle10);

    // Create a light
    Light light1(glm::vec3(0.0, 4.9, -2.5), glm::vec3(1.0, 1.0, 1.0));
    lights.push_back(light1);

    glm::vec3 eyeCoord(0.0, 0.0, 1.0);
    float invAAFactor = 1.0/aaFactor;

    // For each row
    for(int r = 0; r < HEIGHT; ++r)
    {
        // For each column
        for(int c = 0; c < WIDTH; ++c)
        {
            // Multisampling
            glm::vec3 fragColor(0.0);
            for(int dr = 0; dr < aaFactor; ++dr)
            {
                for(int dc = 0; dc < aaFactor; ++dc)
                {
                    glm::vec3 planeCoord = inverseViewport(
                        glm::vec2((invAAFactor * dc + 1.0 * c) / WIDTH,
                                  (invAAFactor * dr + 1.0 * (HEIGHT - r))
                                  / HEIGHT));
                    fragColor += getFragmentColor(eyeCoord,
                        glm::normalize(planeCoord - eyeCoord), 1);
                }
            }
            fragColor *= invAAFactor * invAAFactor;

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

glm::vec3 Scene::getFragmentColor(glm::vec3 const &orig,
                                  glm::vec3 const &dir,
                                  int level)
{
    glm::vec3 normal;
    glm::vec3 normalMin;
    glm::vec3 fragPos;
    glm::vec3 fragPosMin;
    glm::vec3 diffColor;
    glm::vec3 specColor;
    float specCoef;
    float refFactor;
    float t;
    float tMin = 0xffff;
    int iMin;
    bool intersects = false;
    bool intersectsSphere = true;

    // Check spheres
    for(int i = 0; i < spheres.size(); ++i)
    {
        if(spheres[i].intersects(orig, dir, t, fragPos, normal))
        {
            if(t < tMin)
            {
                tMin = t;
                iMin = i;
                normalMin = normal;
                fragPosMin = fragPos;
                intersects = true;
            }
        }
    }

    // Check triangles
    glm::vec3 baryCoords;
    glm::vec3 baryCoordsMin;
    for(int i = 0; i < triangles.size(); ++i)
    {
        if(triangles[i].intersects(orig, dir, baryCoords, t, fragPos))
        {
            if(t < tMin)
            {
                tMin = t;
                iMin = i;
                baryCoordsMin = baryCoords;
                normalMin = triangles[i].getNormal(baryCoords);
                fragPosMin = fragPos;
                intersectsSphere = false;
                intersects = true;
            }
        }
    }
    if(!intersects)
    {
        return glm::vec3(0.0);
    }

    // Store nearest frag values
    if(intersectsSphere)
    {
        diffColor = spheres[iMin].diffColor;
        specColor = spheres[iMin].specColor;
        specCoef  = spheres[iMin].specCoef;
        refFactor = spheres[iMin].refFactor;
    }
    else
    {
        diffColor = triangles[iMin].getDiffColor(baryCoordsMin);
        if(triangles[iMin].image != NULL)
        {
            diffColor *= triangles[iMin].image->getColor(
                         triangles[iMin].getTexCoords(baryCoordsMin));
        }
        specColor = triangles[iMin].getSpecColor(baryCoordsMin);
        specCoef  = triangles[iMin].getSpecCoef(baryCoordsMin);
        refFactor  = triangles[iMin].getRefFactor(baryCoordsMin);
    }

    // Clamp refFactor
    refFactor = glm::max(glm::min(1.0f, refFactor),0.0f);

    glm::vec3 lightDir;
    glm::vec3 fragColor(0.0);

    // Ambient
    fragColor += ambient * diffColor;

    for(int i = 0; i < lights.size(); ++i)
    {
        if(checkRayIntersection(fragPosMin, lights[i].pos))
        {
            continue;
        }
        lightDir = glm::normalize(lights[i].pos - fragPosMin);

        // Diffuse
        fragColor += lights[i].color * diffColor *
                     glm::max(0.0f, glm::dot(normalMin, lightDir));
        // Specular
        fragColor += lights[i].color * specColor *
                     glm::pow(glm::max(0.0f,
                         glm::dot(-dir,
                              glm::reflect(-lightDir, normalMin))),
                              specCoef);
    }

    // Clamp fragment color
    fragColor.x = glm::min(1.0f, fragColor.x);
    fragColor.y = glm::min(1.0f, fragColor.y);
    fragColor.z = glm::min(1.0f, fragColor.z);

    // If we're done recursing
    if(level >= maxLevels || refFactor <= 0)
    {
        return fragColor;
    }

    glm::vec3 refDir = glm::reflect(dir, normalMin);

    // Cheap fix to prevent some intersections
    return fragColor * (1 - refFactor) +
        getFragmentColor(fragPosMin + 0.1f * refDir, refDir, level + 1) *
        refFactor;
}

bool Scene::checkRayIntersection(glm::vec3 orig, glm::vec3 lightPos)
{
    glm::vec3 dir = glm::normalize(lightPos - orig);
    glm::vec3 normal;
    glm::vec3 fragPos;
    glm::vec3 baryCoords;
    float t;

    for(int i = 0; i < spheres.size(); ++i)
    {
        if(spheres[i].intersects(orig, dir, t, fragPos, normal))
        {
            if(t * t < glm::length2(fragPos - lightPos))
            {
                return true;
            }
        }
    }
    
    for(int i = 0; i < triangles.size(); ++i)
    {
        if(triangles[i].intersects(orig, dir, baryCoords, t, fragPos))
        {
            if(t * t < glm::length2(fragPos - lightPos))
            {
                return true;
            }
        }
    }

    return false;
}
