#include <rand.h>
#include <gb/gb.h>
#include "obstacle.h"
#include "player.h"

unsigned int x = 180;
unsigned int y = 120;
int qPassed = 0;
INT8 obst;
Player p1 = {10,120};
int Px = p1.x;
int Py = p1.y;
int Pycurrent = 120;
int collided;
int isCrouched;
int score = 38;
int nDigit;
int hScore;
int obstSpeed = 6;
int tempX = x;
int tempY,tempCY = Pycurrent;


void MoveObs(){
	x -= (obstSpeed+(hScore/10));
	if(x <= -5 && x >= -16){
		RandomObstacle();
		score+=2;
		hScore++;
		ChangeScore(score);
		qPassed = 0;
		x = 180;
	}
	if(x > 80 && qPassed == 1){
		qPassed = 0;
	}
	switch(obst){
		case 0:
			//single jump obstacle
		collided = hasCollided(obst);
		move_sprite(2, x, y);
		move_sprite(3, x, y-40);
		move_sprite(4, x, y-56);
		break;
		case 1:
			//duck obstacle
		collided = hasCollided(obst);
		move_sprite(2, x, y-9);
		move_sprite(3, x, y-24);
		move_sprite(4, x, y-40);
		move_sprite(5, x, y-56);
			//
		break;
		case 2:
			//quick-action obstacle a	
		if(x <= 50 && x >= 0 && qPassed != TRUE){
			if(joypad() == J_A){
				qPassed = 1;
				set_sprite_tile(2,60);
			}
		}
		collided = hasCollided(obst);
		move_sprite(2,x,y);
		move_sprite(3, x, y-16);
		move_sprite(4, x, y-24);
		move_sprite(5, x, y-40);
		move_sprite(6, x, y-56);
			//
		break;
		case 3:
			//quick-action obstacle b	
		if(x <= 50 && x >= 0 && qPassed != TRUE){
			if(joypad() == J_B){
				qPassed = 1;
				set_sprite_tile(2,60);
			}
		}
		collided = hasCollided(obst);
		move_sprite(2,x,y);
		move_sprite(3, x, y-16);
		move_sprite(4, x, y-24);
		move_sprite(5, x, y-40);
		move_sprite(6, x, y-56);
			//
		break;
	}
}
int hasCollided(int ob){
	tempX = x-8;
	tempY = Pycurrent-16;
	if(tempX <= 10 && tempX >= 5){
	tempCY = Pycurrent-8;
		if(ob == 0){
				if(Pycurrent > (104)){
					return 1;
				}
			}
		if(ob == 1){
				if((tempCY < 111) || isCrouched != 1){
					return 1;
				}
		}
		if(ob == 2){
			if(qPassed != 1){
				return 1;
			}
			else if(tempY < 103){
				return 1;
			}
		}
		if(ob == 3){
			if(qPassed != 1){
				return 1;
			}
			else if(tempY < 103){
				return 1;
			}
		}
		return 0;
	}
	else{
	return 0;
	}
}

void RandomObstacle(){
	obst = rand() & 3;
	CreateObstacle(obst);//calls CreateObstacle from obstacle.c
}

void ChangeScore(){
	if(score > 56){
		nDigit++;
		set_sprite_tile(11,(38+(nDigit*2)));
		move_sprite(11,96,40);
		move_sprite(10,104,40);
		score = 38;
	}
	set_sprite_tile(10,score);
}

void CheckCrouch(int check){
	if(check == 1){
		isCrouched = 1;
	}
	else{
		isCrouched = 0;
	}
}

void CreateObstacle(int ob){
	collided = 0;
	switch(ob) { //creates a randomly generated obstacle
		case 0:
			//single jump obstacle
		set_sprite_tile(2,28);
		set_sprite_tile(3,32);
		set_sprite_tile(4,32);
			//	
		break;
		case 1:
			//duck obstacle
		set_sprite_tile(2,30);
		set_sprite_tile(3,32);
		set_sprite_tile(4,32);
		set_sprite_tile(5,32);
		break;
		case 2:
			//quick-action obstacle a
		set_sprite_tile(2,34);
		set_sprite_tile(3,32);
		set_sprite_tile(4,32);
		set_sprite_tile(5,32);
		set_sprite_tile(6,32);
		break;
		case 3:
			//quick-action obstacle b
		set_sprite_tile(2,36);
		set_sprite_tile(3,32);
		set_sprite_tile(4,32);
		set_sprite_tile(5,32);
		set_sprite_tile(6,32);
		break;
	}
}