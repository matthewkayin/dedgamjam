//Gam Jam
//main.cpp

#include <SDL2/SDL.h>
#include <iostream>

void input();
void update(int delta);
void render();

int updates;
int frames;
bool running;

int main(int argc, char* argv[]){

    std::cout << "booperoni and cheese hello darkness my old friend not again or it might be okay" << std::endl;

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


}

void update(int delta){

    updates += delta;
}

void paint(){

    frames++;
}
