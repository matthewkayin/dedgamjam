//Gam Jam
//main.cpp

#include "renderer.hpp"
#include "texture.hpp"
#include "level.hpp"

#include <SDL2/SDL.h>
#include <iostream>

void input();
void update(int delta);
void render();

Texture grass;

Renderer renderer;
Level level;

int updates;
int frames;
bool running;

int main(int argc, char* argv[]){

    //Init the renderer, exit program if initialization failed
    if(!renderer.initGFX("Raycasting", 1280, 720)){

        return 0;
    }

    grass.import(renderer.getRenderer(), "res/gfx/grass.png");

    level = Level(renderer.getScreenWidth(), renderer.getScreenHeight());

    //timing constants
    const Uint32 SECOND = 1000;
    const Uint32 TARGET_FPS = 90;
    const Uint32 TARGET_UPS = 60;
    const Uint32 FRAME_TIME = SECOND / TARGET_FPS;
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
    Uint32 frameStart = 0;
    Uint32 loopDump = 0;
    Uint32 secDump = 0;
    Uint32 sleepTime = 0;

    loopStart = SDL_GetTicks();
    secStart = loopStart;
    frameStart = loopStart;

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
            for frames we figure how out much time, if any, we have in excess of the
            desired frame time. If our frame rendering was a shorter amount of time than
            the target, we sleep to stay on target. If our render time was longer we don't
            sleep since we're already falling behind schedule
        */
        timeDiff = currentTime - frameStart;
        if(TARGET_FPS != 0 && timeDiff < FRAME_TIME){

            sleepTime = FRAME_TIME - timeDiff;
        }

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

            std::cout << "FPS: " << fps << " UPS: " << ups << std::endl;
        }

        /*
            the sleep time is excess time that we have left over from rendering so we do not want
            to start the frame timer again until we are done with any sleeping we do.

            The update timer works based off of how much updates should have occured so we need the
            start time to happen here
        */
        loopStart = SDL_GetTicks();

        SDL_Delay(sleepTime);
        sleepTime = 0;

        frameStart = SDL_GetTicks();

        //actual calling of game functions
        input();
        update(delta);
        render();
    }

    return 0;
}

void input(){

    //events are for when things happen such as a mouse is clicked or a key is initially pressed/released
    SDL_Event e;

    while(SDL_PollEvent(&e) != 0){

        if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)){

            running = false;
        }
    }

    //scancodes and keyboard state are for figuring out which keys are being held in
    const Uint8 *state = SDL_GetKeyboardState(nullptr);
    int playerSpeed = 20;
    
    if (state[SDLK_w])
        level.setPlayerSpeedY(-playerSpeed);
    else{
        if (state[SDLK_s])
            level.setPlayerSpeedY(playerSpeed);
        else
            level.setPlayerSpeedY(0);
    }
    
    if (state[SDLK_a])
        level.setPlayerSpeedX(-playerSpeed);
    else{
        if (state[SDLK_d])
            level.setPlayerSpeedX(playerSpeed);
        else
            level.setPlayerSpeedX(0);
    }

}

void update(int delta){

    updates += delta;
}

void render(){

    renderer.clear();

    //draw the ground
    int dx = 0;
    int dy = 0;

    for(int i = 0; i < (renderer.getScreenWidth() * renderer.getScreenHeight()) / 64; i++){

        renderer.drawImage(grass.getImage(), dx, dy, grass.getHeight(), grass.getHeight());

        dx += 64;
        if(dx >= renderer.getScreenWidth()){

            dx = 0;
            dy += 64;
        }
    }

    renderer.render();
    frames++;
}
