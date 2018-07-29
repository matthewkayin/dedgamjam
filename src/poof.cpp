#include "poof.hpp"

Poof::Poof(){
    
    timeStarted = 0;
    x = -100;
    y = -100;
    width = 48;
    height = 48;
    used = false;
}

bool Poof::keepShowing(){
    
    return (timeStarted - SDL_GetTicks() > 500);
}

bool Poof::isUsed(){
    
    return used;
}

int Poof::getX(){
    
    return x;
}
int Poof::getY(){
    
    return y;
}

int Poof::getWidth(){
    
    return width;
}

int Poof::getHeight(){
    
    return height;
}

void Poof::setX(int value){
    
    x = value;
}

void Poof::setY(int value){
    
    y = value;
}

void Poof::setUsed(bool value){
    
    if(value)
        timeStarted = SDL_GetTicks();
    
    used = value;
}
