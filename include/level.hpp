//level class, where everything will happen
//level will be update logic only

#ifndef LEVEL_H
#define LEVEL_H
#include "Player.hpp"
#include "monster.hpp"
#include <ctime>

class Level{

public:
    Level();
    Level(int screenwidth, int screenheight);
    ~Level();

    void update(int delta);

    void createMonster();
    Monster* getMonsterArray();
    void killMonster(int value);
    void updateMonsterDir();

    Player* getPlayer();
    Uint32 getSpawnTime();
    bool getRectCollision(int x, int y, int width, int height, int xtwo, int ytwo, int widthtwo, int heighttwo);
    bool xIntersectY(int x, int y, int width, int height, int xtwo, int ytwo, int widthtwo, int heighttwo);

private:
    int chunkwidth;
    int chunkheight;
    Player player;
    Monster monsterArray[100];
};

#endif
