#ifndef __TOKEN_SECOND_HEADER_H__
#define __TOKEN_SECOND_HEADER_H__

#include <stdio.h>
#include <string.h>

#include "set.h"
#include "token.h"
#include "ansi_color.h"
#include "color.h"

#include "color_second_header.h"

/*
    Print very short display for token
*/
void token_short_diplay(struct token_t t);

struct set_t token_get_set(struct token_t *token);



#endif
