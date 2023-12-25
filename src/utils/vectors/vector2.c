#include "vector2.h"
#include "cli_utils.h"

#include <math.h>
#include <stdio.h>


struct vector2_t VECTOR2_ZERO = {0, 0};
struct vector2_t VECTOR2_ONES = {LINE_SIZE, LINE_SIZE};
struct vector2_t VECTOR2_UP = {0, -LINE_SIZE};
struct vector2_t VECTOR2_DOWN = {0, LINE_SIZE};
struct vector2_t VECTOR2_LEFT = {-LINE_SIZE, 0};
struct vector2_t VECTOR2_RIGHT = {LINE_SIZE, 0};


struct vector2_t vector2_zero(void) {return VECTOR2_ZERO;}
struct vector2_t vector2_ones(void) {return VECTOR2_ONES;}
struct vector2_t vector2_up(void) {return VECTOR2_UP;}
struct vector2_t vector2_down(void) {return VECTOR2_DOWN;}
struct vector2_t vector2_left(void) {return VECTOR2_LEFT;}
struct vector2_t vector2_right(void) {return VECTOR2_RIGHT;}


int vector2_equals(struct vector2_t v1, struct vector2_t v2)
{
	return v1.x == v2.x && v1.y == v2.y;
}


struct vector2_t vector2_add(struct vector2_t v1, struct vector2_t v2)
{
	struct vector2_t out = {};

	out.x = v1.x + v2.x;
	out.y = v1.y + v2.y;

	return out;
}


struct vector2_t vector2_opposite(struct vector2_t v)
{
	struct vector2_t out = {};

	out.x = -v.x;
	out.y = -v.y;

	return out;
}


double vector2_norm(struct vector2_t v)
{
	return sqrt(v.x * v.x + v.y * v.y);  // sqrt(x**2 + y**2)
}

double vector2_norm2(struct vector2_t v)
{
	return sqrt( 0.25 *v.x * v.x + v.y * v.y);
}
void vector2_display(struct vector2_t v)
{
	printf("Vec2: (x, y) = (%f, %f)\n", v.x, v.y);
}

int vector2_is_inside(struct vector2_t vector, struct vector2_t top_left, struct vector2_t bottom_right)
{	
	/* Doesn't work for the left and above section because of the doubles*/
	// return (vector.x > top_left.x && vector.x < bottom_right.x && vector.y > top_left.y && vector.y < bottom_right.y) ;

	if (vector.x - top_left.x < 1 )
		return 0;
	if (vector.x >= bottom_right.x )
		return 0;
	if (vector.y - top_left.y < 1)
		return 0;
	if (vector.y >= bottom_right.y)
		return 0;
	return 1;
}
