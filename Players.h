#ifndef PLAYERS_H
#define PLAYERS_H

typedef struct{
	char* name;
	int games;
	int wins;
	int defeats;
	int rounds;
	int rndwn;
	int rnddr;
	int rndlst;
	int score;
}player_t;

player_t* player_new(void);

void player_ctor(player_t* player);

void player_init(player_t* player);

void player_set(player_t* player, char name[4], int games, int wins,int defeats,int rounds,int rndwn,int rnddr,int rndlst, int score);

void player_dtor(player_t* player);

void player_show(player_t* player);

void player_save(player_t* player);

void askName(char name[4]);

void showAllplayers(void);

#endif
