#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "string.h"
#include "Players.h"

player_t* player_new(void){
	player_t* player = (player_t*) malloc(sizeof(player_t));
	return player;
}

void player_ctor(player_t* player){
	player->name = (char*)malloc(4);
	player_init(player);
}

void player_dtor(player_t* player){
	free(player->name);
}

void player_init(player_t* player){
	player_set(player, "   \0",0, 0, 0, 0, 0, 0, 0, 0);
}

void player_set(player_t* player, char name[4], int games, int wins,int defeats,int rounds,int rndwn,int rnddr,int rndlst, int score){
	strcpy(player->name, name);
	player->games = games;
	player->wins = wins;
	player->defeats = defeats;
	player->rounds = rounds;
	player->rndwn = rndwn;
	player->rnddr = rnddr;
	player->rndlst = rndlst;
	player->score = score;
}

void askName(char name[4]){
	char buffer[5], ch;
	do{
		printf("Type your initials ( exactly 3 characters): ");
		fflush(stdin);
		fgets(buffer, 5, stdin); 
	}while( buffer[3] != '\n' );
	buffer[3] = '\0';
	int i;
	for (i=0; i<3; i++){
		ch = buffer[i];
		ch = (!isdigit(ch)) ? toupper(ch) : ch;
		name[i] = ch;		
	}
}

void player_save(player_t* player){
	FILE* fout;
	FILE* fin = fopen("playerData.txt", "r");
	int exists=0;
	exists = (fin == NULL) ? 0 : 1;
	close(fin);
	fout = fopen("playerData.txt", "a");
	if (!exists){
		fprintf(fout, "%10s %10s %10s %10s %10s %15s %15s %15s %15s\n","Name", "Games", "Wins", "Defeats", "Rounds", "Rounds Won", "Rounds Draw", "Rounds Lost", "Total Score");
		fprintf(fout, "     ------------------------------------------------------------------------------------------------------------------\n");
	}
	
	fprintf(fout, "%10s %10d %10d %10d %10d %15d %15d %15d %15d\n",player->name, player->games, player->wins, player->defeats, player->rounds, player->rndwn, player->rnddr, player->rndlst, player->score);	
	
	fclose(fout);
}

void player_show(player_t* player){
	printf("%10s %10d %10d %10d %10d %15d %15d %15d %15d\n",player->name, player->games, player->wins, player->defeats, player->rounds, player->rndwn, player->rnddr, player->rndlst, player->score);
}

void showAllplayers(void){
	FILE* fin = fopen("playerData.txt", "r");
	char ch;
	int i=0;
	while (fscanf(fin, "%c", &ch) != EOF){
		printf("%c", ch);
		i++;
	}
	printf("\n");
	fclose(fin);
}

