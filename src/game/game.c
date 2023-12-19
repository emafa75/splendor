#include "game.h"
#include "ansi_color.h"
#include "guild.h"
#include "market.h"
#include "players.h"
#include "skills.h"
#include "can_buy.h"
#include "token_second_header.h"
#include "builder.h"
#include "favors.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void init_game(struct game_t* game, struct game_parameters params)
{
	/*
		Get the first turn to init it
	*/

	struct turn_t* first_turn = game_get_turn(game, 0);

	/*
		Apply basic params
	*/
	game->current_turn_index = 0; //use index 0 to save the initialisation
	game->num_turns = params.max_turns;
	first_turn->points_to_win = params.points_to_win;
	first_turn->display = params.display;
	first_turn->num_player = MIN(params.num_player, MAX_PLAYERS);
	first_turn->params = params;


	/*
		Init the market
	*/	
	struct market_t* market = turn_get_market(first_turn);
	*market = create_default_market(); 
	init_tokens(params.market_seed);
	init_market(market , params.market_seed);
	init_tokens_skills();

	/*
		Init builders in game and then guild
	*/
	init_builders(params.builder_seed);
	init_guild(turn_get_guild(first_turn));
	init_builder_skills();

	/*
		Init the players
	*/
	int num_player = first_turn->num_player;
	struct player_t* players = turn_get_players(first_turn);

	for (int index = 0 ; index < num_player ; ++index)
	{
		players[index] = init_player();
		players[index].id = index;
	}

	//Init the random for the rest of the game 
	srand(params.random_seed);

	/*
		Init first player
	*/
	first_turn->current_player = get_random_player(num_player) ;

	/*
		Init the first player without favor
	*/
	struct player_t* first_player = turn_get_current_player(first_turn);		
	player_set_favor(first_player,0);
	


	//save this init state  
	game_save_turn(game);
}


void game_save_turn(struct game_t* game)
{
	unsigned int current_turn_index = game -> current_turn_index;

	if (current_turn_index <= game->num_turns)
	{ 
		memcpy(game_get_turn(game, current_turn_index + 1), game_get_current_turn(game), sizeof(struct turn_t));	   
	}

	++game->current_turn_index;
	struct turn_t* new_turn = game_get_current_turn(game);
	new_turn->id = game->current_turn_index;
}


void next_player(struct turn_t* current_turn)
{
	unsigned int current_player = current_turn->current_player;
	int num_player = current_turn->num_player;

	current_player = (current_player + 1) % num_player;
	current_turn->current_player = current_player;
}


int has_won(struct turn_t *current_turn)
{
	int num_player = turn_get_num_player(current_turn);

	for (int index = 0 ; index < num_player ; ++index)
	{
		struct player_t* player = &current_turn->players[index];
		int points_to_win = current_turn->points_to_win;
		if (player_get_points(player) >= points_to_win)
			return 1;
		
	}
	return 0;
}

int get_winner(struct turn_t *current_turn)
{
	int id_max_points = 0;
	int points_to_win = current_turn->points_to_win;
	struct player_t* players = current_turn->players;
	int num_player = turn_get_num_player(current_turn);

	//get index of the player with the max of points
	for (int index = 0 ; index < num_player ; ++index)
	{
		struct player_t* player = &current_turn->players[index];
		int player_point = player_get_points(player);

		if (player_point >= points_to_win)
			return index;

		if (player_point > player_get_points(&players[id_max_points])) 
		{
			id_max_points = index;
		}
	}

	//Check if the player with the max points has the same amount of points than an other player
	int max_points = player_get_points(&players[id_max_points]);

	for (int index = 0 ; index < num_player ; ++index)
	{
		if((index != id_max_points) && (max_points == players[index].current_point))
			return TIE;
	}

	return id_max_points;
}


struct turn_t* game_get_turn(struct game_t* game, int index)
{
	return &game->turns[index];
}


struct turn_t* game_get_current_turn(struct game_t* game)
{
	return game_get_turn(game, game->current_turn_index);
}


struct market_t* turn_get_market(struct turn_t* turn)
{
	return &turn->market;
}


struct guild_t* turn_get_guild(struct turn_t* turn)
{
	return &turn->guild;
}


struct player_t* turn_get_players(struct turn_t* turn)
{
	return turn->players;
}


struct player_t* turn_get_current_player(struct turn_t* turn)
{
	return &turn_get_players(turn)[turn->current_player];
}


int turn_get_current_player_index(struct turn_t* turn)
{
	return turn->current_player;
}


unsigned int get_random_player(int num_player)
{
	return  rand() % num_player;
}


void turn_display(struct turn_t* turn)
{
	/*
		Display player's inventory
	*/
	printf("\n");
	struct player_t* players = turn_get_players(turn);
	int num_player = turn_get_num_player(turn);

	for (int index = 0 ; index < num_player ; ++index)
	{
		struct player_t* player = &players[index];

		printf("Inventory of player id.%d\n", index);
		player_display_inventory(player);
		printf("\n");
	}

	/*
		Display the market
	*/
	printf("\n");
	printf("Market : \n");
	market_display(turn_get_market(turn));

	/*
		Display Builders avaible to hire
	*/
	printf("\n");
	printf("Game Guild :\n");
	guild_display(turn_get_guild(turn));
}


struct turn_statistics turn_play(struct turn_t* current_turn)
{
	/*
		Display
	*/
	int display = current_turn->display;

	/*
		If we need a display
	*/
	FILE * output;

	if (display)
	{
		output = stdout;
	}
	else
	{
		output = stdout; /* patch for thor */
	}
	/*
		Create statistic container
	*/

	struct turn_statistics stats = {};

	/*
		Get place where to stock the action of the current turn
	*/
	struct market_t* market = turn_get_market(current_turn);
	struct guild_t* guild = turn_get_guild(current_turn); 
	struct player_t* current_player = turn_get_current_player(current_turn);
	int player_index = turn_get_current_player_index(current_turn);


	/*
		If the player has a favor he use it (or not)
	*/
	int favors = player_get_favor(current_player);

	if (favors)
	{
		enum favor_id favor_id = rand() % NUM_FAVOR; //if NO_FAVOR then the player decided to not use it

		if(favor_id != NO_FAVOR)
		{
			skill_f favor_function = favor_by_id(favor_id);
			favor_function(current_turn, current_player /* unused */);
			DISPLAY(display, favor_display(favor_id, HCYN "Player used "));
			DISPLAY(display, printf("\n" CRESET));

			/*
				Remove the favor
			*/
			player_set_favor(current_player,player_get_favor(current_player) - 1); 

			/*
				Add statistic
			*/
			++stats.used_favor;
		}
		else
		{
			DISPLAY(display, printf("Player had favor but he decided to keep it\n"));
		}
	}

	/*
		Take a random decision and check if it's possible to hire a builder
	*/
	enum choice random_choice = rand() % 100; 
	struct builder_t* builder_to_buy = select_affordable_builder(guild, current_player);

	if ((random_choice <= 50) && (builder_to_buy != NULL)) 
	{
		stats.choice = HIRE;
		/*
			The player choosed to hire a builder and is able to do so
		*/
		DISPLAY(display,fprintf(output, HCYN "Player id.%d choosed to hire\n" CRESET, player_index));
		player_pay_builder(market, current_player, builder_to_buy);
		player_hire_builder(guild, current_player, builder_to_buy);

		/*
			Execute the skill associate to the builder
		*/
		skill_exec(current_turn, builder_to_buy);
		DISPLAY(display, trigger_display_skill(builder_to_buy));

		/*
			Add statistics
		*/
		stats.used_skill += trigger_num_skills(builder_to_buy); 
	}
	else if (random_choice <= 90)
	{
		stats.choice = PICK;
		//change random choice to fit with the current action
		// if ((random_choice == HIRE) && (builder_to_buy == NULL)) 
		// 	random_choice = PICK ;

		/*
			The player choosed to pick a token or is unable to hire a builder (default choice)
		*/
		/*
			Choose how many token he wants to take (1 to 3), never more than the number of available token and never more that what he can take.
		*/
		int num_token_in_inventory = market_num_tokens(&player_get_ressources(current_player)->market);
		int num_token_to_pick =  1 + rand() % 3; 
		num_token_to_pick = MIN(num_token_to_pick, market_num_tokens(market));
		num_token_to_pick = MIN(num_token_to_pick, PLAYER_MAX_TOKENS - num_token_in_inventory); //take never more than what he is able to pick

		DISPLAY(display, fprintf(output, HCYN "Player id.%d choosed to pick %d token(s)\n"  CRESET, player_index, num_token_to_pick));

		/*
			Get the index of the first available token to match with the number of token that the player wanted to pick
		*/
		int index_first_token_to_pick = market_get_linked_tokens(market, num_token_to_pick);

		/*
			Pick the number of token he wants from the market (no choice, pick one per one in order)
			If his choice is impossible, he skip his turn;
		*/

		if (index_first_token_to_pick == -1 && num_token_to_pick != 0) // impossible choice 
		{
			DISPLAY(display, fprintf(output, RED "Player id.%d choosed to pick too much tokens, not enough linked token available. Turn skipped.\n" CRESET , player_index));
		}
		else
		{
			struct token_t* picked_tokens[num_token_to_pick]; //stock picked token to execute skills after the turn

			for (int index = 0 ; index < num_token_to_pick ; ++index)
			{
				struct token_t* picked_token = market->tokens[index_first_token_to_pick+index] ;
				picked_tokens[index] = picked_token;
				player_pick_token(market, current_player, picked_token);
			}

			/*
				Execute associated skills
			*/
			for (int index = 0 ; index < num_token_to_pick ; ++index)
			{
				skill_exec(current_turn, picked_tokens[index]);
				DISPLAY(display, trigger_display_skill(picked_tokens[index]));

				/*
					Add statistics
				*/
				stats.used_skill += trigger_num_skills(picked_tokens[index]); 
			}	
		}

		/*
			Add statistics
		*/
		stats.num_picked_tokens += num_token_to_pick;
		if (num_token_to_pick == 0)
		{
			++stats.forced_skip;
		}
	}
	else 
	{
		stats.choice = SKIP;
		DISPLAY(display, fprintf(output, HCYN "Player id.%d skipped his turn\n" CRESET, player_index));
	}

	/*
		End of the turn, display player inventory, game market and game guild to follow the game
	*/
	DISPLAY(display, fprintf(output, "\n"));
	DISPLAY(display, fprintf(output, "Current inventory for player id.%d : \n", player_index));
	DISPLAY(display, player_display_inventory(current_player));
	DISPLAY(display, fprintf(output, "\n"));

	DISPLAY(display, fprintf(output, "Market after turn :\n"));
	DISPLAY(display, market_display(market)) ;

	DISPLAY(display, fprintf(output,"Game Guild  : \n"));
	DISPLAY(display, guild_display(guild));
	DISPLAY(display, fprintf(output, "\n"));

	/*
		Add statistics
	*/

	// stats.choice = random_choice;

	// fclose(output);

	return stats;
}


struct game_statistics game_play(struct game_t *game, int display)
{
	/*
		If we need a display
	*/
	FILE * output;

	if (display)
	{
		output = stdout;
	}
	else
	{
		output = stdout; /* Patch for Thor*/
	}

	/*
		Create statistics for the game
	*/
	struct game_statistics game_stats = {};

	struct turn_t* current_turn = game_get_current_turn(game);

	/*
		Game loop
	*/
	while (!has_won(current_turn) && game->current_turn_index <= game->num_turns)
	{	
		current_turn = game_get_current_turn(game);
		//int turn_index = game->current_turn_index;

		/*
			Play turn
		*/
		DISPLAY(display,fprintf(output, BBLU "════════════════════════" BRED "  TURN %d  " BBLU "════════════════════════════\n" CRESET, turn_get_id(current_turn)));
		struct turn_statistics turn_stats = turn_play(current_turn);
		DISPLAY(display, fprintf(output, BBLU "══════════════════════════════════════════════════════════════\n" CRESET));
		DISPLAY(display, fprintf(output, "\n"));

		/*
			Update game statistics
		*/
		++game_stats.choices[turn_stats.choice];
		++game_stats.nb_turns;

		game_stats.forced_skip += turn_stats.forced_skip;
		game_stats.num_picked_tokens += turn_stats.num_picked_tokens;
		game_stats.used_favor += turn_stats.used_favor;
		game_stats.used_skill += turn_stats.used_skill;

		/*
			Save the state of the turn and give turn to the next player 
		*/
		game_save_turn(game);

		next_player(game_get_current_turn(game));
	}
	game_stats.result = (has_won(current_turn));

	return game_stats;
}


void game_stats_display(struct game_statistics game_stats)
{
	float forced_skip_tun = game_stats.forced_skip;
	float nb_turns = game_stats.nb_turns;
	float skipped_turns = (forced_skip_tun / nb_turns) * 100;

	printf("Played turns : " BYEL "%d " CRESET "including " RED "%d" CRESET " skipped turn (" RED "%d%%" CRESET ")\n\
Number of picked tokens: " BYEL "%d " CRESET "\n\
Number of favors used : " BYEL "%d " CRESET "\n\
Number of skills executed : " BYEL "%d " CRESET " \n\
Number of pick turn : " BYEL "%d" CRESET "\n\
Number of hire turn : " BYEL "%d" CRESET "\n\
Number of skipped turn : " BYEL "%d\n" CRESET,
	game_stats.nb_turns,
	game_stats.forced_skip,
	(int) skipped_turns,
	game_stats.num_picked_tokens,
	game_stats.used_favor,
	game_stats.used_skill,
	game_stats.choices[PICK],
	game_stats.choices[HIRE],
	game_stats.choices[SKIP]
	);
}


int turn_get_num_player(struct turn_t* turn)
{
	return turn->num_player;
}


unsigned int turn_get_id(struct turn_t* turn)
{
	return turn->id;
}


struct game_parameters* turn_get_params(struct turn_t* turn)
{
	return &turn->params;
}
