#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include <stdio.h>
#include <math.h>

#include "token.h"
#include "market.h"


struct vector2_t {
	int x;
	int y;
};


struct vector2_t VECTOR2_ZERO = {0, 0};
struct vector2_t VECTOR2_UP = {0, -1};
struct vector2_t VECTOR2_DOWN = {0, 1};
struct vector2_t VECTOR2_LEFT = {-1, 0};
struct vector2_t VECTOR2_RIGHT = {1, 0};


/*
 *  Returns 1 if v1 == v2
 *		0 otherwise
 */
int vector2_equals(struct vector2_t v1, struct vector2_t v2);


/*
 *  Returns v1 + v2
 */
struct vector2_t vector2_add(struct vector2_t v1, struct vector2_t v2);


/*
 *  Returns v1 + v2
 */
struct vector2_t vector2_add(struct vector2_t v1, struct vector2_t v2);


/*
 *  Returns -v
 */
struct vector2_t vector2_opposite(struct vector2_t v);


/*
 *  Returns |v|
 */
double vector2_norm(struct vector2_t v);
#endif
