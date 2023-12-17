#include "cli_builders.h"

#include "builder.h"
#include "cli_set.h"
#include "cli_utils.h"

#include <stdio.h>
#include <string.h>


void cli_builder_display(struct vector2_t position , const struct builder_t* builder, char* prefix)
{
	char buffer[200] = {};
	char tmp_buffer[100] = {};
	struct set_t builder_require = builder_requires(builder);
	struct set_t builder_provide = builder_provides(builder);
	
	sprintf(buffer,"%sBuilder(lvl=%d, points=%d, ", \
			prefix, \
			builder_level(builder) + 1, \
			builder_points(builder)
			);

	cli_set_short_display(tmp_buffer, &builder_require, "requires=");
	strcat(buffer, tmp_buffer);
	
	sprintf(tmp_buffer, ", ");
	strcat(buffer, tmp_buffer);

	cli_set_short_display(tmp_buffer, &builder_provide, "provides=");
	strcat(buffer, tmp_buffer);

	printToCoordinates(position.x, position.y, buffer);

}