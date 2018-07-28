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
        
        if(monsterArray[i].beingUsed())
            monsterArray[i].updatePosition(delta);
    }

    player.updatePosition(SDL_GetTicks(), delta);

    if(player.getX() <= 0){

        player.setX(0);

    }else if(player.getX() + player.getWidth() >= chunkwidth){

        player.setX(chunkwidth - player.getWidth());
    }

    if(player.getY() <= 0){

        player.setY(0);

    }else if(player.getY() + player.getHeight() >= chunkheight){

        player.setY(chunkheight - player.getHeight());
    }
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
