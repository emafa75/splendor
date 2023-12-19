#include "cli_skills.h"
#include "skills.h"
#include <stdio.h>

void cli_skill_display(char* buffer, enum skills_id skills_id, char* prefix)
{
	sprintf(buffer,"%s%s",prefix, skill_string(skills_id));
}