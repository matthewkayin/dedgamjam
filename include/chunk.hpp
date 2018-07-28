//Chunk class, each screen size portion of the map will be a chunk

#ifndef CHUNK_H
#define CHUNK_H

#include "object.hpp"

class Chunk{

public:
    Chunk(int chunkx, int chunky, int width, int height);
    Object* getHead();
    Chunk* getLeft() const;
    Chunk* getRight() const;
    Chunk* getUp() const;
    Chunk* getDown() const;
    void generateUp();
    void generateDown();
    void generateLeft();
    void generateRight();
    int getX() const;
    int getY() const;
private:
    int x;
    int y;
    int width;
    int height;
    Object *head;
    Chunk *left;
    Chunk *right;
    Chunk *up;
    Chunk *down;
};

#endif
