
#include "test_can_buy.h"



int test_utils()
{
	int test_passed = 0;

	if (test_can_buy())
	{
		printf(GRN "Test can_buy passed\n" CRESET);
		++test_passed;
	}
	if (test_select_affordable_builder())
	{	
		printf(GRN "Test select_affordable_builder passed\n" CRESET);
		++test_passed;
	}
	return test_passed;
}

int test_can_buy()
{
	// struct builder_t builder = {.lvl=1, .pts=2, .requires={BLUE, 2}, .provides={BLUE, 2}};
	return 1;
}

int test_select_affordable_builder()
{
	return 1;
}
