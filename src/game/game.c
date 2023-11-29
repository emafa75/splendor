#include "game.h"


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
    printf("%d", first_turn->current_player);

    /*
        Init the market
    */    
    init_market(turn_get_market(first_turn), params.market_seed);

    /*
        Init builders in game and then guild
    */
    init_builders(params.builder_seed);
    init_guild(turn_get_guild(first_turn));

    /*
        Init the players
    */
    struct player_t* players = turn_get_players(first_turn);
    for (int index = 0; index < MAX_PLAYERS; ++index)
    {
        players[index] = init_player();
    }
    
    //save this init state  
    game_save_turn(game);
    
}   

void game_save_turn(struct game_t* game)
{
    unsigned int current_turn_index = game -> current_turn_index;
    if (current_turn_index < game->num_turns)
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