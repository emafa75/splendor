#include "fireworks.h"
#include "cli_utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ansi_color.h"
#include "color.h"
#include "color_second_header.h"
#include "vector2.h"


void init_firework(struct firework_t* firework)
{
	struct winsize winsize = get_terminal_dimensions();
	firework->exploded = 0;
	firework->flight_duration = 10 + rand() % (30 - 10);
	firework->flight_time = 0;
	// firework->num_particules =  MIN_PARTICULES + rand() % (MAX_PARTICULES - MIN_PARTICULES);
	firework->num_particules = 70;
	firework->radius = 10;

	struct particule_t* particule;

	double start_position_x = rand() % winsize.ws_col;
	double start_position_y = winsize.ws_row - 1; //begin from bottom
	enum color_t color = rand() % NUM_COLORS;

	for (int index = 0; index < firework->num_particules; ++index)
	{
		particule = &firework->particules[index];
		particule->position.x = start_position_x;
		particule->position.y = start_position_y; 
		particule->velocity.x = 0;
		particule->velocity.y = -2; 
		particule->color = color;
	}
}

void particule_update(struct particule_t* particule, double dt)
{
	particule->position.x += particule->velocity.x * dt;
	particule->position.y += particule->velocity.y * dt;
}

void firework_display(struct firework_t* firework)
{
	struct particule_t* particule;
	char buffer[BUFFER_SIZE] = {};
	
	if (firework->flight_time > firework->flight_duration)
	{
		//the firefork is dead
		return;
	}

	double dist_to_center;
	
	for (int index = 0; index < firework->num_particules; ++index)
	{
		particule = &firework->particules[index];

		if (particule != NULL)
		{
			//get particule display 
			sprintf(buffer,"%so" CRESET, color_prefix(particule->color));

			/*
				Check if we need to display it
			*/
			if (firework->exploded)
			{
				//check if the particule is not to far away
				dist_to_center = vector2_norm2(vector2_add(vector2_opposite(particule->position), firework->center));

				if (dist_to_center < firework->radius)
				{
					
					printToCoordinates(particule->position.x, particule->position.y, buffer);
				}
			}
			else {
				printToCoordinates(particule->position.x, particule->position.y, buffer);
			}
		}
	}
}

void firework_erase(struct firework_t* firework)
{
	struct particule_t* particule;
	double dist_to_center;

	for (int index = 0; index < firework->num_particules; ++index)
	{
		particule = &firework->particules[index];

		if (particule)
		{
			if (firework->exploded)
			{
				//check if the particule is not to far away
				dist_to_center = vector2_norm2(vector2_add(vector2_opposite(particule->position), firework->center));

				if (dist_to_center < firework->radius)
				{
					printToCoordinates(particule->position.x, particule->position.y, RED " " CRESET);
				}
			}
			else {
				printToCoordinates(particule->position.x, particule->position.y, RED " " CRESET);
			}
		}
	}
}

void firework_update(struct firework_t* firework, double dt)
{
	struct particule_t* particule;
	firework->flight_time += dt;

	if (firework->flight_time > 0.6 * firework->flight_duration && (firework->exploded == 0) ) //time to explode
	{
		firework->exploded = 1;
		/*
			update velocity
		*/
		for (int index = 0; index < firework->num_particules; ++index)
		{
			particule = &firework->particules[index];

			particule->velocity.x =  (float) pow(-1, rand() % 2) * (rand() % 600) / 100;
			particule->velocity.y = (float) pow(-1, rand() % 2) * (rand() % 300) / 100;
		}
		firework->center.x = particule->position.x;
		firework->center.y = particule->position.y;
	}

	if (firework->flight_time > 0.8 * firework->flight_duration)
	{
		for (int index = 0; index < firework->num_particules; ++index)
		{
			particule = &firework->particules[index];

			particule->color = BLACK;
		}
	}

	if (firework->flight_time > 0.99 * firework->flight_duration) //firework is dead, reinit it
	{
		init_firework(firework);
	}

	/*
		Update particules
	*/

	for (int index = 0; index < firework->num_particules; ++index)
	{
		particule = &firework->particules[index];

		if (particule != NULL)
		{
			particule_update(particule, dt);
			
		}
	}
}