#ifndef __TOKEN_H__
#define __TOKEN_H__

#include "color.h"

/** The number of tokens in play. */
#ifndef NUM_TOKENS
  #define NUM_TOKENS 25
#endif

/** A type describing a token, that is to say a set of different
    colors. */
struct token_t {
  unsigned int c[NUM_COLORS];
};

/** Builder for tokens. */
struct token_t create_simple_token(enum color_t c);
struct token_t create_complex_token(unsigned int c[NUM_COLORS]);

/** Compares the two tokens `t1` and `t2` and returns a boolean
    telling whether they are equal or different. */
int token_equals(const struct token_t t1, const struct token_t t2);

/** Display the token on the stdout, after a possible prefix.
    Example : token_display(g, "    - ") displays on the screen :
    - Token(B=1,W=5)
*/
void token_display(struct token_t t, const char* prefix);

#endif // __TOKEN_H__
