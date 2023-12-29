#include "skills.h"
#include "ansi_color.h"
#include "skills_builders.h"
#include "skills_tokens.h"

#include <stdio.h>

struct skill_instance_t associated_skills[NB_SKILLS_IN_GAME] = {}; 

skill_f skills_functions[NUM_SKILLS] = {
	NULL,
	skill_token_rob,
	skill_turn_rob,
	skill_gentry_master,
	skill_masters_hand,
	skill_market_panic,
	skill_favor_rob,
	skill_guild_panic,
};


char *skills_strings[NUM_SKILLS] = {
	"no skill",
	"token_rob",
	"turn_rob",
	"gentry master",
	"masters_hand",
	"market_panic",
	"favor_rob",
	"guild_panic"
};

void reset_associated_skills()
{
	struct skill_instance_t null_instance = {};

	for (int index = 0; index < NB_SKILLS_IN_GAME; ++index)
	{
		associated_skills[index] = null_instance;
	}
}

void add_skill_instance(void* trigger, enum skills_id skills_to_add[MAX_SKILLS_PER_TRIGGER])
{
	int index_skill = is_associate_to_a_skill(trigger);
	if(index_skill >= 0) //the trigger has already associated skills
	{
		associated_skills[index_skill].nb_skill = 0;
		for (int index = 0; index < MAX_SKILLS_PER_TRIGGER; ++index)
		{
			associated_skills[index_skill].skills[index] = skills_to_add[index];
			if(skills_to_add[index] != NO_SKILL)
			{
				++associated_skills[index_skill].nb_skill;
			}
		}
	   return;
	}else {
		/*
			Find a place to place new skill instance
		*/
		for (int index = 0; index < NB_SKILLS_IN_GAME; ++index)
		{
			if (associated_skills[index].trigger == NULL)
			{
				
				associated_skills[index].trigger = trigger;
				for (int skill_index = 0; skill_index < MAX_SKILLS_PER_TRIGGER; ++skill_index)
				{
				   associated_skills[index].skills[skill_index] = skills_to_add[skill_index];
				   if(skills_to_add[skill_index] != NO_SKILL)
				   {
						++associated_skills[index].nb_skill;
				   }
				}
				return;
			}
		}
	}

}

int is_associate_to_a_skill(const void* trigger)
{
	for (int index = 0; index < NB_SKILLS_IN_GAME; ++index)
	{
		if(associated_skills[index].trigger == trigger && trigger != NULL)
		{
			return index;			
		}

	}
	return -1;
}

enum skills_id* skills_get_by_trigger(const void* trigger){
	int index_skill = is_associate_to_a_skill(trigger);

	if (index_skill < 0 )
	{
		return NULL;
	}
	return associated_skills[index_skill].skills;
}

skill_f skill_by_id(enum skills_id skill)
{
	return skills_functions[skill];
}


char* skill_string(enum skills_id skill_id)
{
	return skills_strings[skill_id];
}

void skill_display(enum skills_id skill, char* prefix)
{
	printf("%s%s", prefix, skill_string(skill));
}

void trigger_display_skill(const void* trigger)
{
	if (!has_skills(trigger))
	{
		return;
	}
	enum skills_id* trigger_skills = skills_get_by_trigger(trigger);

	for (int index = 0; index < MAX_SKILLS_PER_TRIGGER; ++index)
	{
		if (trigger_skills[index] != NO_SKILL)
		{
			skill_display(trigger_skills[index], HCYN "");
			printf(" skill execute\n" CRESET);
		}
	}
}

int has_skills(const void *trigger)
{
	int skill_instance_index = is_associate_to_a_skill(trigger);
	if (skill_instance_index < 0)
	{
		return 0;
	}
	if (associated_skills[skill_instance_index].skills[0] != NO_SKILL) //check if the first associated skill is a real skill
	{
		return 1;
	}
	return 0;
}

void skill_exec(struct turn_t *turn, const void* trigger)
{
	if (!has_skills(trigger))
	{
		return;
	}
	enum skills_id* trigger_skills = skills_get_by_trigger(trigger);

	for (int index = 0; index < MAX_SKILLS_PER_TRIGGER; ++index)
	{
		if (trigger_skills[index] != NO_SKILL)
		{
			skill_f skill_function = skill_by_id(trigger_skills[index]);
			skill_function(turn, trigger);
		}
	}
}

int trigger_num_skills(const void* trigger)
{
	int skill_instance_index = is_associate_to_a_skill(trigger);

	if (skill_instance_index < 0)
	{
		return 0;
	}

	return associated_skills[skill_instance_index].nb_skill;

}
