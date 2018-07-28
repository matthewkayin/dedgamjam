#include "level.hpp"

Level::Level(){
    
}

Level::Level(int screenwidth, int screenheight){

    base = new Chunk(0, 0, screenwidth, screenheight);
    cameraxOffset = 0;
    camerayOffset = 0;
    chunkwidth = screenwidth;
    chunkheight = screenheight;
    
    player.setX((screenwidth + player.getWidth()) / 2);
    player.setY((screenheight + player.getHeight()) / 2);
}

Chunk* Level::getChunkFromPosition(int x, int y){

    Chunk* curr = base;

    //while x and y are not inside curr's coordinate reach
    if( !( x >= curr->getX() && x < curr->getX() + chunkwidth && y >= curr->getY() && y <= curr->getY() + chunkheight ) ){

        while(x < curr->getX()){


        }
    }
}

Player Level::getPlayer(){
    
    return player;
}
