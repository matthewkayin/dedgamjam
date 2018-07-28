//Renderer class contains rendering and core SDL stuff

#ifndef RENDERER_H
#define RENDERER_H

#include "global.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>
#include <cmath>

class Renderer{

public:
    //structure to hold rgba info as one variable
    struct Color{

        Uint8 r;
        Uint8 g;
        Uint8 b;
        Uint8 a;
    };

    Renderer();
    ~Renderer();
    bool initGFX(std::string title, int width, int height);
    void toggleFullscreen();

    //rendering commands to use in main file's render function
    void clear();
    void render();
    void setRenderDrawColor(Color c);
    void drawRect(int x, int y, int width, int height);
    void fillRect(int x, int y, int width, int height);
    void drawLine(int x, int y, int sx, int sy);
    void drawLine(int x, int y, int distance, float degree);
    void drawImage(SDL_Texture* texture, int x, int y, int w, int h);

    //constants for commonly used colors
    Color white;
    Color black;
    Color blue;
    Color red;
    Color green;

    //utility functions to store paramters into a Color struct
    Color colorFromRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    Color colorFromRGB(Uint8 r, Uint8 g, Uint8 b);

    SDL_Renderer* getRenderer() const;
    int getScreenWidth() const;
    int getScreenHeight() const;

private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    bool isFullscreen;

    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;

    void initializeColorConstants();

    void giveError(std::string message);
    void giveSDLError(std::string message);
};

#endif
