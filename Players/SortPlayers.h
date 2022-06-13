#ifndef SORTPLAYERS_H
#define SORTPLAYERS_H

void sortPlayersByWins(player_t** players, int lines);

void sortPlayersByNames(player_t** players, int lines);

int comperatorNum(const void* p, const void* q);

int comperatorStr(const void* p, const void* q);

#endif
