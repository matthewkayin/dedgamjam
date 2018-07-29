#include "level.hpp"

Level::Level(){

}

Level::Level(int screenwidth, int screenheight){

    chunkwidth = screenwidth;
    chunkheight = screenheight;

    player = Player(SDL_GetTicks());
    player.setX((screenwidth + player.getWidth()) / 2);
    player.setY((screenheight + player.getHeight()) / 2);

    srand(time(NULL));
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
                player.setDead(true);
            }

            Bullet *curr = player.getHead();
            bool poofUsed(false);
            //std::cout << "checking bullet collisions for monster #" << i << std::endl;
            while(curr != nullptr){

                //std::cout << "monster: " << monsterArray[i].getX() << ", " << monsterArray[i].getY() << ", " << monsterArray[i].getWidth() << ", " << monsterArray[i].getHeight() << std::endl;
                //std::cout << "vs bullet: " << curr->getX() << ", " << curr->getY() << ", " << 8 << ", " << 8 << std::endl;

                if(getRectCollision(monsterArray[i].getX(), monsterArray[i].getY(), monsterArray[i].getWidth(), monsterArray[i].getHeight(),
                    curr->getX(), curr->getY(), 12, 12)){

                    killMonster(i);
                    
                    for(int j=0; j< 100 && !poofUsed; j++){

                        if(!poofArray[j].isUsed()){

                            poofArray[j].setUsed(true);
                            poofArray[j].setX(monsterArray[i].getX());
                            poofArray[j].setY(monsterArray[i].getY());
                            poofUsed = true;
                        }
                    }

                    Bullet *next = curr->getNext();
                    player.killBullet(curr);
                    curr = next;
                    player.countScore();
                    break;
                }

                if(curr != nullptr){

                    curr = curr->getNext();
                }
            }
        }
        
        //updates poofs
        if(poofArray[i].isUsed()){
            
            if (!poofArray[i].keepShowing())
                poofArray[i].setUsed(false);
        }
        
    }
    player.updatePosition(SDL_GetTicks(), delta, chunkwidth, chunkheight);
}

void Level::createMonster(){

    bool foundMonster = false;

    int index;

    for(int i=0; i<100 && !foundMonster; i++){

        if(!monsterArray[i].beingUsed()){
            monsterArray[i].setUse(true);
            foundMonster = true;
            index = i;
        }
    }

    if(foundMonster){

        int side = rand() % 4;
        switch (side){

                //left
            case 0:
                monsterArray[index].setX(0);
                monsterArray[index].setY(rand() % (chunkheight - 48));
                break;

                //top
            case 1:
                monsterArray[index].setX(rand() % (chunkwidth - 48));
                monsterArray[index].setY(0);
                break;

                //right
            case 2:
                monsterArray[index].setX(chunkwidth - 48);
                monsterArray[index].setY(rand() % (chunkheight - 48));
                break;

                //bottom
            case 3:
                monsterArray[index].setX(rand() % (chunkwidth - 48));
                monsterArray[index].setY(chunkheight - 48);
                break;

            default:
                break;
        }

    }
}

void Level::killMonster(int value){

    //value is the index of the monster being killed
    monsterArray[value].setUse(false);
}


Monster* Level::getMonsterArray(){

    return monsterArray;
}

Poof* Level::getPoofArray(){

    return poofArray;
}

void Level::updateMonsterDir(){

    int xDif, yDif, pos(0);

    for(int i=0; i<100; i++){

        if(monsterArray[i].beingUsed()){

            xDif = (player.getX() - monsterArray[i].getX());
            yDif = (player.getY() - monsterArray[i].getY());

            if(xDif == 0)
                xDif = 1;

            if(yDif == 0)
                yDif = 1;

            if(xDif > 0 && yDif < 0)
                pos = 1;

            if(xDif < 0 && yDif < 0)
                pos = 2;

            if(xDif <0 && yDif > 0)
                pos = 3;

            if (xDif < 0)
                xDif = xDif * -1;
            if(yDif < 0)
                yDif = yDif * -1;

            double radi = atan(xDif/yDif);
            monsterArray[i].setDegree(toDegrees(radi));

            monsterArray[i].setDx(monsterArray[i].getSpeed() * sin(radi));
            monsterArray[i].setDy(monsterArray[i].getSpeed() * cos(radi));

            switch (pos) {
                case 1:
                    monsterArray[i].setDy(-1 * monsterArray[i].getDY());
                    break;

                case 2:
                    monsterArray[i].setDx(-1 * monsterArray[i].getDX());
                    monsterArray[i].setDy(-1 * monsterArray[i].getDY());
                    break;

                case 3:
                    monsterArray[i].setDx(-1 * monsterArray[i].getDX());
                    break;

                default:
                    break;
            }
        }
    }
}

Player* Level::getPlayer(){

    return &player;
}

Uint32 Level::getSpawnTime(){
    
    if(player.getScore() < 25)
        return(3000 - (112 * player.getScore()));
    else
        return 200;l
}

bool Level::getRectCollision(int x, int y, int width, int height, int xtwo, int ytwo, int widthtwo, int heighttwo){

    return xIntersectY(x, y, width, height, xtwo, ytwo, widthtwo, heighttwo) || xIntersectY(xtwo, ytwo, widthtwo, heighttwo, x, y, width, height);
}

bool Level::xIntersectY(int x, int y, int width, int height, int xtwo, int ytwo, int widthtwo, int heighttwo){

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
