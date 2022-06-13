#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "menu.h"
#include "gameManager.h"

int main(int argc, char *argv[]){
	
	game_t* newGame;
	
	newGame = game_new();
	
	game_ctor(newGame);
	
	srand(time(NULL));
	
    gameLoop(newGame);
	
	game_dtor(newGame);
	
	free(newGame);
	
	return 0;
}
