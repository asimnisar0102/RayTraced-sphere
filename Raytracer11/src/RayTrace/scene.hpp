#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "SDL.h"
#include "image.hpp"
#include "camera.hpp"
#include "objsphere.hpp"


namespace RT 
{
    class Scene
    {
        public:
            //default constructor
            Scene();

            //rendering function
            bool Render(image &outputImage);

        private:
            //camera
            RT::Camera m_camera;

            //unit sphere on origin (for testing)
            RT::ObjSphere m_testSphere;


    };
    
}


#endif