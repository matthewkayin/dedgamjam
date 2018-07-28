#include "renderer.hpp"

Renderer::Renderer(){

    window = nullptr;
    renderer = nullptr;
}

bool Renderer::initGFX(std::string title, int width, int height){

    if(window || renderer){

        giveError("gfx already initialized!");
        return false;
    }

    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){

        giveSDLError("unable to initialize SDL");
        return false;
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); //alternatively, SDL_RENDERER_ACCELERATED for hardware renderering

    if(!window || !renderer){

        giveSDLError("unable to initialize window");
        return false;
    }

    initializeColorConstants();
    setRenderDrawColor(black);
    clear();
    render();

    return true;
}

void Renderer::clear(){

    SDL_RenderClear(renderer);
}

void Renderer::render(){

    SDL_RenderPresent(renderer);
}

void Renderer::setRenderDrawColor(Color c){

    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

void Renderer::drawRect(int x, int y, int width, int height){

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    SDL_RenderDrawRect(renderer, &rect);
}

void Renderer::fillRect(int x, int y, int width, int height){

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::drawLine(int x, int y, int sx, int sy){

    SDL_RenderDrawLine(renderer, x, y, sx, sy);
}

void Renderer::drawLine(int x, int y, int distance, float degree){

    int sy = distance * sin(toRadians(degree));
    int sx = distance * cos(toRadians(degree));

    drawLine(x, y, x + sx, y + sy);
}

void Renderer::drawImage(SDL_Texture* texture, int x, int y, int w, int h){ 

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Renderer::initializeColorConstants(){

    white = colorFromRGB(255, 255, 255);
    black = colorFromRGB(0, 0, 0);
    red = colorFromRGB(255, 0, 0);
    green = colorFromRGB(0, 255, 0);
    blue = colorFromRGB(0, 0, 255);
}

Renderer::Color Renderer::colorFromRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a){

    Color c;
    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;

    return c;
}

Renderer::Color Renderer::colorFromRGB(Uint8 r, Uint8 g, Uint8 b){

    return colorFromRGBA(r, g, b, 255);
}

SDL_Renderer* Renderer::getRenderer(){

    return renderer;
}

void Renderer::giveError(std::string message){

    std::cout << "Error! " << message << std::endl;
}

void Renderer::giveSDLError(std::string message){

    std::cout << "Error! " << message << " SDL Error: " << SDL_GetError() << std::endl;
}
