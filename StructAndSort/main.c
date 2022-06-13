#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct{
	char c[4];
	int n;
}domi;

int comperatorNum(const void* p, const void* q);

int comperatorStr(const void* p, const void* q);

void domiShow(domi dm[3]);

int main(int argc, char *argv[]) {
	
	domi Arr[]={
		{"ato\0", 2},
		{"bto\0", 0},
		{"ati\0", 1}
	};
	printf("Before sorting\n\n");
	domiShow(Arr);
	printf("\n");
	
	int size = sizeof(Arr) / sizeof(domi);
	qsort(Arr, size, sizeof(domi), comperatorNum);
	
	printf("After sorting on numbers\n\n");
	domiShow(Arr);
	
	
	qsort(Arr, size, sizeof(domi), comperatorStr);
	
	printf("After sorting on strings\n\n");
	domiShow(Arr);
	return 0;
}

void domiShow(domi dm[3]){
	int i=0;
	for(i=0; i<3; i++){
		printf("Name: %s,  num: %d\n\n", dm[i].c, dm[i].n);
	}
}

int comperatorNum(const void* p, const void* q){
	const domi *p1 = p;
	const domi *p2 = q;
	return p1->n - p2->n;
}

int comperatorStr(const void* p, const void* q){
	const domi *p1 = p;
	const domi *p2 = q;
	return strcmp(p1->c, p2->c);
}
