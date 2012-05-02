#include <fstream>
#include "image.h"

using namespace std;

Image::Image(string const &filename)
{
    int i = 0;
    string str;
    ifstream ifs(filename.c_str(), ifstream::in);
    
    // Ignore magic number
    ifs >> str;
    ifs >> width;
    ifs >> height;
    ifs >> maxVal;

    // Create image;
    image = new float[width * height * 3];
    
    // Setup rows
    imageRows = new float*[height];
    for(int i = 0; i < height; i++)
    {
        imageRows[i] = &image[(height - i - 1) * width * 3];
    }

    while(ifs.good())
    {
        ifs >> image[i];
        image[i] /= maxVal;
        i++;
    }
}

Image::~Image()
{
    delete[] image;
    delete[] imageRows;
}

glm::vec3 Image::getColor(glm::vec2 const &texCoords)
{
    glm::vec2 pixelCoords;
    // width/height - 2 provides a number from 0 to width/height - 1
    pixelCoords.x = texCoords.x * (width - 2);
    pixelCoords.y = texCoords.y * (height - 2);
   
    int pr = (int)pixelCoords.y;
    int pc = (int)pixelCoords.x;

    glm::vec2 subPixelCoords;
    subPixelCoords.x = pixelCoords.x - pc; 
    subPixelCoords.y = pixelCoords.y - pr; 

    // Perform bilinear interpolation
    pc *= 3;
    glm::vec3 lerp1(imageRows[pr][pc] * (1 - subPixelCoords.x) +
                    imageRows[pr][pc + 3] * subPixelCoords.x,
                    imageRows[pr][pc + 1] * (1 - subPixelCoords.x) +
                    imageRows[pr][pc + 3 + 1] * subPixelCoords.x,
                    imageRows[pr][pc + 2] * (1 - subPixelCoords.x) +
                    imageRows[pr][pc + 3 + 2] * subPixelCoords.x);
    glm::vec3 lerp2(imageRows[pr + 1][pc] * (1 - subPixelCoords.x) +
                    imageRows[pr + 1][pc + 3] * subPixelCoords.x,
                    imageRows[pr + 1][pc + 1] * (1 - subPixelCoords.x) +
                    imageRows[pr + 1][pc + 3 + 1] * subPixelCoords.x,
                    imageRows[pr + 1][pc + 2] * (1 - subPixelCoords.x) +
                    imageRows[pr + 1][pc + 3 + 2] * subPixelCoords.x);
    glm::vec3 lerp3(lerp1 * (1 - subPixelCoords.y) + lerp2 * subPixelCoords.y);
    return lerp3;
}
