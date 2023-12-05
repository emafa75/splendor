#ifndef __SKILLS_H__
#define  __SKILLS_H__

#include "builder.h"
#include "game.h"
#include "market.h"
#include "token.h"
#include "skills_tokens.h"
#include "skills_builders.h"

#define MAX_SKILLS_PER_TRIGGER 3
#define NB_SKILLS_IN_GAME MAX_PLAYERS + NUM_TOKENS


typedef int (*skill_f)(struct turn_t* , void* );

struct skill_instance_t{
    void*  trigger;
    skill_f skills[MAX_SKILLS_PER_TRIGGER];
};

enum skills_id{
    TOKEN_ROB,
    TURN_ROB,
    MASTERS_HAND,
    MARKET_PANIC,
    GUILD_PANIC,
    BUILDER_FIRST_SKILL = TOKEN_ROB,
    BUILDER_LAST_SKILL = MASTERS_HAND,
    TOKEN_FIRST_SKILL = MARKET_PANIC,
    TOKEN_LAST_SKILL = GUILD_PANIC,
    NUM_SKILLS = TOKEN_LAST_SKILL + 1
};


/*
    Add skills associate to a trigger, if the trigger exist replace the skills by new one
*/
void add_skill_instance(void* trigger, skill_f skills[MAX_SKILLS_PER_TRIGGER]);

/*
    Returns the array of the all the skills for a specific pointer
*/
skill_f* skills_get_by_trigger(void* trigger);

/*
    Check is a trigger has already skills associated
*/
int has_skills(void* trigger);

/*
    Return skill_f for a specific skill id
*/
skill_f skill_by_id(enum skills_id skill);


/*
    Display the skill with skill id
*/
void skill_display(enum skills_id skill, char* prefix);

#endif
