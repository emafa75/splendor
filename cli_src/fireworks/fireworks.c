#include "fireworks.h"
#include "cli_utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ansi_color.h"
#include "color.h"
#include "color_second_header.h"
#include "vector2.h"


void init_firework(struct firework_t* firework, struct vector2_t top_left, struct vector2_t bottom_right)
{
	/* max positions */
	firework->top_left = top_left;
	firework->bottom_right = bottom_right;

	firework->exploded = 0;
	
	firework->flight_time = 0;
	firework->num_particules =  MIN_PARTICULES + rand() % (MAX_PARTICULES - MIN_PARTICULES);
	//firework->num_particules = 70;
	firework->radius = 10;

	struct particule_t* particule;

	double start_position_x = top_left.x + rand() % (int) (bottom_right.x - top_left.x);
	double start_position_y = bottom_right.y; //begin from bottom
	enum color_t color = 1 + rand() % (NUM_COLORS - 1); //no black

	for (int index = 0; index < firework->num_particules; ++index)
	{
		particule = &firework->particules[index];
		particule->position.x = start_position_x;
		particule->position.y = start_position_y; 
		particule->velocity.x = 0;
		particule->velocity.y = -2; 
		particule->color = color;
	}
	/* Setup flight duration */
	double max_duration = (bottom_right.y - top_left.y) / ((-firework->particules[0].velocity.y) * 0.6) ; //explode at 60% of the time
	double min_duration = 0.3 * max_duration;
	firework->flight_duration = min_duration + rand() % (int) ((0.9 * max_duration) - min_duration);
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
			if ( vector2_is_inside(particule->position, firework->top_left, firework->bottom_right)) //is in the display box
			{
				//get particule display 
				sprintf(buffer,"%s●" CRESET, color_prefix(particule->color));

				/*
					Check if we need to display it
				*/
				if (firework->exploded)
				{
					//check if the particule is not to far away
					dist_to_center = vector2_norm2(vector2_add(vector2_opposite(particule->position), firework->center));

					if (dist_to_center < firework->radius)
					{
						
						print_to_coordinates(particule->position.x, particule->position.y, buffer);
					}
				}
				else {
					print_to_coordinates(particule->position.x, particule->position.y, buffer);
				}
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
			if ( vector2_is_inside(particule->position, firework->top_left, firework->bottom_right)) //is in the display box
			{
				if (firework->exploded)
				{
					//check if the particule is not to far away
					dist_to_center = vector2_norm2(vector2_add(vector2_opposite(particule->position), firework->center));

					if (dist_to_center < firework->radius)
					{
						print_to_coordinates(particule->position.x, particule->position.y, RED " " CRESET);
					}
				}
				else {
					print_to_coordinates(particule->position.x, particule->position.y, RED " " CRESET);
				}
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
		firework_erase(firework);
		init_firework(firework, firework->top_left, firework->bottom_right);
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