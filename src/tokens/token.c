
#include "token.h"
#include "game.h"
#include "token_second_header.h"
#include "skills.h"
#include "set.h"

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
	UNUSED(seed);
	int i = 0;
	enum color_t color = 0;
	enum color_t complex_token_colors[NUM_COLORS] = {};

	while (i < NUM_TOKENS)
	{
		// Create first the complex tokens
		if (i < NUM_COLORS)
		{
			complex_token_colors[(color - 1) % NUM_COLORS] = 0;
			complex_token_colors[color] = 2;
			struct set_t set_for_complex_token = {};

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

struct token_t* make_token(unsigned int index)
{
	if (index >= NUM_TOKENS)
	{
		return NULL;
	}
	return &tokens[index];
	
}