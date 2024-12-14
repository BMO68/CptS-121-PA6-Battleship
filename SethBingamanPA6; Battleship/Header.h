/* header file lol */

#ifndef HEADER_H
#define HEADER_H

#define _CRT_SECURE_NO_WARNINGS 

#define Max_R 10
#define Max_C 10

#define CARRIER 5
#define CRUISER 3
#define SUBMARINE 3
#define BATTLESHIP 4
#define DESTROYER 2


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// if we were to do a gameboard struct

//typedef enum shipChar
//{
//	CARRIER = 5, CRUISER = 3, SUBMARINE = 3, BATTLESHIP = 4, DESTROYER = 2
//}ShipChar;




typedef struct bcell { //fuck bcell, use it if you have to later
	char hit; //*
	char ship; //depends, 'C' for Carrier, 'B' for Battleship, 'R' for Cruiser, 'S' for Submarine, 'D' for Destroyer
	char miss; //m
	int isHit;

	//char water; //~

} Bcell; 

typedef struct players {
	int player1;
	int player2;

} Players;

typedef struct player { //stores the stats of each player
	char BSboard[10][10];   
	char hitBSboard[10][10];
	int current_player;
	int hit_count;
	int miss_count;
	int total_shots;
	int shipType[5];
	int shipSize[5];
	char shipChar[5];
	int direction[4]; //0 up, 1 down, 2 left, 3 right
	int sunk_ships[5];

} Player;  

typedef struct stats {
	int hit_count;
	int miss_count;
	int total_shots;
	float hit_to_miss;
	int wins; 
} Stats;

void print_board(Player* currentplayer);   

//void initialize_players(Player* currentPlayer, Player* player1);

void initialize_player(Player* player, int playernum);   

void initialize_stats(Stats* player);

void update_stats(Stats* playeR, Player* player, Player* player1, Player* player2, int condition); 

void log_stats(Stats* playeR, FILE* output);

void initialize_hit_board(Player* player);

void battleship_cell(int modify);

void delay(int seconds);

void shooting(Player* currentplayer, Player* notcurrentplayer, Player* player1, Player* player2, FILE* output); 

void prompt_placement(Player* player, Player* player1, Player* player2);

int roll_for_turn(Player* currentplayer, Player* notcurrentplayer, Player* player1, Player* player2);

void placeShip(Player* player, int ship, int x, int y, int size, int direction);

void manually_place_ships(Player* player);

void random_place_all_ships(Player* player);

void check_up(Player* player, int r, int c, int shipsize);

void check_down(Player* player, int r, int c, int shipsize);

void check_left(Player* player, int r, int c, int shipsize);

void check_right(Player* player, int r, int c, int shipsize);

int win_condition(Player* player1, Player* player2); //determines if win condition was reached

void switchPlayers(Player* currentplayer, Player* notcurrentplayer, Player* player1, Player* player2);



#endif 