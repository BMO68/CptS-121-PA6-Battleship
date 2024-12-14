/* this file executse the battleship program */

#include "Header.h"

int main(void)
{
	FILE* inputstream = NULL; FILE* outputstream = NULL;

	outputstream = fopen("battleship.log", "w");

	char hit = '*'; //*z
	//char ship; //depends, 'C' for Carrier, 'B' for Battleship, 'R' for Cruiser, 'S' for Submarine, 'D' for Destroyer //figure this out later
	char miss = 'm'; //m
	char water = '~'; //~
	Player player1;
	Player player2;
	Stats Player1;
	Stats Player2;

	initialize_player(&player1, 1); // = { CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER }; 
	initialize_player(&player2, 2);

	Player* current_player = &player1;
	Player* not_current_player = &player2; 

	 //  = { 'C', 'B', 'R', 'S', 'D' };
	initialize_hit_board(&player1);
	initialize_hit_board(&player2);
	initialize_stats(&Player1);
	initialize_stats(&Player2); 

	

	srand((unsigned int)time(NULL));   

	//Player currentPlayer = player1; //figure out dice roll later

	//print_board(&players[current_player]); //saving this for later 

	prompt_placement(current_player, &player1, &player2);
	
	int val = roll_for_turn(current_player, not_current_player, &player1, &player2);   //figure out how to switch between players  

	if (val == 1) { current_player = &player1; }
	if (val == 2) { current_player = &player2; }

	int condition = 0;

	while (condition == 0)
	{
		shooting(current_player, not_current_player, &player1, &player2, outputstream);

		//switchPlayers(current_player, not_current_player, &player1, &player2);
		if (current_player == &player1)
		{
			current_player = &player2;
			not_current_player = &player1;
		}
		else
		{
			if (current_player == &player2)
			{
				current_player = &player1;
				not_current_player = &player2;
			}
		}

		condition = win_condition(&player1, &player2); 

	}

	update_stats(&Player1, &player1, &player1, &player2, condition);
	update_stats(&Player2, &player2, &player1, &player2, condition);

	fprintf(outputstream, "Player 1 Stats:\n");
	log_stats(&Player1, outputstream);
	fprintf(outputstream, "Player 2 Stats:\n");
	log_stats(&Player2, outputstream);

	if (condition < 0)
	{
		system("cls");
		printf("Player 1 Wins!\n");
	}
	if (condition > 0)
	{
		system("cls");
		printf("Player 2 Wins!\n");
	}

	fclose(outputstream);
	

	return 0;
}