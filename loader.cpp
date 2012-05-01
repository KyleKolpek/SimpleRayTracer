#include <fstream>
#include "loader.h"

using namespace std;

Loader::Loader(string const &filename)
{
    ifstream ifs(filename.c_str());
    string str;
    while(ifs.good())
    {
        switch(ifs.peek())
        {
        // Check for empty line
        case '\n':
            ifs.ignore(255, '\n');
            continue;

        // Check for comment
        case '#':
            ifs.ignore(255, '\n');
            continue;
        }
        ifs >> str;
        
        // Read a sphere
        if(!str.compare("ambient"))
        {
            
        }
        else if(!str.compare("sphere"))
        {
            glm::vec3 center;
            float radius;
            glm::vec3 diffColor;
            glm::vec3 specColor;
            float specCoef;
            int material;

            for(int i = 0; i < 4;)
            {
                if(ifs.good())
                {
                    ifs >> str;
                    if(!str.compare("mt:"))
                    {
                        string mat;
                        ifs >> mat;
                        if(!mat.compare("Phong"))
                        {
                            material = 0;
                        }
                        else if(!mat.compare("mirror"))
                        {
                            material = 1;
                        }
                        ++i;
                    }
                    else if(!str.compare("pos:"))
                    {
                        ifs >> center.x;
                        ifs >> center.y;
                        ifs >> center.z;
                        ++i;
                    }
                    else if(!str.compare("rad:"))
                    {
                        ifs >> radius;
                        ++i;
                    }
                    else if(!str.compare("Phong:"))
                    {
                        ifs >> diffColor.x;
                        ifs >> diffColor.y;
                        ifs >> diffColor.z;
                        ifs >> specColor.x;
                        ifs >> specColor.y;
                        ifs >> specColor.z;
                        ifs >> specCoef;
                        ++i;
                    }
                }
            }
            spheres.push_back(Sphere(center, radius, diffColor, specColor,
                specCoef));
        }
        // Read a triangle
        else if(!str.compare("triangle"))
        {
            
        }
    }
}
