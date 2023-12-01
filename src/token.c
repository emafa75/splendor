
#include "token.h"
#include "token_second_header.h"
#include "skills.h"

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
