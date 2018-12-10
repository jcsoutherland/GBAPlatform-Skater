#include <stdio.h>
//#include <stdlib.h>
#include "leaders.h"
#include "linkedlist.h"
//gbdk doesnt let us do this stuff but we did it atleast.

int i;
LinkedList * lead;
leaders * l;
char * defaultName = "bill";

leaders * MakeLeader(int score, char * name){
	leaders * l = malloc(sizeof(leaders));
	l->score = score;
	l->name = name;
	return l;
}


void ReadFile(){

	FILE * f = fopen("leaderboard.txt", "r");
    if(f == NULL)

    {

    	//error
    }
    for(int i = 0; i < 3; i++){
    	char o[2];
    	fget(o, 2, f);
    	int s = atoi(o[0]);
    	leaders l = MakeLeader(s, o);
    	add(l);
    }

}

void add(leaders * l){
	lead->value = l;
	lead->next;
}


void WriteFile(){
	FILE * f = fopenf("leaderboard.txt", "w");
	int i = 0;
	while(i < 3){
		fprintf(f, "%d %s", lead->value->score lead->value->name);
		leaders->next;
		i++;
	}

}

void StartLead(){
	l = MakeLeader(9,defaultName);
	for(i = 0; i < 3;i++){
		lead->value = l;
		lead->next;
	}
}

int ChecksLeader(leaders * l){
	while(lead->next != NULL){
		if(l->score >= lead->value){
			LinkedList * s = lead;
			lead->value = l;
			lead->next = s;

		}
		lead->next;
	}
}
