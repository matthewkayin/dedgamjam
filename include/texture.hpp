//Texture class, used to store and print images

#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <iostream>

class Texture{

public:
    Texture();
    ~Texture();
    bool import(SDL_Renderer* renderer, std::string path);
    bool import(SDL_Renderer* renderer, std::string text, std::string path, int size, SDL_Color c);
    void free();
    SDL_Texture* getImage() const;
    int getWidth() const;
    int getHeight() const;

private:
    SDL_Texture* image;
    int width;
    int height;
};

#endif
