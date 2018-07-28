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

    void update(int delta);

    void createMonster();
    void killMonster(Monster* deadMonster);

    Player* getPlayer();
    Monster* getMonsterList();

private:
    int chunkwidth;
    int chunkheight;
    Player player;
    Monster* monsters;
};

#endif
