#include "Game.h"

Game *game = nullptr;

int main(int argc, cont char *argv[])
{
	game = new Game();
	
	game->inti(/*enter parameters here*/)
	
	while(game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}
	
	game->clean();
	
	return 0;
}
