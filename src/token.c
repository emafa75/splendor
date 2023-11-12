#include "token.h"
#include <stdio.h>
#include <string.h>


struct token_t create_simple_token(enum color_t c)
{
  struct token_t new_token={};
  new_token.c[c]=1;
  return new_token;
  
}

struct token_t create_complex_token(unsigned int c[NUM_COLORS])
{
  struct token_t new_token = {};
  for (int i = 0; i < NUM_COLORS; ++i)
	{
		new_token.c[i]=c[i];
	}
  return new_token;
}

int token_equals(const struct token_t t1, const struct token_t t2)
{
  for (unsigned int index = 0; index < NUM_COLORS; ++index)
	{
		if (t1.c[index] != t2.c[index])
		{
			return 0;
		}
	}

  return 1;
}

void token_display(struct token_t t, const char* prefix)
{
	printf("%sTOKEN(", prefix);
	for (int i = 0 ; i < NUM_COLORS ; ++i)
	{
		if (t.c[i] != 0)
		{
			printf("%s=%d (%d),", color_to_short_string(i), i, t.c[i]);	  
		}
	}
  printf(")\n");
}
