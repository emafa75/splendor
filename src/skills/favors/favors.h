#ifndef __FAVORS_H__
#define __FAVORS_H__

#include "game.h"
#include "skills.h"

enum favor_id {
	NO_FAVOR,
	FAVOR_RETURN,
	FAVOR_RENEWAL,
	NUM_FAVOR
};


/*
 * take a random token from the global market
 */
int favor_return(struct turn_t* turn, const void* trigger);


/*
 *	recycle all the builders
 */
int favor_renewal(struct turn_t* turn, const void* trigger);

/*
	Get the favor skiil_f by his id
*/

skill_f favor_by_id(enum favor_id favor_id);

/*
	Display favor description
*/
void favor_display(enum favor_id favor_id, char* prefix);
#endif
