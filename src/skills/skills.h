#ifndef __SKILLS_H__
#define  __SKILLS_H__

#include "builder.h"
#include "game.h"
#include "token.h"

#define MAX_SKILLS_PER_TRIGGER 3
#define NB_SKILLS_IN_GAME MAX_PLAYERS + NUM_TOKENS


typedef int (*skill_f)(struct turn_t* , void* );



struct skill_instance_t{
    void*  trigger;
    skill_f skills[MAX_SKILLS_PER_TRIGGER];
};

/*
    Add skills associate to a trigger, if the trigger exist replace the skills by new one
*/
void add_skill_instance(void* trigger, skill_f skills[MAX_SKILLS_PER_TRIGGER]);

/*
    Returns the array of the all the skills for a specific pointer
*/
skill_f* get_skills(void* trigger);

/*
    Check is a trigger has already skills associated
*/
int has_skills(void* trigger);

#endif