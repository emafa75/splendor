#ifndef __FAVORS_H__
#define __FAVORS_H__

#include "game.h"

enum favor_id {
	NO_FAVOR,
	FAVOR_RETURN,
	FAVOR_RENEWAL,
	NUM_FAVOR
};


/*
 *
 */
int favor_return(struct turn_t* turn, const void* trigger);


/*
 *
 */
int favor_renewal(struct turn_t* turn, const void* trigger);
#endif
