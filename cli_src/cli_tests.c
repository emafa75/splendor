#include "cli_tests.h"
#include "cli_utils.h"
#include "fireworks/fireworks.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_FIREWORK 4

void cli_tests(void)
{	
	struct firework_t fireworks[NUM_FIREWORK] = {};

	srand(0);

	for (int index = 0; index < NUM_FIREWORK; ++index)
	{
		init_firework(&fireworks[index]);
	}
	
	char ch = 0;
	clear_terminal();
	terminal_cursor(0);

	while(getkey_unlocked() != 'q') {
		for (int index = 0; index < NUM_FIREWORK; ++index)
		{ 
			firework_erase(&fireworks[index]);
			firework_update(&fireworks[index],0.1);
			firework_display(&fireworks[index]);
		}
		usleep(20000);
		
	}
	terminal_cursor(1);
	
}


