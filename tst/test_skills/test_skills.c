#include "test_skills.h"
#include "builder.h"
#include "game.h"
#include "guild.h"
#include "market.h"
#include "players.h"
#include "set.h"
#include "skills_builders.h"
#include "skills_tokens.h"
#include "token.h"
#include <stdio.h>


static struct game_parameters game_parameters ={
	.builder_seed = 0,
	.market_seed = 0,
	.random_seed = 0,
	.max_turns = 10,
	.points_to_win = 20
} ;

int test_skills()
{
	int test_passed = 0;

	if(test_skill_guild_panic())
	{
		printf(GRN "Test skill_guild_panic passed\n" CRESET);
		++test_passed;
	}
	if(test_skill_market_panic())
	{
		printf(GRN "Test skill_market_panic passed\n" CRESET);
		++test_passed;
	}
	if(test_skill_masters_hand())
	{
		printf( GRN "Test skill_masters_hand passed\n" CRESET);
		++test_passed;
	}
	if(test_skill_token_rob())
	{
		printf(GRN "Test skill_token_rob passed\n" CRESET);
		++test_passed;
	}

	if(test_skill_turn_rob())
	{
		printf(GRN "Test skill_turn_rob passed\n" CRESET);
		++test_passed;
	}

	return test_passed;
}

int test_skill_guild_panic()
{
	/*
		Init test game
	*/
	struct game_t game = {};
	init_game(&game, game_parameters);

	struct turn_t* turn = game_get_current_turn(&game);
	struct guild_t* game_guild = turn_get_guild(turn);

	/*
		Get available builders to compare with the guild after skill execute
	*/
	struct available_builders old_available_builders = game_guild->available_builders;

	/*
		Execute the skill
	*/
	skill_guild_panic(turn,turn /* unused */);

	struct available_builders new_available_builders = game_guild->available_builders;

	/*
		Compare the two states
	*/
	int num_different_builder = 0;

	for (int index = 0; index < MAX_BUILDERS; ++index)
	{
		if (old_available_builders.builders[index] != new_available_builders.builders[index])
		{
			++num_different_builder;
		}
	}

	if (num_different_builder == 0)
	{
		fprintf(stderr, RED "test_skill_guild_panic: the guild panic didn't change\n" CRESET);
		return 0;
	}

	if (num_different_builder != 1)
	{
		fprintf(stderr, RED "test_skill_guild_panic: the guild panic change more than one builder\n" CRESET);
		return 0;
	}
	return 1;
}

int test_skill_market_panic()
{
	/*
		Init test game
	*/
	struct game_t game = {};
	init_game(&game, game_parameters);

	struct turn_t* turn = game_get_current_turn(&game);
	struct market_t* game_market = turn_get_market(turn);

	/*
		Give a token from the market to simulate the action of picking a token with market_panic skill	
	*/
	struct player_t* current_player = turn_get_current_player(turn);
	int token_index = market_get_linked_tokens(game_market, 1);
	struct token_t* picked_token = game_market->tokens[token_index];

	player_pick_token(game_market, current_player, picked_token);

	/*
		Store old market to compare it after skill execution
	*/
	struct market_t old_market = *game_market;

	skill_market_panic(turn, turn /* unused */);

	struct market_t new_market = * game_market;

	/*
		Compare the two state of the market
	*/
	int market_changes = 0;
	for (int index = 0; index < NUM_TOKENS ; ++index)
	{
		if (old_market.tokens[index] != new_market.tokens[index])
		{
			++market_changes ; 
		}
	}

	if (market_changes == 0)
	{
		fprintf(stderr, RED "test_skill_market_panic: no change in the market\n" CRESET);
		return 0;
	}

	if (market_changes != 2)
	{
		fprintf(stderr, RED "test_skill_market_panic: more than one token has been replace\n" CRESET);
		return 0;
	}
	return 1;
}

int test_skill_masters_hand()
{
	/*
		Init test game
	*/
	struct game_t game = {};
	init_game(&game, game_parameters);

	struct turn_t* turn = game_get_current_turn(&game);
	struct market_t* game_market = turn_get_market(turn);
	struct guild_t* game_guild = turn_get_guild(turn);

	/*
		Give a builder from the game_guild to simulate the action of picking a builder with master_hand skill	
	*/
	struct player_t* current_player = turn_get_current_player(turn);
	struct builder_t* picked_builder = game_guild->available_builders.builders[ rand() % game_guild->available_builders.n_builders_available ];

	player_hire_builder(game_guild, current_player, picked_builder);

	int skill_status = skill_masters_hand(turn, picked_builder);

	if (skill_status == 0)
	{
		fprintf(stdout, YEL "test_skill_masters_hand: no token provided from the builder in the market\n" CRESET);
		fprintf(stdout, "Game market : \n");
		market_display(game_market);
		builder_display(picked_builder, "Picked Builder : \n");
		return 1;
	}

	if (market_num_tokens(&player_get_ressources(current_player)->market) > 1)
	{
		fprintf(stderr, RED "test_skill_masters_hand: too much tokens picked by the player\n" CRESET);
		return 0;
	}

	if (market_num_tokens(&player_get_ressources(current_player)->market) == 0)
	{
		fprintf(stderr, RED "test_skill_masters_hand: no token picked by the player\n" CRESET);
		fprintf(stdout, "Game market : \n");
		market_display(game_market);
		builder_display(picked_builder, "Picked Builder : \n");
		return 0;
	}

	/*
		Get the picked token in player's inventory
	*/

	struct token_t* picked_token = player_get_ressources(current_player)->market.tokens[0]; //Normally stock in first slot from player market

	struct set_t zero = set_zero();

	struct set_t provided = builder_provides(picked_builder);

	struct set_t intersection = set_inter(&picked_token->s, &provided);

	if (set_are_equals(&intersection, &zero))
	{
		fprintf(stderr, RED "test_skill_masters_hand: picked token is not provide by the picked builder\n" CRESET);
		token_display(*picked_token, "Picked token : \n");
		builder_display(picked_builder, "Picked builder : \n");
		return 0;
	}


	
	return 1;
}

int test_skill_token_rob()
{
	/*
		Init test game
	*/
	struct game_t game = {};
	init_game(&game, game_parameters);

	struct turn_t* turn = game_get_current_turn(&game);
	struct market_t* game_market = turn_get_market(turn);

	/*
		Test if the skill do nothing when no token  are in player's inventory
	*/
	if (skill_token_rob(turn, turn /* unused */) != 0)
	{
		fprintf(stderr, RED "test_skill_token_rob: skill is doing something while no token in player inventory\n" CRESET);
		return 0;
	}

	struct player_t* players = turn_get_players(turn);

	/*
		Give a token to every player so that we can rob it 
	*/
	int num_player = turn_get_num_player(turn);

	for (int index = 0; index < num_player; ++index)
	{
		int token_index = market_get_linked_tokens(game_market, 1);
		struct token_t* picked_token = game_market->tokens[token_index];
		player_pick_token(game_market, &players[index], picked_token);
	}
	
	/*
		Rob a token and check if a token has been robbed
	*/

	struct player_t* current_player = turn_get_current_player(turn);

	skill_token_rob(turn,turn /* unused*/);

	if (market_num_tokens(&player_get_ressources(current_player)->market) != 2)
	{
		fprintf(stderr, RED "test_skill_token_rob: player robbed no token\n" CRESET);
		return 0;
	}
	return 1;
}

int test_skill_turn_rob()
{
	/*
		Init test game
	*/
	struct game_t game = {};
	init_game(&game, game_parameters);

	struct turn_t* turn = game_get_current_turn(&game);
	struct player_t* current_player = turn_get_current_player(turn);

	skill_turn_rob(turn, turn /* unused */);

	struct player_t* new_player = turn_get_current_player(turn);

	if (new_player == current_player)
	{
		fprintf(stderr, RED "test_skill_turn_rob: next player is still the same\n" CRESET);
		return 0;
	}

	return 1;
}