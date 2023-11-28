#include "vector2.h"

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


void vector2_display(struct vector2_t v)
{
	printf("Vec2: (x, y) = (%f, %f)\n", v.x, v.y);
}
