#include "level.hpp"

Level::Level(){

}

Level::Level(int screenwidth, int screenheight){

    base = new Chunk(0, 0, screenwidth, screenheight);
    cameraxOffset = 0;
    camerayOffset = 0;
    chunkwidth = screenwidth;
    chunkheight = screenheight;
    cameraSpeed = 3;
    cameraxSpeed = 0;
    cameraySpeed = 0;

    monsters = nullptr;

    player = Player(SDL_GetTicks());
    player.setX((screenwidth + player.getWidth()) / 2);
    player.setY((screenheight + player.getHeight()) / 2);
}

void Level::update(int delta){

    player.updatePosition(SDL_GetTicks(), delta);

    cameraxOffset += (cameraxSpeed * delta);
    camerayOffset += (cameraySpeed * delta);
}

Chunk* Level::getChunkFromPosition(int x, int y){

    Chunk* curr = base;

    //while x and y are not inside curr's coordinate reach
    if( !( x >= curr->getX() && x < curr->getX() + chunkwidth && y >= curr->getY() && y <= curr->getY() + chunkheight ) ){

        while(x < curr->getX() && curr != nullptr){

            curr = curr->getLeft();
        }

        while(x >= curr->getX() + chunkwidth && curr != nullptr){

            curr = curr->getRight();
        }

        while(y < curr->getY() && curr != nullptr){

            curr = curr->getUp();
        }

        while(y >= curr->getY() + chunkheight && curr != nullptr){

            curr = curr->getDown();
        }
    }

    return curr;
}

int Level::getCameraXOffset() const{

    return cameraxOffset;
}

int Level::getCameraYOffset() const{

    return camerayOffset;
}

void Level::setCameraXSpeed(int value){

    cameraxSpeed = value;
}

void Level::setCameraYSpeed(int value){

    cameraySpeed = value;
}

int Level::getCameraSpeed() const{

    return cameraSpeed;
}

void Level::createMonster(){

    Monster* hold = monsters;

    while (monsters->getTail() != nullptr)
        hold = monsters->getTail();

    Monster* newMon = new Monster;

    hold->setTail(newMon);

    newMon->setHead(hold);
    newMon->setTail(nullptr);

    int side = (rand() % 4);

    switch (side){

        //left
        case 0:
            newMon->setX(0);
            newMon->setY(rand() % (chunkheight - 48));
            break;

        //top
        case 1:
            newMon->setX(rand() % (chunkwidth - 48));
            newMon->setY(0);
            break;

        //right
        case 2:
            newMon->setX(chunkwidth - 48);
            newMon->setY(rand() % (chunkheight - 48));
            break;

        //bottom
        case 3:
            newMon->setX(rand() % (chunkwidth - 48));
            newMon->setY(chunkheight - 48);
            break;
    }
}

void Level::killMonster(Monster* deadMonster){

    Monster* hold = deadMonster;
    //head of linked list
    if (deadMonster->getHead() == nullptr && deadMonster->getTail() != nullptr){
        deadMonster = deadMonster->getTail();
        deadMonster->setHead(nullptr);
    }

    else{
        //at the end of linked list
        if(deadMonster->getTail() == nullptr && deadMonster->getHead() != nullptr){

            deadMonster = deadMonster->getHead();
            deadMonster->setTail(nullptr);
        }
        //middle of linked list
        else{

            hold = deadMonster;
            deadMonster = deadMonster->getHead();
            deadMonster->setTail(hold->getTail());
        }
    }
}

Player* Level::getPlayer(){

    return &player;
}
