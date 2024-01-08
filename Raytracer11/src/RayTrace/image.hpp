#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include "SDL.h"

class image
{
    public:

        //constructor
        image();

        //destructor
        ~image();

        //initialization
        void Initialize(const int xSize, const int ysize, SDL_Renderer *pRenderer);

        //set colour of a pixel
        void SetPixel(const int x, const int y, const double red, const double green, const double blue);

        //function to handle display
        void Display();

        //functions to return dim of images

        int GetXSize();
        int GetYSize();

    private:

        Uint32 ConvertColor(const double red, const double green, const double blue);
        void InitTexture();

    private:

        //arrays that store img data

        std::vector<std::vector<double>> m_rChannel;
        std::vector<std::vector<double>> m_gChannel;
        std::vector<std::vector<double>> m_bChannel;

        //dimensions
        int m_xSize, m_ySize;

        SDL_Renderer *m_pRenderer;
        SDL_Texture *m_pTexture;



};

#endif