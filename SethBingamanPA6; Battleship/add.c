/* funcions / def's for battleship.c and Headerh.h */

#include "Header.h"

//void initialize_players(Players* player_1, Players* player_2)
//{
//	currentPlayer = player1; 
//}

void battleship_cell(int modify)
{
	//if(modify == 0)
}

void print_board(Player* player)
{	
	printf(" ************* Player %d Board *************\n", player->current_player);

	printf("     0   1   2   3   4   5   6   7   8   9\n");
	for (int j = 0; j < 10; j++) //columns (duplicate rows)
	{
		printf("%d  ", j);
		for (int i = 0; i < 10; i++) //rows
		{
			printf("  %c ", player->BSboard[j][i]);   
		}
		printf("\n");
	}

}

void initialize_hit_board(Player* player)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			player->hitBSboard[i][j] = '~';
		}
	}
}

void print_hit_board(Player* player) //use this later
{
	printf(" ************* Player %d Board *************\n", player->current_player);

	printf("     0   1   2   3   4   5   6   7   8   9\n");
	for (int j = 0; j < 10; j++) //columns (duplicate rows) 
	{
		printf("%d  ", j);
		for (int i = 0; i < 10; i++) //rows
		{
			printf("  %c ", player->hitBSboard[j][i]);
		}
		printf("\n");
	}
}

void initialize_player(Player* player, int num)
{
	player->hit_count = 0;
	player->miss_count = 0;
	player->total_shots = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			player->BSboard[i][j] = '~';  
		}
	}
	player->current_player = num;
	player->shipChar[0] = 'C';
	player->shipChar[1] = 'B';
	player->shipChar[2] = 'R';
	player->shipChar[3] = 'S';
	player->shipChar[4] = 'D'; 
	player->shipType[0] = CARRIER;
	player->shipType[1] = BATTLESHIP;
	player->shipType[2] = CRUISER;
	player->shipType[3] = SUBMARINE;
	player->shipType[4] = DESTROYER;
	player->shipSize[0] = 5;
	player->shipSize[1] = 4;
	player->shipSize[2] = 3;
	player->shipSize[3] = 3;
	player->shipSize[4] = 2;

	for (int i = 0; i < 5; i++)
	{
		player->sunk_ships[i] = 0;
	}
}

void initialize_stats(Stats* player) 
{
	player->hit_count = 0;
	player->miss_count = 0;
	player->total_shots = 0; 
	player->hit_to_miss = 0; 
	player->wins = 0;
}

void update_stats(Stats* playeR, Player* player, Player* player1, Player* player2, int condition)  
{
	playeR->hit_count = player->hit_count;
	playeR->miss_count = player->miss_count;
	playeR->total_shots = player->total_shots;
	playeR->hit_to_miss = (float)player->hit_count / player->miss_count * 100;
	if (condition == -1 && player == player1)
	{
		playeR->wins++;
	}
	if (condition == 1 && player == player2)
	{
		playeR->wins++;
	}
}

void log_stats(Stats* playeR, FILE* output)
{
	fprintf(output, "Hits: %d\n", playeR->hit_count);
	fprintf(output, "Misses: %d\n", playeR->miss_count);
	fprintf(output, "Hit / miss percent: %d\n", playeR->hit_to_miss);
	fprintf(output, "Wins: %d\n", playeR->wins);
}

void delay(int seconds)
{
	time_t start_time = time(NULL);
	while (1)
	{
		time_t current_time = time(NULL);
		if (current_time - start_time >= seconds)

			break;
	}
}





void shooting(Player* currentplayer, Player* notcurrentplayer, Player* player1, Player* player2, FILE* output)
{
	int C = 0, R = 0;
	if (currentplayer->current_player == 1) 
	{
		system("cls");
		printf("************** Player %d **************\n\n", currentplayer->current_player);
		printf("Where would you like to shoot? X, Y:\n\n");
		print_hit_board(player1);
		scanf("%d, %d", &C, &R); 

		if (currentplayer->hitBSboard[R][C] == 'm' || currentplayer->hitBSboard[R][C] == '*')
		{
			printf("You have already shot here...\n");
			printf("Where would you like to shoot? X, Y:\n");
			scanf("%d, %d", &C, &R); //don't forget what you were doing
		}
		else //is hit
		{
			if (notcurrentplayer->BSboard[R][C] != '~')
			{
				currentplayer->hitBSboard[R][C] = '*';
				notcurrentplayer->BSboard[R][C] = '*';

				currentplayer->total_shots++;
				currentplayer->hit_count++;
				fprintf(output, "Player 1: Hit at %d, %d\n", C, R);

					for (int i = 0; i < 10; i++)
					{
						for (int j = 0; j < 10; j++)
						{
							if (notcurrentplayer->BSboard[i][j] == 'C') { currentplayer->sunk_ships[0]++; } //exception thrown somewhere in 'shooting'
							if (notcurrentplayer->BSboard[i][j] == 'B') { currentplayer->sunk_ships[1]++; }
							if (notcurrentplayer->BSboard[i][j] == 'R') { currentplayer->sunk_ships[2]++; }
							if (notcurrentplayer->BSboard[i][j] == 'S') { currentplayer->sunk_ships[3]++; }
							if (notcurrentplayer->BSboard[i][j] == 'D') { currentplayer->sunk_ships[4]++; }
						}
					}

					if (currentplayer->sunk_ships[0] == 1)
					{
						fprintf(output, "Carrier Sunk\n"); 
					}
					if (currentplayer->sunk_ships[1] == 1)
					{
						fprintf(output, "Battleship Sunk\n");
					}
					if (currentplayer->sunk_ships[2] == 1)
					{
						fprintf(output, "Cruiser Sunk\n");
					}
					if (currentplayer->sunk_ships[3] == 1)
					{
						fprintf(output, "Submarine Sunk\n");
					}
					if (currentplayer->sunk_ships[4] == 1)
					{
						fprintf(output, "Destroyer Sunk\n");
					}

					system("cls");
					printf("************** Player 1 **************\n\n");
					print_hit_board(currentplayer);
					printf("Hit at %d, %d!\n", C, R);
					system("pause");
			}
			else
			{
				currentplayer->total_shots++;
				currentplayer->miss_count++;
				currentplayer->hitBSboard[R][C] = 'm';
				fprintf(output, "Player 1: Miss at %d, %d\n", C, R);
				system("cls");
				printf("************** Player 1 **************\n\n");
				print_hit_board(currentplayer);
				printf("Miss at %d, %d\n", C, R);
				system("pause");
			}
	
		}
	}
	if(currentplayer->current_player == 2)//modification for player 2 shots
	{
		system("cls");
		printf("************** Player 2 **************\n\n");
		printf("Where would you like to shoot? X, Y:\n\n");
		delay(3);
		R = get_random_10();
		C = get_random_10();

		if (currentplayer->hitBSboard[R][C] == 'm' || currentplayer->hitBSboard[R][C] == '*')
		{
			R = get_random_10();
			C = get_random_10();
		}
		else //is hit
		{
			if (notcurrentplayer->BSboard[R][C] != '~')
			{
				currentplayer->hitBSboard[R][C] = '*';
				notcurrentplayer->BSboard[R][C] = '*';
				currentplayer->total_shots++;
				currentplayer->hit_count++;
				fprintf(output, "Player 2: Hit at %d, %d\n", C, R);

				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (notcurrentplayer->BSboard[i][j] == 'C') { currentplayer->sunk_ships[0]++; }
						if (notcurrentplayer->BSboard[i][j] == 'B') { currentplayer->sunk_ships[1]++; }
						if (notcurrentplayer->BSboard[i][j] == 'R') { currentplayer->sunk_ships[2]++; }
						if (notcurrentplayer->BSboard[i][j] == 'S') { currentplayer->sunk_ships[3]++; }
						if (notcurrentplayer->BSboard[i][j] == 'D') { currentplayer->sunk_ships[4]++; }
					}
				}

				if (currentplayer->sunk_ships[0] == 1)
				{
					fprintf(output, "Carrier Sunk\n");
				}
				if (currentplayer->sunk_ships[1] == 1)
				{
					fprintf(output, "Battleship Sunk\n");
				}
				if (currentplayer->sunk_ships[2] == 1)
				{
					fprintf(output, "Cruiser Sunk\n");
				}
				if (currentplayer->sunk_ships[3] == 1)
				{
					fprintf(output, "Submarine Sunk\n");
				}
				if (currentplayer->sunk_ships[4] == 1)
				{
					fprintf(output, "Destroyer Sunk\n");
				}

				system("cls");
				printf("************** Player 2 **************\n\n");
				print_hit_board(currentplayer);
				printf("Hit at %d, %d!\n", C, R);
				delay(3);
			}
			else
			{
				currentplayer->total_shots++;
				currentplayer->miss_count++;
				currentplayer->hitBSboard[R][C] = 'm';
				fprintf(output, "Player 2: Miss at %d, %d\n", C, R);
				system("cls");
				printf("************** Player 2 **************\n\n");
				print_hit_board(currentplayer);
				printf("Miss at %d, %d\n", C, R);
				delay(3);
			}
		}
	}
}

void prompt_placement(Player* player, Player* player1, Player* player2)
{
	int placement = 0;
	printf("Welcome to Battleship! Player 1, place your ships on your board...\n\n");
	print_board(player1);
	printf("\nWould you like to place your ships manually or randomly?\n");
	printf("1) Manually\n");
	printf("2) Randomly\n"); 
	scanf("%d", &placement);
	switch (placement)
	{
	case 1:
		manually_place_ships(player);  
		break;
	case 2:
		random_place_all_ships(player);
		print_board(player1); 
		delay(5);
		break;
	}



	system("cls");
	printf("Player 2, place your ships on your board...\n\n");
	print_board(player2);
	random_place_all_ships(player2); 
	delay(3);

	system("cls");

}

int roll_for_turn(Player* currentplayer, Player* notcurrentplayer, Player* player1, Player* player2)
{
	int die1 = rand() % 6 + 1, die2 = rand() % 6 + 1;
	printf("Roll to see who goes first...\n\n");
	delay(2);

	printf("************ Player 1 ************\n");
	system("pause");

	printf("Player 1 rolled: [%d]\n\n", die1);
	delay(1);

	printf("************ Player 2 ************\n");
	delay(2);

	printf("Player 2 rolled: [%d]\n\n", die2);

	delay(1);

	if (die1 > die2)
	{
		printf("Player 1 goes first...\n"); 
		return 1;
	}
	if (die1 < die2)
	{
		printf("Player 2 goes first...\n"); 
		return 2;
	}
	if (die1 == die2)
	{
		printf("Tie! Rerolling...\n");
		delay(1);
		while (die1 == die2)
		{
			die1 = rand() % 6 + 1;
			die2 = rand() % 6 + 1;
			printf("Player 1 rolled: [%d]\nPlayer 2 rolled: [%d]\n", die1, die2);
		}
		if (die1 > die2)
		{
			printf("Player 1 goes first...\n");
			return 1;
		}
		if (die1 < die2)
		{
			printf("Player 2 goes first...\n"); 
			return 1;
		}
	}

	delay(3);
	system("cls");
}

void placeShip(Player* player, int ship, int x, int y, int size, int direction) 	// alrogithm to iterate through 2d array to place ship in given direction
{		 //up, down, left, right

		if (direction == 1) //up
		{
			for (int i = 0; i < size; i++)
			{
				player->BSboard[x - i][y] = player->shipChar[ship];      
			}
		}
		if (direction == 2) //down
		{
			for (int i = 0; i < size; i++)
			{
				player->BSboard[x + i][y] = player->shipChar[ship];
			}
		}
		if (direction == 3) //left
		{
			for (int i = 0; i < size; i++)
			{
				player->BSboard[x][y - i] = player->shipChar[ship];
			}
		}
		if (direction == 4) //right
		{
			for (int i = 0; i < size; i++)
			{
				player->BSboard[x][y + i] = player->shipChar[ship];
			}
		}

}

//scanf("%d, %d", &X, &Y); 

void manually_place_ships(Player* player)
{
	// 0 is up, 1 is down, 2 is left, 3 is right //0 is invalid, 1 is valid
	int tempX = 0, tempY = 0, direction2 = 0;
	int j = 0;
	for (int i = 0; i < 5; i++)
	{
		char yes = 'N', yes2 = 'N';

		while (yes == 'N')
		{
			printf("Place your %c \n", player->shipChar[i]); //5 spaces long
			printf("Enter empty starting coordinate on board: X, Y\n"); // 
			scanf("%d, %d", &tempY, &tempX); //change these later if you have to
			if (player->BSboard[tempX][tempY] == '~')
			{
				printf("Valid selection; is this correct? (Y/N):\n");
				scanf(" %c", &yes);

			}
		}

		check_up(player, tempX, tempY, player->shipSize[i]);
		check_down(player, tempX, tempY, player->shipSize[i]);
		check_left(player, tempX, tempY, player->shipSize[i]);
		check_right(player, tempX, tempY, player->shipSize[i]);

		
		//printf("Place your %c", ship);
		while (player->BSboard[tempX][tempY] == '~') //change this soon
		{
			while(yes2 == 'N')
			{
				printf("Which direction will your ship face? \n");
				if (player->direction[0] == 1)
				{
					printf("1) Place facing up\n");
				}
				if (player->direction[1] == 1)
				{
					printf("2) Place facing down\n");
				}
				if (player->direction[2] == 1)
				{
					printf("3) Place facing left\n");
				}
				if (player->direction[3] == 1)
				{
					printf("4) Place facing right\n");
				}
					scanf("%d", &direction2);
					printf("Are you sure?: Y/N\n");
					scanf(" %c", &yes2);
			}

				placeShip(player, j, tempX, tempY, player->shipSize[j], direction2);
				print_board(player);
				j++;
				delay(3);
		}

	}

}


int get_random_10()
{
	int i = 0;
	i = rand() % 10;
	return i;
}

void random_place_all_ships(Player* player) //add ship sizes soon
{
	int row;
	int column;

	for (int i = 0; i < 5; i++)
	{
		row = get_random_10();
		column = get_random_10();
		while (player->BSboard[row][column] != '~')
		{
			row = get_random_10();
			column = get_random_10();
		}
		check_up(player, row, column, player->shipSize[i]); //ship size 
		check_down(player, row, column, player->shipSize[i]); //ship size
		check_left(player, row, column, player->shipSize[i]); //ship size
		check_right(player, row, column, player->shipSize[i]); //ship size


			int place = 0; //ask how to make loop continue until a ship is placed

				
			place = rand() % 4;
			int condition = 1;
				
				while (condition == 1)
				{

					if (player->direction[place] == 0)
					{
						place = rand() % 4;
					}
					else
					{
						condition = 0;
					}
					
				}

				placeShip(player, i, row, column, player->shipSize[i], place + 1); //player->direction[place]

				/*if (place == 0 && player->direction[0] == 1)
				{
					placeShip(player, player->shipChar[i], row, column, player->shipSize[i], 0);
				}
				if (place == 1 && player->direction[0] == 1)
				{
					placeShip(player, player->shipChar[i], row, column, player->shipSize[i], 1);
				}
				if (place == 2 && player->direction[0] == 1)
				{
					placeShip(player, player->shipChar[i], row, column, player->shipSize[i], 2);
				}
				if (place == 3 && player->direction[0] == 1)
				{
					placeShip(player, player->shipChar[i], row, column, player->shipSize[i], 3);
				}*/
	}
}

int win_condition(Player* player1, Player* player2)
{
	if (player1->hit_count == 17) { return -1; }
	if (player2->hit_count == 17) { return 1; }
	else { return 0; }
}

void check_up(Player* player, int r, int c, int shipsize) //if yes then return 1, if no then return 0
{
	player->direction[0] = 1;
	for (int a = 0; a < shipsize; a++)
	{
		if ((r - a) < 0) { player->direction[0] = 0; } //not able to place up
		if (player->BSboard[r - a][c] != '~') { player->direction[0] = 0; } //not able to place up
	}
	 // can place up (patern is the same for following functions
}

void check_down(Player* player, int r, int c, int shipsize)
{
	player->direction[1] = 1;
	for (int a = 0; a < shipsize; a++)
	{
		if ((r + a) > 10) { player->direction[1] = 0; } // change out of bounds check for array notation
		if (player->BSboard[r + a][c] != '~') { player->direction[1] = 0; }
	}
}

void check_left(Player* player, int r, int c, int shipsize)
{
	player->direction[2] = 1;
	for (int a = 0; a < shipsize; a++)
	{
		if ((c - a) < 0) { player->direction[2] = 0; } // change out of bounds check for array notation
		if (player->BSboard[r][c - a] != '~') { player->direction[2] = 0; }
	}
}

void check_right(Player* player, int r, int c, int shipsize)
{
	player->direction[3] = 1;
	for (int a = 0; a < shipsize; a++)
	{
		if ((c + a) > 10) { player->direction[3] = 0; } // change out of bounds check for array notation
		if (player->BSboard[r][c + a] != '~') { player->direction[3] = 0; }
	}
}

void switchPlayers(Player* currentplayer, Player* notcurrentplayer, Player* player1, Player* player2)
{
	
}
	