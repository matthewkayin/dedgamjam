//level class, where everything will happen
//level will be update logic only

#ifndef LEVEL_H
#define LEVEL_H
#include "Player.hpp"
#include "monster.hpp"

class Level{

public:
    Level();
    Level(int screenwidth, int screenheight);
    ~Level();

    void update(int delta);

    void createMonster();
    Monster* getMonsterArray();

    Player* getPlayer();

private:
    int chunkwidth;
    int chunkheight;
    Player player;
    Monster monsterArray[100];
};

#endif
