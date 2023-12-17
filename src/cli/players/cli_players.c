#include "cli_players.h"
#include "ansi_color.h"
#include "cli_builders.h"
#include "cli_utils.h"
#include "players.h"
#include "vector2.h"
#include <stdio.h>
#include "cli_token.h"

struct vector2_t cli_player_display_inventory(struct vector2_t position, struct player_t* player)
{


	char buffer[BUFFER_SIZE] = {};

	/*
		Display header
	*/
	sprintf(buffer, BOLD " ── Inventory of player " CRESET RED "id.%d " CRESET BOLD "──" CRESET, player_get_id(player));
	printToCoordinates(position.x,position.y, buffer);

	/* Jump line*/
	cli_jump_line(&position);

	/*
		Points
	*/
	unsigned int points = player_get_points(player);
	sprintf(buffer,BOLD "Point(s) : " HYEL "%d" CRESET , points );

	printToCoordinates(position.x, position.y, buffer);

	/* Jump a line */
	cli_jump_line(&position);

	/*
		Favors
	*/
	unsigned int favor = player_get_favor(player);
	sprintf(buffer, favor ?  BOLD "Favor(s) : " CRESET HYEL "%d\n\n"  CRESET: BOLD "Favor(s) : " CRESET WHT "No favor\n\n" CRESET , favor );
	printToCoordinates(position.x, position.y, buffer);


	/* Jump a line */
	cli_jump_line(&position);

	struct ressources* player_ressources = player_get_ressources(player);
	
	/*
		Tokens
	*/
	printToCoordinates(position.x, position.y, BOLD "Tokens : " CRESET);
	cli_jump_line(&position);

	for (int index = 0; index < NUM_TOKENS; ++index)
	{
		struct token_t* token = player_ressources->market.tokens[index];
		if(token)
		{
			cli_token_display(position, token, " --- ");
			cli_jump_line(&position);
		}
	}
	if(market_num_tokens(&player_ressources->market) == 0 )
	{
		printToCoordinates(position.x, position.y, WHT " --- No token" CRESET);
		cli_jump_line(&position);
	}
	
	/* Jump line */
	cli_jump_line(&position);

	/*
		Builders
	*/

	printToCoordinates(position.x, position.y, BOLD "Builders :" CRESET);
	cli_jump_line(&position);

	for (unsigned int index = 0; index < MAX_BUILDERS; ++index)
	{
		if(player->ressources.guild.builders[index]) {
			cli_builder_display(position, player_ressources->guild.builders[index]," --- ");
			cli_jump_line(&position);
		}
	}
	if (guild_nb_builder(&player_ressources->guild) == 0)
	{
		printToCoordinates(position.x, position.y, WHT " --- No builder" CRESET);
		cli_jump_line(&position);
	}

	cli_jump_line(&position);
	
	return position;
}