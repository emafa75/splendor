#include "cli_token.h"
#include "cli_set.h"
#include "cli_utils.h"
#include "set.h"
#include "token_second_header.h"
#include <stdio.h>
#include <string.h>
#include "skills.h"
#include "cli_skills.h"

void cli_token_display(struct vector2_t position, struct token_t* token, char* prefix)
{
	char buffer[BUFFER_SIZE]= {};
	char tmp_buffer[2 * BUFFER_SIZE ] = {};

	struct set_t token_set = token_get_set(token);
	cli_set_short_display(buffer, &token_set, "Token(");

	/* Skills */

	if (has_skills(token))
	{
		sprintf(tmp_buffer, "%s %s", buffer, "skill(s)=");
		
		/* Replace it in buffer */
		strcpy(buffer, tmp_buffer);

		enum skills_id* skills = skills_get_by_trigger(token);
		for (int index = 0; index < MAX_SKILLS_PER_TRIGGER; ++index)
		{
			if (skills[index] != NO_SKILL)
			{
				cli_skill_display(tmp_buffer,skills[index],(index != 0) ? ", " : "");
				strcat(buffer, tmp_buffer);
			}
		}
	}

	sprintf(tmp_buffer, "%s%s)", prefix, buffer);

	/* Replace it in buffer */
	strcpy(buffer, tmp_buffer);

	print_to_coordinates(position.x, position.y, buffer);
}