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

    player.setX((screenwidth + player.getWidth()) / 2);
    player.setY((screenheight + player.getHeight()) / 2);
}

Level::~Level(){
    
}

void Level::update(int delta){

    player.updatePosition(delta);
    
    for(int i=0; i<100; i++){
        
        if(monsterArray[i].beingUsed())
            monsterArray[i].updatePosition(delta);
    }

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
