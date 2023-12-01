#include "skills.h"

struct skill_instance_t associated_skills[NB_SKILLS_IN_GAME] = {}; 

void add_skill_instance(void* trigger, skill_f skills_to_add[MAX_SKILLS_PER_TRIGGER])
{
    int index_skill = has_skills(trigger);
    if(index_skill >= 0) //the trigger has already associated skills
    {
       for (int index = 0; index < MAX_SKILLS_PER_TRIGGER; ++index)
       {
            associated_skills[index_skill].skills[index] = skills_to_add[index];
       }
    }else {
        /*
            Find a place to place new skill instance
        */
        for (int index =0; index < NB_SKILLS_IN_GAME; ++index)
        {
            if (associated_skills[index].trigger == NULL)
            {
                associated_skills[index].trigger = trigger;
                for (int index = 0; index < MAX_SKILLS_PER_TRIGGER; ++index)
                {
                   associated_skills[index_skill].skills[index] = skills_to_add[index];
                }
            }
        }
    }

}

int has_skills(void* trigger)
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

skill_f* get_skills(void* trigger){
    int index_skill = has_skills(trigger);

    if (index_skill < 0 )
    {
        return NULL;
    }
    return associated_skills[index_skill].skills;
}