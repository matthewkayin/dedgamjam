#include "level.hpp"

Level::Level(){

}

Level::Level(int screenwidth, int screenheight){

    chunkwidth = screenwidth;
    chunkheight = screenheight;

    player = Player(SDL_GetTicks());
    player.setX((screenwidth + player.getWidth()) / 2);
    player.setY((screenheight + player.getHeight()) / 2);
}

Level::~Level(){

}

void Level::update(int delta){

    for(int i=0; i<100; i++){

        if(monsterArray[i].beingUsed()){

            monsterArray[i].updatePosition(delta);

            //check monster collisions
            if(getRectCollision(monsterArray[i].getX(), monsterArray[i].getY(), monsterArray[i].getWidth(), monsterArray[i].getHeight(),
                player.getX(), player.getY(), player.getWidth(), player.getHeight())){

                //std::cout << "player is dead" << std::endl;
            }

            Bullet *curr = player.getHead();

            while(curr != nullptr){

                if(getRectCollision(monsterArray[i].getX(), monsterArray[i].getY(), monsterArray[i].getWidth(), monsterArray[i].getHeight(),
                    curr->getX(), curr->getY(), 8, 8)){

                    std::cout << "monster is hit" << std::endl;
                }

                curr = curr->getNext();
            }
        }
    }

    player.updatePosition(SDL_GetTicks(), delta, chunkwidth, chunkheight);
}

void Level::createMonster(){

    bool foundMonster(false);

    int i;

    for(i=0; i<100 && !foundMonster; i++){

        if(!monsterArray[i].beingUsed()){
            monsterArray[i].setUse(true);
            foundMonster = true;
        }
    }

    if(foundMonster){

        int side = rand() % 4;
        switch (side){

                //left
            case 0:
                monsterArray[i].setX(0);
                monsterArray[i].setY(rand() % (chunkheight - 48));
                break;

                //top
            case 1:
                monsterArray[i].setX(rand() % (chunkwidth - 48));
                monsterArray[i].setY(0);
                break;

                //right
            case 2:
                monsterArray[i].setX(chunkwidth - 48);
                monsterArray[i].setY(rand() % (chunkheight - 48));
                break;

                //bottom
            case 3:
                monsterArray[i].setX(rand() % (chunkwidth - 48));
                monsterArray[i].setY(chunkheight - 48);
                break;

            default:
                break;
        }
    }
}


Monster* Level::getMonsterArray(){

    return monsterArray;
}

Player* Level::getPlayer(){

    return &player;
}

bool Level::getRectCollision(int x, int y, int width, int height, int xtwo, int ytwo, int widthtwo, int heighttwo){

    int xpoint = x;
    int ypoint = y;
    if ( xpoint >= xtwo && xpoint <= xtwo + widthtwo && ypoint >= ytwo && ypoint <= ytwo + heighttwo ){

        return true;
    }

    xpoint = x + width;
    if ( xpoint >= xtwo && xpoint <= xtwo + widthtwo && ypoint >= ytwo && ypoint <= ytwo + heighttwo ){

        return true;
    }

    ypoint = y + height;
    if ( xpoint >= xtwo && xpoint <= xtwo + widthtwo && ypoint >= ytwo && ypoint <= ytwo + heighttwo ){

        return true;
    }

    xpoint = x - width;
    if ( xpoint >= xtwo && xpoint <= xtwo + widthtwo && ypoint >= ytwo && ypoint <= ytwo + heighttwo ){

        return true;
    }

    return false;
}
