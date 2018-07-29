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
float getMonsterAngle(int monsterx, int monstery);
void reset();

Texture grassT;
Texture playerT;
Texture cursorT;
Texture bulletT;
Texture fpsText;
Texture upsText;
Texture scoreText;
Texture handRockT;
Texture gameoverT;
Texture handPaperT;
Texture handScissorT;
Texture titleT;
Texture playText;
Texture aboutText;
Texture descText;
Texture titleAboutT;

bool displayFPS = false;

Renderer renderer;
Level level;

int mousex;
int mousey;
int recentY = 0;
int recentX = 0;

int gamestate;
int gameOverX;
int gameOverY;

int updates;
int frames;
bool running;

Uint32 releaseMonster = 0;
int score = -1;
int uifocus = -1;
int uistate = 0;

int main(int argc, char* argv[]){

    //Init the renderer, exit program if initialization failed
    if(!renderer.initGFX("Raycasting", 1280, 720)){

        return 0;
    }

    grassT.import(renderer.getRenderer(), "res/gfx/grass-wrapped.png");
    playerT.import(renderer.getRenderer(), "res/gfx/fingergun.png");
    cursorT.import(renderer.getRenderer(), "res/gfx/cursor.png");
    bulletT.import(renderer.getRenderer(), "res/gfx/bullet.png");
    handRockT.import(renderer.getRenderer(), "res/gfx/rockhand.png");
    gameoverT.import(renderer.getRenderer(), "res/gfx/gameover.png");
    handPaperT.import(renderer.getRenderer(), "res/gfx/paperhand.png");
    handScissorT.import(renderer.getRenderer(), "res/gfx/scissorhand.png");
    titleT.import(renderer.getRenderer(), "res/gfx/title.png");
    titleAboutT.import(renderer.getRenderer(), "res/gfx/title-about.png");
    playText.import(renderer.getRenderer(), "PLAY", "monospace.ttf", 60, SDL_Color{0, 148, 255});
    aboutText.import(renderer.getRenderer(), "ABOUT", "monospace.ttf", 60, SDL_Color{0, 148, 255});

    level = Level(renderer.getScreenWidth(), renderer.getScreenHeight());

    gamestate = 0;
    gameOverX = renderer.getScreenWidth() / 2;
    gameOverY = 0;

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

            if(gamestate == 0){

                if(uistate == 0){

                    if(uifocus == 1){

                        gamestate = 1;

                    }else if(uifocus == 2){

                        uistate = 2;
                    }
                }

            }else if(gamestate == 1){

                level.getPlayer()->shoot(getPlayerAngle());

            }else if(gamestate == 2){

                reset();
            }
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

    if(gamestate == 0){

        if(uistate == 0){

            //title menu
            if(mousex >= 300 - (playText.getWidth() / 2) && mousex <= 300 - (playText.getWidth() / 2) + playText.getWidth() &&
                mousey >= 230 && mousey <= 230 + playText.getHeight()){

                uifocus = 1;

            }else if(mousex >= 300 - (aboutText.getWidth() / 2) && mousex <= 300 - (aboutText.getWidth() / 2) + aboutText.getWidth() &&
                mousey >= 300 && mousey <= 300 + playText.getHeight()){

                uifocus = 2;

            }else{

                uifocus = -1;
            }
        }

    }else if(gamestate == 1){

        level.update(delta);


        if((SDL_GetTicks() - releaseMonster) >= level.getSpawnTime()){
            releaseMonster = SDL_GetTicks();
            level.createMonster();
        }
        level.updateMonsterDir();

        if(level.getPlayer()->getDead()){

            gamestate = 2;
        }

    }else if(gamestate == 2){

        if(abs(gameOverY - (renderer.getScreenHeight() / 2)) <= 5){

            gameOverY = renderer.getScreenHeight() / 2;

        }else{

            gameOverY += 3;
        }
    }

    updates += delta;
}

void render(){

    renderer.clear();

    if(gamestate == 0){

        //render title menu

        if(uistate == 0){

            renderer.drawImage(titleT.getImage(), 0, 0, 1280, 768);

            renderer.drawImage(playText.getImage(), 300 - (playText.getWidth() / 2), 230, playText.getWidth(), playText.getHeight());
            renderer.drawImage(aboutText.getImage(), 300 - (aboutText.getWidth() / 2), 300, aboutText.getWidth(), aboutText.getHeight());

            if(uifocus == 1){

                renderer.drawImage(playerT.getImage(), 300 - (playText.getWidth() / 2) + playText.getWidth() + 20, 230 + (playText.getHeight() / 2) - (playerT.getHeight() / 2), playerT.getWidth(), playerT.getHeight(), -90);

            }else if(uifocus == 2){

                renderer.drawImage(playerT.getImage(), 300 - (aboutText.getWidth() / 2) + aboutText.getWidth() + 20, 300 + (aboutText.getHeight() / 2) - (playerT.getHeight() / 2), playerT.getWidth(), playerT.getHeight(), -90);
            }

        }else if(uistate == 1){

            renderer.drawImage(titleAboutT.getImage(), 0, 0, 1280, 768);
        }

    }else{

        if(score != level.getPlayer()->getScore()){

            score = level.getPlayer()->getScore();
            scoreText.import(renderer.getRenderer(), "SCORE: " + std::to_string(score), "monospace.ttf", 20, SDL_Color{255, 255, 0});
        }

        //draw the ground
        int dx = 0;
        int dy = 0;

        for(int i = 0; i < (renderer.getScreenWidth() / grassT.getWidth()) * (768 / grassT.getWidth()); i++){

            renderer.drawImage(grassT.getImage(), dx, dy, grassT.getWidth(), grassT.getHeight());

            dx += grassT.getWidth();
            if(dx >= renderer.getScreenWidth()){

                dx = 0;
                dy += grassT.getWidth();
            }
        }

        Monster* hold = level.getMonsterArray();
        for(int i=0; i<100; i++){

            if(hold[i].beingUsed()){

                float adjustedDegree = hold[i].getDegree();

                adjustedDegree = getMonsterAngle(hold[i].getX(), hold[i].getY());

                if(i % 3 == 0)
                    renderer.drawImage(handRockT.getImage(), hold[i].getX(), hold[i].getY(), handRockT.getHeight(), handRockT.getWidth(), adjustedDegree);
                if(i % 3 == 1)
                    renderer.drawImage(handScissorT.getImage(), hold[i].getX(), hold[i].getY(), handScissorT.getHeight(), handScissorT.getWidth(), adjustedDegree);
                if(i % 3 == 2)
                    renderer.drawImage(handPaperT.getImage(), hold[i].getX(), hold[i].getY(), handPaperT.getHeight(), handPaperT.getWidth(), adjustedDegree);
            }
        }

        if(!level.getPlayer()->getDead()){

            float playerAngle = getPlayerAngle();
            renderer.drawImage(playerT.getImage(), level.getPlayer()->getX(), level.getPlayer()->getY(), playerT.getWidth(), playerT.getHeight(), playerAngle);
        }
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

        if(gamestate == 2){

            renderer.drawImage(gameoverT.getImage(), gameOverX - (gameoverT.getWidth() / 2), gameOverY - (gameoverT.getHeight() / 2), gameoverT.getWidth(), gameoverT.getHeight());
        }

        renderer.drawImage(scoreText.getImage(), renderer.getScreenWidth() - scoreText.getWidth(), 0, scoreText.getWidth(), scoreText.getHeight());
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

float getMonsterAngle(int monsterx, int monstery){

    int playerx = level.getPlayer()->getX();
    int playery = level.getPlayer()->getY();

    int xdist = pow(playerx - monsterx, 2);
    int ydist = pow(playery - monstery, 2);
    float playerAngle = toDegrees(atan2(ydist, xdist));

    if(playerx - monsterx < 0 && monstery - playery > 0){

        playerAngle += 180;

    }else if(playerx - monsterx > 0 && monstery - playery < 0){

        playerAngle += 180;

    }else{

        playerAngle = 90 - playerAngle;
    }

    if(playerx - monsterx > 0){

        if(monstery - playery < 0){

            playerAngle += 270;
        }

    }else if(playerx - monsterx < 0){

        if(monstery - playery < 0){

            playerAngle += 180;

        }else if(monstery - playery > 0){

            playerAngle += 90;
        }
    }

    if(xdist == 0){

        if(monstery - playery < 0){

            playerAngle = 90;

        }else{

            playerAngle = 180;
        }

    }else if(ydist == 0){

        if(playerx - monsterx < 0){

            playerAngle = 180;

        }else if(playerx - monsterx > 0){

            playerAngle = 0;
        }
    }

    return playerAngle;
}

void reset(){

    gameOverY = 0;
    level = Level(renderer.getScreenWidth(), renderer.getScreenHeight());
    releaseMonster += 3000;
    score = -1;

    gamestate = 1;
}
