#include "game.h"
#include "guild.h"
#include "market.h"
#include "players.h"
#include "skills.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "can_buy.h"
#include "token_second_header.h"
#include "builder.h"
#include "favors.h"
/*
	Used to use a display function only if _x is true
*/
#define DISPLAY(_x, _y)\
	(_x) ? (_y) : UNUSED(_x);

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

	/*
		Init first player
	*/
	first_turn->current_player = get_random_player(params.random_seed);
	struct player_t* first_player = turn_get_current_player(first_turn);		
	player_set_favor(first_player,0);

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
	struct player_t* players = turn_get_players(first_turn);
	for (int index = 0; index < MAX_PLAYERS; ++index)
	{
		players[index] = init_player();
	}
	
	//Init the random for the rest of the game 
	srand(params.random_seed);

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
	++ game->current_turn_index ;
}

void next_player(struct turn_t* current_turn)
{
	unsigned int current_player = current_turn->current_player;
	current_player = (current_player + 1) % MAX_PLAYERS;
	current_turn->current_player = current_player;
}

int has_won(struct turn_t *current_turn)
{
	for (int index = 0; index < MAX_PLAYERS; ++index)
	{
		struct player_t* player = &current_turn->players[index];
		int points_to_win = current_turn->points_to_win;
		if (player_get_points(player) >= points_to_win)
		{
			return 1;
		}
		
	}
	return 0;
}

int get_winner(struct turn_t *current_turn)
{
	int id_max_points = 0;
	int points_to_win = current_turn->points_to_win;
	struct player_t* players = current_turn->players;
	
	//get index of the player with the max of points
	for (int index = 0; index < MAX_PLAYERS; ++index)
	{
		struct player_t* player = &current_turn->players[index];
		int player_point = player_get_points(player);

		if (player_point >= points_to_win)
		{
			return index;
		}

		if (player_point > player_get_points(&players[id_max_points])) 
		{
			id_max_points = index;
		}
	}

	//Check if the player with the max points has the same amount of points than an other player
	int max_points = player_get_points(&players[id_max_points]);

	for (int index = 0; index < MAX_PLAYERS; ++index)
	{
		if((index != id_max_points) && (max_points == players[index].current_point))
		{
			return TIE;
		}
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

unsigned int get_random_player(int random_seed)
{
	srand(random_seed);
	return  rand() % MAX_PLAYERS;
}

void turn_display(struct turn_t* turn)
{
	/*
		Display player's inventory
	*/
	printf("\n");
	struct player_t* players = turn_get_players(turn);
	for (int index = 0; index < MAX_PLAYERS; ++index)
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

void turn_play(struct turn_t* current_turn, int display)
{
	/*
		If we need a display
	*/
	FILE * output;
	if (display)
	{
		output = stdout;
	}
	else {
		output = stdout; /* patch for thor */
	}

	/*
		Get place where to stock the action of the current turn
	*/
	struct market_t* market = turn_get_market(current_turn);
	struct guild_t* guild = turn_get_guild(current_turn); 
	struct player_t* current_player = turn_get_current_player(current_turn);
	int player_index = turn_get_current_player_index(current_turn);

	DISPLAY(display, fprintf(output, "══════════════════════════════════════════════════════════════════════\n"));

	/*
		If the player has a favor he use it (or not)
	*/

	int favors = player_get_favor(current_player);

	if(favors)
	{
		enum favor_id favor_id = rand() % NUM_FAVOR; //if NO_FAVOR then the player decided to not use it
		if(favor_id != NO_FAVOR)
		{
			skill_f favor_function = favor_by_id(favor_id);
			favor_function(current_turn, current_player /* unused */);
			DISPLAY(display, favor_display(favor_id, "Player used "));
			DISPLAY(display, printf("\n"));
			/*
				Remove the favor
			*/
			player_set_favor(current_player,player_get_favor(current_player) - 1); 
		}
		else {
			DISPLAY(display, printf("Player had favor but he decided to keep it\n"));
		}
	}

	/*
		Take a random decision and check if it's possible to hire a builder
	*/
	enum choice random_choice = rand() % NUM_CHOICE; 
	struct builder_t * builder_to_buy = select_affordable_builder(guild, current_player);


	if ((random_choice == HIRE) && (builder_to_buy != NULL)) 
	{
		/*
			The player choosed to hire a builder and is able to do so
		*/
		DISPLAY(display,fprintf(output, "Player id.%d choosed to hire\n", player_index));
		player_pay_builder(market, current_player, builder_to_buy);
		player_hire_builder(guild, current_player, builder_to_buy);
		/*
			Execute the skill associate to the builder
		*/
		skill_exec(current_turn, builder_to_buy);
		DISPLAY(display, trigger_display_skill(builder_to_buy));
	}
	else 
	{
		/*
			The player choosed to pick a token or is unable to hire a builder (default choice)
			If he choose to pick 0 token, he skip his turn
		*/
		/*
			Choose how many token he wants to take (0 to 3), never more than the number of available token.
		*/
		int num_token_to_pick = rand() % 4; 
		num_token_to_pick = MIN(num_token_to_pick, market_num_tokens(market));
		DISPLAY(display, fprintf(output, "Player id.%d choosed to pick %d token(s)\n" , player_index, num_token_to_pick));

		/*
			Get the index of the first available token to match with the number of token that the player wanted to pick
		*/
		int index_first_token_to_pick = market_get_linked_tokens(market, num_token_to_pick);

		/*
			Pick the number of token he wants from the market (no choice, pick one per one in order)
			If his choice is impossible, he skip his turn;
		*/

		if(index_first_token_to_pick == -1 && num_token_to_pick != 0) // impossible choice 
		{
			DISPLAY(display, fprintf(output, "Player id.%d choosed to pick too much tokens, not enough linked token available. Turn skipped.\n" , player_index));
		}else{
			
			struct token_t* picked_tokens[num_token_to_pick]; //stock picked token to execute skills after the turn

			for (int index = 0; index < num_token_to_pick ; ++index)
			{
				struct token_t* picked_token = market->tokens[index_first_token_to_pick+index] ;
				picked_tokens[index] = picked_token;
				player_pick_token(market, current_player, picked_token);
			}

			/*
				Execute associated skills
			*/
			for (int index = 0; index < num_token_to_pick ; ++index)
			{
				skill_exec(current_turn, picked_tokens[index]);
				DISPLAY(display, trigger_display_skill(picked_tokens[index]));
			}
			
		}
	}

	/*
		End of the turn, display player inventory, game market and game guild to follow the game
	*/

	DISPLAY(display,fprintf(output, "Current inventory for player id.%d : \n", player_index));
	DISPLAY(display, player_display_inventory(current_player));
	
	DISPLAY(display, fprintf(output, "══════════════════════════════════════════════════════════════════════\n"));
	DISPLAY(display,fprintf(output, "Market after turn :\n"));
	DISPLAY(display, market_display(market)) ;
	DISPLAY(display,fprintf(output,"Game Guild  : \n"));
	DISPLAY(display, guild_display(guild));

	//fclose(output);
}

void game_play(struct game_t *game, int display)
{
	/*
		If we need a display
	*/
	FILE * output;
	if (display)
	{
		output = stdout;
	}
	else {
		output = stdout; /* Patch for Thor*/
	}

	struct turn_t* current_turn = game_get_current_turn(game);

	/*
		Game loop
	*/
	while (!has_won(current_turn) && game->current_turn_index <= game->num_turns)
	{	
		
		current_turn = game_get_current_turn(game);
		int turn_index = game->current_turn_index;

		/*
			Play turn
		*/
		DISPLAY(display,fprintf(output, "Turn n°%d\n", turn_index));
		turn_play(current_turn, display );
		DISPLAY(display, fprintf(output, "\n"));

		/*
			Give turn to the next player and save the state of the turn
		*/
		next_player(current_turn);
		game_save_turn(game);

	}
	//fclose(output);
}