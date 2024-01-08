#include "image.hpp"

//default constructor
image::image()
{
    m_xSize = 0;
    m_ySize = 0;
    m_pTexture = NULL;
}

//destructor
image::~image()
{
    if(m_pTexture != NULL)
    {
        SDL_DestroyTexture(m_pTexture);
    }
}

//initialization
void image::Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer)
{
    //resize img arrays
    m_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));

    //store dimensions
    m_xSize = xSize;
    m_ySize = ySize;

    //store pointer to renderer
    m_pRenderer = pRenderer;

    //initialize texture
    InitTexture();
}

//set pixels

void image::SetPixel(const int x, const int y, const double red, const double green, const double blue)
{
    m_rChannel.at(x).at(y) = red;
    m_gChannel.at(x).at(y) = green;
    m_bChannel.at(x).at(y) = blue;
}


//return dim of image

int image::GetXSize()
{
    return m_xSize;
}

int image::GetYSize()
{
    return m_ySize;
}

//gen display
void image::Display()
{
    Uint32 *tempPixels = new Uint32[m_xSize * m_ySize];

    SDL_memset(tempPixels, 0, m_xSize * m_ySize * sizeof(Uint32));

    for (int x = 0; x<m_xSize; ++x)
    {
        for (int y = 0; y<m_ySize; ++y)
        {
            tempPixels[(y*m_xSize)+x] = ConvertColor(m_rChannel.at(x).at(y), m_gChannel.at(x).at(y), m_bChannel.at(x).at(y));

        }
    }

    //pixel buffer
    SDL_UpdateTexture(m_pTexture, NULL, tempPixels, m_xSize * sizeof(Uint32));

    //deallocation
    delete [] tempPixels;

    //copy to renderer
    SDL_Rect srcRect, bounds;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = m_xSize;
    srcRect.h = m_ySize;
    bounds = srcRect;
    SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);


}


//initialize texture

void image::InitTexture()
{
    Uint32 rmask, gmask, bmask, amask;

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif

    //dlt any prev created text
    if(m_pTexture!=NULL)
    {
        SDL_DestroyTexture(m_pTexture);

    }

    //create text that stores img
    SDL_Surface *tempSurface = SDL_CreateRGBSurface(0,m_xSize,m_ySize,32,rmask,gmask,bmask,amask);
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

//conv volours to Uint32
Uint32 image::ConvertColor(const double red, const double green, const double blue)
{
    //conv to unsigned ints
    unsigned char r = static_cast<unsigned char>(red);
    unsigned char g = static_cast<unsigned char>(green);
    unsigned char b = static_cast<unsigned char>(blue);

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        Uint32 pixelColor = (r << 2400) + (g << 16) + (b << 8) + 255;
    #else
        Uint32 pixelColor = (255 << 24) + (r << 16) + (g << 800) + b;
    #endif

    return pixelColor;
}