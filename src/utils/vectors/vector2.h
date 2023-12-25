#ifndef __VECTOR2_H__
#define __VECTOR2_H__


struct vector2_t {
	double x;
	double y;
};


struct vector2_t vector2_zero(void);
struct vector2_t vector2_ones(void);
struct vector2_t vector2_up(void);
struct vector2_t vector2_down(void);
struct vector2_t vector2_left(void);
struct vector2_t vector2_right(void);


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


/*
 *  Returns |v| 2, adapted to the text size (give more importance to the x axe)
 */
double vector2_norm2(struct vector2_t v);



/*
 *  Display a vector2 coordinates
 */
void vector2_display(struct vector2_t v);

/*
	Returns 1 if the vector is inside the sqare describe by two corners
	Strict (borders not included)
*/
int vector2_is_inside(struct vector2_t vector, struct vector2_t top_left, struct vector2_t bottom_right);
#endif
