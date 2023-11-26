#ifndef __VICTOIRE_H__
#define __VICTOIRE_H__

#include <stdio.h>
#include <math.h>

#include "token.h"
#include "market.h"

struct board;

struct vector2;


int vector2_equals(struct vector2 v1, struct vector2 v2);

struct board available_to_board(struct available_tokens *available_tokens);


void board_display();
#endif
