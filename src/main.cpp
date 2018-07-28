//Gam Jam
//main.cpp

#include "renderer.hpp"
#include "texture.hpp"
#include "level.hpp"

#include <SDL2/SDL.h>

#include <iostream>
#include <cmath>

void input();
void update(int delta);
void render();
bool getRectangleCollision(int x, int y, int width, int height, int xtwo, int ytwo, int widthtwo, int heighttwo);
float getPlayerAngle();

Texture grassT;
Texture playerT;
Texture cursorT;
Texture bulletT;
Texture fpsText;
Texture upsText;
Texture handRockT;

bool displayFPS = false;

Renderer renderer;
Level level;

int mousex;
int mousey;
int recentY = 0;
int recentX = 0;

int updates;
int frames;
bool running;

int main(int argc, char* argv[]){

    //Init the renderer, exit program if initialization failed
    if(!renderer.initGFX("Raycasting", 1280, 720)){

        return 0;
    }

    grassT.import(renderer.getRenderer(), "res/gfx/grass.png");
    playerT.import(renderer.getRenderer(), "res/gfx/fingergun.png");
    cursorT.import(renderer.getRenderer(), "res/gfx/cursor.png");
    bulletT.import(renderer.getRenderer(), "res/gfx/bullet.png");
    handRockT.import(renderer.getRenderer(), "res/gfx/rockhand.png");

    level = Level(renderer.getScreenWidth(), renderer.getScreenHeight());

    //timing constants
    const Uint32 SECOND = 1000;
    const Uint32 TARGET_UPS = 60;
    const Uint32 UPDATE_TIME = SECOND / TARGET_UPS;

    //timing variables
    updates = 0;
    frames = 0;
    int fps = 0;
    int ups = 0;
    int delta;
    Uint32 timeDiff = 0;
    Uint32 currentTime = 0;
    Uint32 secStart = 0;
    Uint32 loopStart = 0;
    Uint32 loopDump = 0;
    Uint32 secDump = 0;
    Uint32 releaseMonster = 0;

    fpsText.import(renderer.getRenderer(), "FPS: " + std::to_string(fps), "monospace.ttf", 16, SDL_Color{0, 255, 0});
    upsText.import(renderer.getRenderer(), "UPS: " + std::to_string(ups), "monospace.ttf", 16, SDL_Color{0, 255, 0});

    loopStart = SDL_GetTicks();
    secStart = loopStart;

    running = true;

    //main gameloop, set running to false to exit
    while(running){

        /*
            for updates we check how much time has past since the last
            time check and figure out how many updates should have occured in that
            time, then we perform that many updates
        */
        currentTime = SDL_GetTicks();
        timeDiff = (currentTime - loopStart) + loopDump;
        delta = timeDiff / UPDATE_TIME;
        loopDump = timeDiff - (delta * UPDATE_TIME);

        /*
            check if a second has passed. If it has, record the fps and ups as being the
            amount of frames/updates that happened in the past second, then print the result
        */
        timeDiff = (currentTime - secStart) + secDump;
        if(timeDiff >= SECOND){

            secDump = timeDiff - SECOND;
            fps = frames;
            ups = updates;
            updates = 0;
            frames = 0;
            secStart = SDL_GetTicks();

            fpsText.import(renderer.getRenderer(), "FPS: " + std::to_string(fps), "monospace.ttf", 16, SDL_Color{0, 255, 0});
            upsText.import(renderer.getRenderer(), "UPS: " + std::to_string(ups), "monospace.ttf", 16, SDL_Color{0, 255, 0});
        }

        /*
            the sleep time is excess time that we have left over from rendering so we do not want
            to start the frame timer again until we are done with any sleeping we do.

            The update timer works based off of how much updates should have occured so we need the
            start time to happen here
        */
        
        if((currentTime - releaseMonster) >= 3000){
            releaseMonster = currentTime;
            level.createMonster();
        }
        
        loopStart = SDL_GetTicks();

        //actual calling of game functions
        input();
        update(delta);
        render();
    }

    grassT.free();
    playerT.free();
    fpsText.free();
    upsText.free();
    handRockT.free();

    return 0;
}

void input(){

    //events are for when things happen such as a mouse is clicked or a key is initially pressed/released
    SDL_Event e;

    while(SDL_PollEvent(&e) != 0){

        if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)){

            running = false;
        }

        if(e.type == SDL_MOUSEMOTION){

            mousex = e.motion.x;
            mousey = e.motion.y;
        }

        if(e.type == SDL_KEYDOWN){

            switch(e.key.keysym.sym){

                case SDLK_F1:
                    displayFPS = !displayFPS;
                    break;

                case SDLK_F11:
                    renderer.toggleFullscreen();
                    break;

                case SDLK_w:
                    recentY = -1;
                    break;

                case SDLK_s:
                    recentY = 1;
                    break;

                case SDLK_a:
                    recentX = -1;
                    break;

                case SDLK_d:
                    recentX = 1;
                    break;
            }
        }

        if(e.type == SDL_MOUSEBUTTONDOWN){

            level.getPlayer()->shoot(getPlayerAngle());
        }
    }

    //scancodes and keyboard state are for figuring out which keys are being held in
    const Uint8 *state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_S]){

        level.getPlayer()->setDy(recentY * level.getPlayer()->getSpeed());

    }else if(state[SDL_SCANCODE_W]){

        level.getPlayer()->setDy(-level.getPlayer()->getSpeed());

    }else if(state[SDL_SCANCODE_S]){

        level.getPlayer()->setDy(level.getPlayer()->getSpeed());

    }else{

        level.getPlayer()->setDy(0);
    }

    if (state[SDL_SCANCODE_A] && state[SDL_SCANCODE_D]){

        level.getPlayer()->setDx(recentX * level.getPlayer()->getSpeed());

    }else if(state[SDL_SCANCODE_A]){

        level.getPlayer()->setDx(-level.getPlayer()->getSpeed());

    }else if(state[SDL_SCANCODE_D]){

        level.getPlayer()->setDx(level.getPlayer()->getSpeed());

    }else{

        level.getPlayer()->setDx(0);
    }
}

void update(int delta){

    level.update(delta);

    updates += delta;
}

void render(){

    renderer.clear();

    //draw the ground
    int dx = 0;
    int dy = 0;

    for(int i = 0; i < (renderer.getScreenWidth() / grassT.getWidth()) * (renderer.getScreenHeight() / grassT.getWidth()); i++){

        renderer.drawImage(grassT.getImage(), dx, dy, grassT.getWidth(), grassT.getHeight());

        dx += 64;
        if(dx >= renderer.getScreenWidth()){

            dx = 0;
            dy += 64;
        }
    }

    float playerAngle = getPlayerAngle();
    
    Monster* hold = level.getMonsterArray();
    for(int i=0; i<100; i++){
        
        if(hold[i].beingUsed())
            renderer.drawImage(handRockT.getImage(), hold[i].getX(), hold[i].getY(), handRockT.getHeight(), handRockT.getWidth());
    }

    renderer.drawImage(playerT.getImage(), level.getPlayer()->getX(), level.getPlayer()->getY(), playerT.getWidth(), playerT.getHeight(), playerAngle);
    Bullet *curr = level.getPlayer()->getHead();
    while(curr != nullptr){

        /*float adjustedDegree = curr->getDegree();
        if(adjustedDegree >= 360){

            adjustedDegree -= 360;

        }else if(adjustedDegree < 0){

            adjustedDegree += 360;
        }*/
        float adjustedDegree = curr->getDegree();
        adjustedDegree -= 90;
        if(adjustedDegree >= 360){

            adjustedDegree -= 360;

        }else if(adjustedDegree < 0){

            adjustedDegree += 360;
        }

        renderer.drawImage(bulletT.getImage(), curr->getX(), curr->getY(), bulletT.getWidth(), bulletT.getHeight(), -adjustedDegree);
        curr = curr->getNext();
    }


    renderer.drawImage(cursorT.getImage(), mousex - (cursorT.getWidth() / 2), mousey - (cursorT.getHeight() / 2), cursorT.getWidth(), cursorT.getHeight());

    if(displayFPS){

        renderer.drawImage(fpsText.getImage(), 0, 0, fpsText.getWidth(), fpsText.getHeight());
        renderer.drawImage(upsText.getImage(), 0, 16, upsText.getWidth(), upsText.getHeight());
    }

    renderer.render();
    frames++;
}

bool getRectangleCollision(int x, int y, int width, int height, int xtwo, int ytwo, int widthtwo, int heighttwo){

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

float getPlayerAngle(){

    int playerx = level.getPlayer()->getX();
    int playery = level.getPlayer()->getY() + level.getPlayer()->getHeight();

    int xdist = pow(mousex - playerx, 2);
    int ydist = pow(mousey - playery, 2);
    float playerAngle = toDegrees(atan2(ydist, xdist));

    if(mousex - playerx < 0 && playery - mousey > 0){

        playerAngle += 180;

    }else if(mousex - playerx > 0 && playery - mousey < 0){

        playerAngle += 180;

    }else{

        playerAngle = 90 - playerAngle;
    }

    if(mousex - playerx > 0){

        if(playery - mousey < 0){

            playerAngle += 270;
        }

    }else if(mousex - playerx < 0){

        if(playery - mousey < 0){

            playerAngle += 180;

        }else if(playery - mousey > 0){

            playerAngle += 90;
        }
    }

    if(xdist == 0){

        if(playery - mousey < 0){

            playerAngle = 90;

        }else{

            playerAngle = 180;
        }

    }else if(ydist == 0){

        if(mousex - playerx < 0){

            playerAngle = 180;

        }else if(mousex - playerx > 0){

            playerAngle = 0;
        }
    }

    return playerAngle;
}
