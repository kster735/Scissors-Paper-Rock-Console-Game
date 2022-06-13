#include <stdio.h>
#include <stdlib.h>
#include "Players.h"

int main(int argc, char *argv[]) {
//	player_t* stergios = player_new();
//	player_ctor(stergios);
//	char temp[4];
//	askName(temp);
//	player_set(stergios, temp, 2, 23, 33, 3, 44, 3, 9);
//	player_show(stergios);
//	player_save(stergios);
//	player_dtor(stergios);
//	free(stergios);
	
	showAllplayers();
	
	sortPlayers();
	
	return 0;
}
