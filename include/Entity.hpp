#ifndef Entity_hpp
#define Entity_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

class Entity {
public:
    Entity();
    ~Entity();
    
    void updatePosition(int delta);
    
    int getX();
    int getY();
    int getDX();
    int getDY();
    int getWidth();
    int getHeight();
    int getHealth();
    Texture& getImage();
    
    void setX(int value);
    void setY(int value);
    void setDx(int value);
    void setDy(int value);
    void setHealth(int value);
    void setImage(SDL_Renderer* renderer, std::string path);
    
    bool getCollision(Entity &other);
    
private:
    Texture image;
    int x;
    int y;
    int xSpeed;
    int ySpeed;
    int health;
};

#endif /* Entity_hpp */
