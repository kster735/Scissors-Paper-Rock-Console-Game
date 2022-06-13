#include <stdlib.h>
#include <stdio.h>
#include "gameManager.h"
#include "Players.h"

/*
	In the following rubric rows represent
	the p's (player's) hand, and columns represent
	npc's (non player character's) hand. 
	   		r  p  s
		------------	
		r  1  0  2
		p  2  1  0
		s  0  2  1
	The result for every combination of player and npc
	hands is given by the rubric. 
		 1 = draw 
		 2 = win for player
		 0 = win for npc (defeat for player)
*/
const int winRubric[3][3] = {{ 1, 0, 2},
							 { 2, 1, 0},
							 { 0, 2, 1}};
							 
							 
const char* hands[3]={"\"Rock\"","\"Paper\"", "\"Scissors\""}; 
const char* roundAnnouncement[3]={"\nSorry you lost Round %d... :( \n","\nIt's a draw in Round %d!\n","\nYou won Round %d!\n"};

game_t* game_new(void){
	game_t* game;
	game =(game_t*) malloc(sizeof(game_t));
	return game;
}

void game_ctor(game_t* game){
	game->results = (results_t*)malloc(sizeof(results_t));
}

void game_init(game_t* game){
	game->rounds=0;
	game->results->wins=0;
	game->results->draws=0;
	game->results->loses=0;
	game->p = 0;
	game->npc = 0;
	game->score = 0;
}

void game_dtor(game_t* game){
	free(game->results); 
}

//Returs 2 if player wins, 0 if npc wind or 1 for draw.
int winner(game_t* game){
	return winRubric[game->p][game->npc];
}

void presentRound(game_t* game, int result){
	printf("\n\nYou chose %s and npc chose %s\n", hands[game->p],hands[game->npc]);	
	printf(roundAnnouncement[result], game->rounds);
}

void presentGame(game_t* game){
	decorText(' ',1,1);
	decorText('#',40, 1);
	decorText('#',4, 0); printf("          GAME OVER             "); decorText('#',4, 1);
	decorText('#',40, 1);
	decorText(' ',1,1);
	printf("Rounds played: %d\n", game->rounds);
	printf("Wins: %d\n", game->results->wins);
	printf("Draws: %d\n", game->results->draws);
	printf("Loses: %d\n", game->results->loses);
	printf("Your Score: %d\n", game->score);
	if(game->results->wins == 3){
		printf("              YOU  WON!\n");
	}else{
		printf("              YOU LOST!\n");
	}
	
	decorText(' ',1,1);
}

int gameRound(game_t* game){
	int npc, p, isNum=0, inRange = 0;
	int result;
	char str[4];

	
	do{
		decorText('*',40,1);
		printf("\nYou have to win 3 rounds to defeat your PC!\n\n");
		printf("So far in this game...                          Rounds: %d\n", game->rounds);
		printf("                                                 Score: %d\n", game->score);
		printf("Rounds won : %d\n", game->results->wins);
		printf("Draws      : %d\n", game->results->draws);
		printf("Rounds lost: %d\n", game->results->loses);
		decorText('*',40,1);
		printf("\nPlease chose 1 = \"Rock\", 2 = \"Paper\" or 3 =\"Scissors\": ");
		fflush(stdin);
		if (fgets(str, 4, stdin) != NULL){
			isNum = isNumber(str, 4);
			if (isNum == 1) p = atoi(str);		
			system("cls");	
		}
		//Check if player choice is in range 1-3 for RPS.
		if (p<1 || p>3){
			printf("Wrong input!!!\n");
			inRange = 0;
		}else{
			inRange = 1;
		}		
	}while( !isNum || !inRange );
	
	npc = rand()%3;
	game->npc = npc;
	game->p = p-1;
	game->rounds++;

	decorText(' ',1,1);
	decorText('*',40,1);
	printf("Round %d:", game->rounds);	
			
	result = winner(game);
	game->score += result;
	presentRound(game, result);
	return result;
}

int gameLoop(game_t* game){
	int result, choice, gameActive=1;
	int games=0, totalwins=0, totaldefeats=0, totalrounds=0, totalrndwon=0, totalrnddraws=0, totalrndlst=0, totalscore=0;
	
	while(gameActive){
		choice = menu();
				
		gameActive = (choice == 1) ? 1 : 0;
	
		if (gameActive == 1){
			game_init(game);
			decorText(' ',1,1);
			decorText('*',40,1);
			decorText('*',4,0); printf("            NEW GAME!           "); decorText('*',4,1);
		}else{
			
			char name[4]="   \0";
			askName(name);
			player_t* player = player_new();
			player_ctor(player);
			player_set(player,name,games, totalwins,totaldefeats, totalrounds, totalrndwon, totalrnddraws, totalrndlst, totalscore);
			player_save(player);
			showAllplayers();
			
			printf("Exit Game...\n");
			return 1;
		}
		 
		games++;
		 
		while(game->results->wins < 3 && game->results->loses <3){	
			result = gameRound(game);
			switch(result){
				case 2:
					game->results->wins++;
					break;
				case 1:
					game->results->draws++;
					break;
				case 0:
					game->results->loses++;
					break;
			}
		}
		
		totalrndwon += game->results->wins;
		totalrnddraws += game->results->draws;
		totalrndlst += game->results->loses;
		totalrounds += game->rounds;
		totalscore += game->score;
		if (game->results->wins == 3){
			totalwins++;	
		}
		if(game->results->loses == 3){
			totaldefeats++;
		}
		
		presentGame(game);	
	}
	
	
	return 0;
}
