#include "Entity.hpp"

Entity::Entity(){
    
    x = 0;
    y = 0;
    xSpeed = 0;
    ySpeed = 0;
    health = 0;
}

Entity::~Entity(){
    
    image.free();
}

void Entity::updatePosition(int delta){
    
    x += (xSpeed * delta);
    y += (ySpeed * delta);
}

int Entity::getX(){
    
    return x;
}

int Entity::getY(){
    
    return y;
}

int Entity::getWidth(){
    
    return image.getWidth();
}

int Entity::getHeight(){
    
    return image.getHeight();
}

int Entity::getHealth(){
    
    return health;
}

int Entity::getDX(){
    
    return xSpeed;
}

int Entity::getDY(){
    
    return ySpeed;
}

Texture& Entity::getImage(){
    
    return image;
}

void Entity::setX(int value){
    
    x = value;
}

void Entity::setY(int value){
    
    y = value;
}

void Entity::setDx(int value){
    
    xSpeed = value;
}

void Entity::setDy(int value){
    
    ySpeed = value;
}

void Entity::setHealth(int value){
    
    health = value;
}

void Entity::setImage(SDL_Renderer* renderer, std::string path){
    
    image.import(renderer, path);
}

bool Entity::getCollision(Entity &other){
    
    return (getX() >= other.getX() && getX() <= other.getX() + other.getWidth()
            && getY() >= other.getY() && getY() <= other.getY() + other.getHeight()) ||
    (other.getX() >= getX() && other.getX() <= getX() + getWidth()
     && other.getY() >= getY() && other.getY() <= getY() + getHeight());
}
