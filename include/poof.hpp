#ifndef poof_h
#define poof_h
#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

class Poof{
    
public:
    Poof();
    bool keepShowing();
    bool isUsed();
    
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void setX(int value);
    void setY(int value);
    void setUsed(bool value);
    
private:
    int x;
    int y;
    int width;
    int height;

    Uint32 timeStarted;
    bool used;
};

#endif /* poof_h */
