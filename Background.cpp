#include <iostream>
#include <string>
#include <SDL/SDL.h>

#include "GerenatePicture.h"

Image::Image():background(0),name("\0")
{
    positionFond.x=0;
    positionFond.y=0;
}

Image::Image(std::string filename):background(0),name(filename)
{
    positionFond.x=0;
    positionFond.y=0;
    background=SDL_LoadBMP( filename.c_str());
}
Image::~Image()
{
    SDL_FreeSurface(background);

}
SDL_Surface* Image::accesBackground()
{
    return background;
}

void Image::SetX(int _X)
{
    positionFond.x=_X;

}
void Image::SetY(int _Y)
{
     positionFond.y=_Y;

}

int Image::GetX()
{
    return positionFond.x;
}

int Image::GetY()
{
    return positionFond.y;
}

void Image::BlitSurfaces(const  Window& g, Image& i)
{
    SDL_BlitSurface( i.background, NULL, g.screen,&i.positionFond);
}

void Image::changeFond(std::string filename)
{
    name=filename; // il faudra mettre directement name au lieu de filenam.c_str()
   background=SDL_LoadBMP( filename.c_str());
}

string Image::GetName()const
{
    return name;
}
