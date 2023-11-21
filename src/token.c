
#include "token.h"
#include "token_second_header.h"


struct token_t create_simple_token(enum color_t c)
{
  struct token_t new_token={};
	unsigned int values[NUM_COLORS] = {};
	values[c] = 1;

	new_token.s = set_create(c);
  return new_token;
}


struct token_t create_complex_token(unsigned int c[NUM_COLORS])
{
  struct token_t new_token = {};
	new_token.s = set_create(c);
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
	set_display(&t.s);
}


// TODO: change t.s.c
void token_short_diplay(struct token_t t)
{
	printf("T(");
	for (enum color_t i = 0; i < NUM_COLORS; ++i)
	{
		if(t.s.c[i] != 0)
		{	
			// if(t.c[i]>1 )
			// {
			// 	printf("*");
			// }
			printf("%s%s=%d%s", color_prefix(i), color_to_short_string(i), t.c[i], CRESET);
		}
	}
	printf(")");
}
