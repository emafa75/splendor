#include "skills_builders.h"
#include "market.h"
#include "set.h"

void skill_masters_hand(struct turn_t* current_turn)
{
	struct set_t provides = builder_provides(builder_bought);
	unsigned int* colors_provides = set_get_colors(&provides);

	struct available_tokens* available_tokens = get_available_tokens();
}





