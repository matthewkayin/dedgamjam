//level class, where everything will happen
//level will be update logic only

#ifndef LEVEL_H
#define LEVEL_H
#include "Player.hpp"

#include "chunk.hpp"

class Level{

public:
    Level();
    Level(int screenwidth, int screenheight);

    void update(int delta);

    int getCameraXOffset() const;
    int getCameraYOffset() const;
    void setCameraXSpeed(int value);
    void setCameraYSpeed(int value);
    int getCameraSpeed() const;

    Chunk* getChunkFromPosition(int x, int y);

    void setPlayerSpeedX(int value);
    void setPlayerSpeedY(int value);

    Player getPlayer();

private:
    Chunk* base;
    int chunkwidth;
    int chunkheight;
    int cameraxOffset;
    int camerayOffset;
    int cameraxSpeed;
    int cameraySpeed;
    int cameraSpeed;
    Player player;
};

#endif
