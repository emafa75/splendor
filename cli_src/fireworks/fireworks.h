#ifndef __FIREWORKS_H__
#define __FIREWORKS_H__

#include "color.h"
#include "vector2.h"

#define MAX_PARTICULES 150
#define MIN_PARTICULES 50
#define DT 0.1

struct particule_t
{
	struct vector2_t position;
	struct vector2_t velocity;
	//add color
	enum color_t color;
};

struct firework_t
{
	struct particule_t particules[MAX_PARTICULES];
	int num_particules; 
	double flight_duration; // time of the full flight
	double flight_time;	// time of flight 
	float radius;
	struct vector2_t center;
	int exploded;
	struct vector2_t top_left;
	struct vector2_t bottom_right; //use to reinit the firework
};

/*
	Init the firework with random options in the sqare define by the two vectors
*/
void init_firework(struct firework_t* firework, struct vector2_t top_left, struct vector2_t bottom_right);

/*
	Update particule position
*/
void particule_update(struct particule_t* particule, double dt);

/*
	Display firework
*/
void firework_display(struct firework_t* firework);

/*
	Erase firework
*/
void firework_erase(struct firework_t* firework);

/*
	Update firework
*/
void firework_update(struct firework_t* firework, double dt);
#endif