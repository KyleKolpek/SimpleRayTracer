#include <iostream>
#include "scene.h"

using namespace std;

Scene::Scene():
    spheres(),
    triangles(),
    lights(),
    ambient(0.5),
    aaFactor(4)
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
    spheres.push_back(sphere1);

    // Create a triangle
    Triangle triangle1(
        Vertex(glm::vec3(-9.0, -9.0, -10.0),
               glm::vec3(0.0, 0.0, 1.0),
               glm::vec3(0.3, 0.0, 0.0),
               glm::vec3(0.5, 0.0, 0.5),
               glm::vec2(0.5, 0.5),
               2.0),
        Vertex(glm::vec3(9.0, -9.0, -10.0),
               glm::vec3(0.0, 0.0, 1.0),
               glm::vec3(0.0, 0.3, 0.0),
               glm::vec3(0.5, 0.0, 0.5),
               glm::vec2(0.5, 0.5),
               2.0),
        Vertex(glm::vec3(0.0, 9.0, -10.0),
               glm::vec3(0.0, 0.0, 1.0),
               glm::vec3(0.0, 0.0, 0.3),
               glm::vec3(0.5, 0.0, 0.5),
               glm::vec2(0.5, 0.5),
               2.0));
    triangles.push_back(triangle1);

    // Create a light
    Light light1(glm::vec3(0.0, 10.0, -5.0), glm::vec3(1.0, 1.0, 1.0));
    lights.push_back(light1);

    glm::vec3 eyeCoord(0.0, 0.0, 1.5);
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
                    fragColor += getFragmentColor(eyeCoord, planeCoord);
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

glm::vec3 Scene::getFragmentColor(glm::vec3 const &eye,
                                  glm::vec3 const &screen)
{
    glm::vec3 direction(glm::normalize(screen - eye));
    glm::vec3 normal;
    glm::vec3 normalMin;
    glm::vec3 fragPos;
    glm::vec3 fragPosMin;
    glm::vec3 diffColor;
    glm::vec3 specColor;
    float specCoef;
    float t;
    float tMin = 0xffff;
    int iMin;
    bool intersects = false;
    bool intersectsSphere = true;

    // Check spheres
    for(int i = 0; i < spheres.size(); ++i)
    {
        if(spheres[i].intersects(eye, direction, t, fragPos, normal))
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
        if(triangles[i].intersects(eye, direction, baryCoords, t, fragPos))
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
    }
    else
    {
        diffColor = triangles[iMin].getDiffColor(baryCoordsMin);
        specColor = triangles[iMin].getSpecColor(baryCoordsMin);
        specCoef  = triangles[iMin].getSpecCoef(baryCoordsMin);
        /*cout << "bary: " << baryCoordsMin.x << "," << baryCoords.y << "," <<
        baryCoordsMin.z << endl;
        cout << "diff: " << diffColor.x << "," << diffColor.y << "," <<
        diffColor.z << endl;
        cout << "spec: " << specColor.x << "," << specColor.y << "," <<
        specColor.z << endl;
        cout << "coef: " << specCoef << endl;*/
    }

    glm::vec3 lightDir;
    glm::vec3 fragColor(0.0);

    // Ambient
    fragColor += ambient * diffColor;

    for(int i = 0; i < lights.size(); ++i)
    {
        lightDir = glm::normalize(lights[i].pos - fragPosMin);

        // Diffuse
        fragColor += lights[i].color * diffColor *
                     glm::max(0.0f, glm::dot(normalMin, lightDir));
        // Specular
        fragColor += lights[i].color * specColor *
                     glm::pow(glm::max(0.0f,
                         glm::dot(-direction,
                              glm::reflect(-lightDir, normalMin))),
                              specCoef);
    }

    return fragColor;
}
