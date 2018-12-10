#include <stdio.h>
#include <rand.h>
#include <gb/gb.h>
#include <gb/drawing.h>
#include <gb/console.h>
#include "gamedata.c"
#include "obstacle.c"

int pScore = 3;
int seed = 0;
int i,k,p,jumpCount,rate,key,temp,temp2,isFalling,isJumping,fallBuffer,onHS,nameLength,playerPlaced;
char *playerName[3];
char c;
char* pName = "Bill";
int jumpY = 102;
int frame = 0;

void AnimRun(){
	switch (frame) {//allows run anims to change on frames
		case 0:
		delay(80);
		set_sprite_tile(0,4);
		set_sprite_tile(1,6);
		break;
		case 1:
		delay(80);
		set_sprite_tile(0,8);
		set_sprite_tile(1,10);
		break;
		case 2:
		delay(80);
		set_sprite_tile(0,0);
		set_sprite_tile(1,2);
		break;	
	}
}

void AnimJump(){
	//will change based on time in air.
	set_sprite_tile(0,12);
	set_sprite_tile(1,14);
	wait_vbl_done();
}

void AnimDuck(){
	set_sprite_tile(0,16);
	set_sprite_tile(1,18);
	wait_vbl_done();
}

void Fall(){
	isJumping = 0;
	if(Pycurrent < Py){
		AnimJump();
		Pycurrent+=8;
		if(Pycurrent > Py){
			Pycurrent = Py;
		}
		move_sprite(1, Px+8, Pycurrent);//rightguy
		move_sprite(0, Px, Pycurrent);//leftguy
	}
	else{
		isJumping = 0;
		fallBuffer = 0;
		isFalling = 0;
	}
}

void Jump(){
	if(Pycurrent >= jumpY && isFalling != 1){
		AnimJump();
		Pycurrent-= 6;
		move_sprite(1, Px+8, Pycurrent);//rightguy
		move_sprite(0, Px, Pycurrent);//leftguy
	}
	if(Pycurrent <= jumpY){
		isJumping = 0;
		isFalling = 1;
	}
}

void clearScreen()
{
	int xS, yS;
	for(yS = 0; yS < 18; yS++)
		for(xS = 0; xS < 20; xS++)
		{
			gotoxy(xS, yS);
			setchar(' ');
		}
		gotoxy(0,0);
	}

	void BKG(){
	set_bkg_tiles(0, 0, 20, 18, map);//makes bkg
}

void SetSprites(){
	//character
	set_sprite_tile(0,0);//leftside-guy
	set_sprite_tile(1,2);//rightside-guy
	//scoreboard/pillars
	set_sprite_data(38,24,scoreboard);
	set_sprite_tile(10,38);//scoretiles

}

void SetSpritesLoc(){
	move_sprite(10,96,40);
	move_sprite(1, Px+8,Py);//rightguy
	move_sprite(0, Px, Py);//leftguy
}

void IntroScene(){
	CreateObstacle(0);
	move_sprite(2, 100, y);
	move_sprite(3, 100, y-40);
	move_sprite(4, 100, y-56);
	while(joypad() != J_A){
		seed++;
		frame += 1; //increments frame
		if(frame == 3){ //makes sure frame is never 3
			frame = 0;
		}
		if(seed >= 255){
			seed = 1;
		}
		AnimRun(); //calls the run anims
		delay(20);
	}
}

void InitEndGame(){
	//HIDE_SPRITES
	DISPLAY_OFF;
	HIDE_BKG;
	move_sprite(0, 200, y);
	move_sprite(1, 200, y);
	move_sprite(2, 200, y-9);//moves existing sprites off screen.
	move_sprite(3, 200, y-24);
	move_sprite(4, 200, y-40);
	move_sprite(5, 200, y-56);
	move_sprite(6, 200, y);
	move_sprite(10,200,50);
	DISPLAY_ON;

	if(onHS == 1){
		printf("Congrats, you placed on the leaderboard\n\n");
		printf("Enter your 3 letter \nname: \n\n\n");
		while(nameLength != 3){
			*(playerName + nameLength) = getchar();
			putchar(*(playerName + nameLength));
			nameLength++;
		}
	//	
		clearScreen();
		gotoxy(5,0);
		printf("SCOREBOARD\n--------------------\n");
		printf("      1. ");
		for(i = 0; i < 3; i++){
		putchar(*(playerName+i));
		}
		printf(" %d\n",hScore);
		printf("--------------------\n");
		for(p = 2;p <= 3;p++){
			printf("      %d. %s %d\n",p,pName,pScore);
			printf("--------------------\n");
			pScore--;
		}
		printf("    You scored:%d\n\n",hScore);
		printf(" Press '*' to play \n again.\n");
	}
	else{
		//show player highscore and ask play again
		clearScreen();
		gotoxy(5,0);
		printf("SCOREBOARD\n--------------------\n");
		for(p = 1;p <= 3;p++){
			printf("      %d. %s %d\n",p,pName,pScore);
			printf("--------------------\n");
			pScore--;

		}
		printf("    You scored:%d\n\n",hScore);
		printf(" Press '*' to play \n again.\n");
	}
}

void InitGame(){
	BKG();
	SetSprites();
	SHOW_BKG;
	SHOW_SPRITES;
	SPRITES_8x16;
	SetSpritesLoc();
	RandomObstacle();
	IntroScene();
	wait_vbl_done();
}

void main(){
	set_bkg_data(0,23,mapallwhite);
	set_sprite_data(0,28, stickguy);
	set_bkg_data(0, 23, tile);//bkg tile data
	set_sprite_data(0,28, stickguy);
	set_sprite_data(28,10,spriteTiles);
	InitGame();
	waitpad(J_A);
	//game starts
	initrand(seed);
	DISPLAY_OFF;
	set_bkg_tiles(0, 0, 20, 18, map2);//covers start text
	wait_vbl_done();
	DISPLAY_ON;
	onHS = 1;
	//StartLead();
	while(1){
		while(collided != 1){
		key = joypad();
		frame += 1; //increments frame
		if(frame == 3){ //makes sure frame is never 3
			frame = 0;
		}
		AnimRun(); //calls the run anims
		if(key==J_DOWN && isJumping!= 1 && isFalling != 1){
			CheckCrouch(1);
			AnimDuck();
		}
		if(key != J_DOWN){
			CheckCrouch(0);
		}
		if(key==J_UP){//jump anims
			isJumping = 1;
		}
		if(isJumping == 1 && isFalling == 0){
			Jump();
		}
		if(isFalling == 1){//might be why jump bug	
			if(fallBuffer > 4){		
				Fall();
			}
			else{
				AnimJump();
				fallBuffer++;
			}
		}
		MoveObs();
		delay(20);
	}
	break;
	}
	InitEndGame();
}
