
#include "token.h"
#include "color.h"
#include "token_second_header.h"
#include "set.h"
#include <stdlib.h>
#include <stdio.h>

static struct token_t tokens[NUM_TOKENS] = {};

struct token_t create_simple_token(enum color_t c)
{
	struct token_t new_token = {};
	unsigned int values[NUM_COLORS] = {};
	values[c] = 1;
	new_token.s = set_create(values);
	return new_token;
}


struct token_t create_complex_token(struct set_t s)
{
	struct token_t new_token = {};
	new_token.s = s;
 	return new_token;
}


int token_equals(const struct token_t t1, const struct token_t t2)
{
	return set_are_equals(&t1.s, &t2.s);
}

struct set_t token_get_set(struct token_t *token)
{
	return token->s;
}


void token_display(struct token_t t, const char* prefix)
{
	printf("%s", prefix);
	printf("Token(");
	set_display(&t.s);
}


void token_short_diplay(struct token_t t)
{
	set_short_display(&t.s, "T");
}

void init_tokens(unsigned int seed)
{
	srand(seed);
	int i = 0;
	enum color_t color = 0;
	enum color_t complex_token_colors[NUM_COLORS] = {};
	/*
		Reserve the seed 0 for default set
	*/
	if (seed == 0 ) {
		while (i < NUM_TOKENS)
		{
			// Create first the complex tokens
			if (i < NUM_COLORS)
			{
				complex_token_colors[(color - 1) % NUM_COLORS] = 0;
				complex_token_colors[color] = 2;
				struct set_t set_for_complex_token = {};
				set_for_complex_token.num_colors = 1;
				for (int index = 0; index < NUM_COLORS; ++index)
				{
					set_for_complex_token.c[index] = complex_token_colors[index];
				}

				tokens[i] = create_complex_token(set_for_complex_token);	 
			}
			else
			{
				tokens[i] = create_simple_token(color);
			}

			color = (color + 1) % NUM_COLORS;
			++i;
		}
	}
	else {
		while (i < NUM_TOKENS)
		{
			/*
				Choose to have a complex or simple token randomly
			*/
			int is_complex = rand() % MAX_COLORS_PER_TOKENS;
			
			tokens[i] = create_complex_token(create_random_set(is_complex + 1));

			++i;
		}
	}
}

struct token_t* make_token(unsigned int index)
{
	if (index >= NUM_TOKENS)
	{
		return NULL;
	}
	return &tokens[index];
	
}