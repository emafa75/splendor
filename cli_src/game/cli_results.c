#include "cli_results.h"
#include "cli_utils.h"
#include "fireworks.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "ansi_color.h"
#include "utils.h"
#include "vector2.h"

#define NUM_FIREWORK 8 

int cli_display_results(struct turn_t* last_turn)
{
	char buffer[BUFFER_SIZE] = {};
	struct winsize winsize = get_terminal_dimensions();

	/*
		Get winner of the game
	*/

	int winner_index = get_winner(last_turn);
	sprintf(buffer,BBLU "════════════════════════" BRED " Player id.%d won " BLU "════════════════════════" CRESET, winner_index);
	printToCoordinates(winsize.ws_col/2 - 31, 0 , buffer); //31 to center

	/*
		Firework launch
	*/
	struct firework_t fireworks[NUM_FIREWORK] = {};
	struct vector2_t bottom_right = {winsize.ws_col, winsize.ws_row};
	struct vector2_t top_left = vector2_ones();


	for (int index = 0; index < NUM_FIREWORK; ++index)
	{
		init_firework(&fireworks[index], top_left, bottom_right);
	}
	
	char ch = 0;
	clear_terminal();
	terminal_cursor(0);

	/*
		Disable echo
	*/
	system("stty -echo");
	sprintf(buffer,RED "Player id.%d won" CRESET, winner_index);
	while(ch != 'q' && ch != 'p' && ch != 68) {
		for (int index = 0; index < NUM_FIREWORK; ++index)
		{ 
			firework_erase(&fireworks[index]);
			firework_update(&fireworks[index], DT);
			firework_display(&fireworks[index]);
			
		}
		
		usleep(20000);
		cli_popup(buffer);

		ch = getkey_unlocked();		
		if (ch == '\033')
		{
			getch();	//skip next caract [
			ch = getch();	
		}
	}

	terminal_cursor(1);

	system("stty echo"); /* reenable echo*/

	return ch;
}