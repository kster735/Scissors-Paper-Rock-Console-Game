#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

typedef enum hand{rock, paper, scissors}hand_t; 

typedef struct results{
	int wins;
	int loses;
	int draws;
}results_t;

typedef struct game{
	int rounds;
	results_t* results;
	hand_t p; //current player hand;
	hand_t npc;//current npc hand;
	int score;
}game_t;

/////////////////////////////////////////
//allocate memory for new game structure
game_t* game_new(void);

//constructor for game
void game_ctor(game_t* game);

//game inintialization
void game_init(game_t* game);

//destructor for game
void game_dtor(game_t* game);

////////////////////////////////////
//Behavior functions for game class
int gameRound(game_t* game);

int gameLoop(game_t* game);

void presentRound(game_t* game, int result);

void presentGame(game_t* game);

//Determines winner per round
int winner(game_t* game);

#endif
