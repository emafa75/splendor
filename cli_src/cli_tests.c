#include "cli_tests.h"
#include "cli_utils.h"
#include "fireworks/fireworks.h"
#include "vector2.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_FIREWORK 5

void cli_tests(void)
{	
	struct firework_t fireworks[NUM_FIREWORK] = {};
	struct winsize winsize = get_terminal_dimensions();
	struct vector2_t bottom_right = {winsize.ws_col/2, winsize.ws_row};
	bottom_right.x = 91;
	bottom_right.y = 45;
	struct vector2_t top_left = vector2_add(vector2_zero(), vector2_ones());
	top_left = vector2_add(top_left, vector2_ones());
	top_left = vector2_add(top_left, vector2_ones());
	srand(time(NULL));

	for (int index = 0; index < NUM_FIREWORK; ++index)
	{
		init_firework(&fireworks[index], top_left, bottom_right);
	}
	
	clear_terminal();
	terminal_cursor(0);
	vector2_display(bottom_right);

	/*
		Disable echo
	*/
	system("stty -echo");
	cli_wrap_box(top_left, bottom_right);
	while(getkey_unlocked() != 'q') {
		for (int index = 0; index < NUM_FIREWORK; ++index)
		{ 
			firework_erase(&fireworks[index]);
			firework_update(&fireworks[index], DT);
			firework_display(&fireworks[index]);
		}
		usleep(20000);
		
	}
	terminal_cursor(1);

	system("stty echo"); /* reenable echo*/
	
}


