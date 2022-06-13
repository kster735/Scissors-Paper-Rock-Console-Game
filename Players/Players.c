#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "string.h"
#include "Players.h"
#include "SortPlayers.h"

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
	player_set(player, "   \0",0, 0, 0, 0, 0, 0, 0);
}

void player_set(player_t* player, char name[4], int games, int wins,int defeats,int rounds,int rndwn,int rnddr,int rndlst){
	strcpy(player->name, name);
	player->games = games;
	player->wins = wins;
	player->defeats = defeats;
	player->rounds = rounds;
	player->rndwn = rndwn;
	player->rnddr = rnddr;
	player->rndlst = rndlst;
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
		fprintf(fout, "%10s %10s %10s %10s %10s %15s %15s %15s\n","Name", "Games", "Wins", "Defeats", "Rounds", "Rounds Won", "Rounds Draw", "Rounds Lost");
		fprintf(fout, "     --------------------------------------------------------------------------------------------------\n");
	}else{
		fprintf(fout, "%10s %10d %10d %10d %10d %15d %15d %15d\n",player->name, player->games, player->wins, player->defeats, player->rounds, player->rndwn, player->rnddr, player->rndlst);	
	}
	fclose(fout);
}

void player_show(player_t* player){
	printf("%10s %10d %10d %10d %10d %15d %15d %15d\n",player->name, player->games, player->wins, player->defeats, player->rounds, player->rndwn, player->rnddr, player->rndlst);
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

void searchPlayers(void){
	//open file for reading and writing
	FILE* fp = fopen("playerData.txt", "r+");
	if (fp == NULL){
		perror("Could not open file playerData.txt\n");
		fclose(fp);
		exit(1);
	}
	
	int lines = 1, i=0;	
	char ch;
	
	char* titles = (char*) malloc(105);
	char* dashes = (char*) malloc(106);
	char temp[4];
	
	//copy titles from file
	fscanf(fp,"%c", &ch);
	while( ch!='\n'){
		titles[i++] = ch;
		fscanf(fp,"%c", &ch);
	}
	titles[i]=ch;
	titles[i+1]='\0';
	
	//copy dash line from file
	printf("%s", titles);
	i=0;
	fscanf(fp,"%c", &ch);
	while( ch!='\n'){
		dashes[i++] = ch;
		fscanf(fp,"%c", &ch);
	}
	dashes[i]=ch;
	dashes[i+1]='\0';
	printf("%s", dashes);
	
	//Free titles and dashes;
	free(titles);
	free(dashes);
		
	//read players data from file and copy them to players dynamic array
	char name[4];
	int games, wins, defeats, rounds, rndwn, rnddr, rndlst;
	i=0;
	player_t** players=(player_t**)malloc(lines*sizeof(player_t*));
	while(fscanf(fp, "%s %d %d %d %d %d %d %d\n", name, &games, &wins, &defeats, &rounds, &rndwn, &rnddr, &rndlst) != EOF){
		name[3]='\0';
		*(players+i) = player_new();
		player_ctor(*(players+i));
		player_set(*(players+i), name, games, wins, defeats, rounds, rndwn, rnddr, rndlst);
		i++;
		lines++;
		players = (player_t**) realloc(players, lines*sizeof(player_t*));
	}

	printf("\nDynamic array players before sorting: \n\n");
  	for (i=0; i<lines-1; i++){
  		player_show(*(players+i));
	}
	
	sortPlayersByNames(players, lines);
	
	printf("\nDynamic array players after sorting: \n\n");
  	for (i=0; i<lines-1; i++){
  		player_show(*(players+i));
	}
	
	//Free dynamic array players
  	for (i=0; i<lines-1; i++){
		player_dtor(*(players+i));
		free(*(players+i));
	}
	free(players);
	
	////Close file fp
	fclose(fp);
}

