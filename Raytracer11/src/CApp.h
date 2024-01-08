#ifndef CAPP_H
#define CAPP_H

#include <SDL.h>
#include "./RayTrace/image.hpp"
#include "./RayTrace/scene.hpp"
#include "./RayTrace/camera.hpp"

class CApp
{
    public:
        CApp();

        int OnExecute();
        bool OnInit();
        void OnEvent(SDL_Event *event);
        void OnLoop();
        void OnRender();
        void OnExit();

    private:
        void PrintVector(const qbVector<double> &inputVector);
    
    private:
        //SDL2 stuff

        bool isRunning;
        SDL_Window *pWindow;
        SDL_Renderer *pRenderer;

        //instance of image class to store img
        image m_image;

        //instance of scene class
        RT::Scene m_Scene;
};

#endif