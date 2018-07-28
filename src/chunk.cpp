#include "chunk.hpp"

Chunk::Chunk(int chunkx, int chunky, int width, int height){

    x = chunkx;
    y = chunky;
    left = nullptr;
    right = nullptr;
    up = nullptr;
    down = nullptr;
    head = nullptr;
}

Object* Chunk::getHead(){

    return head;
}

Chunk* Chunk::getLeft() const{

    return left;
}

Chunk* Chunk::getRight() const{

    return right;
}

Chunk* Chunk::getUp() const{

    return up;
}

Chunk* Chunk::getDown() const{

    return right;
}

void Chunk::generateLeft(){

    left = new Chunk(x - width, y, width, height);
}

void Chunk::generateRight(){

    right = new Chunk(x + width, y, width, height);
}

void Chunk::generateUp(){

     up = new Chunk(x, y - height, width, height);
}

void Chunk::generateDown(){

    down = new Chunk(x, y + height, width, height);
}

int Chunk::getX() const{

    return x;
}

int Chunk::getY() const{

    return y;
}
