#include "rules.h"

int Rule_Carry_Forward_Cell_On_Alive(int neighbours)
{
	return neighbours == 2 || neighbours == 3;
}

int Rule_Carry_Forward_Cell_On_Dead(int neighbours)
{
	return neighbours == 3;
}
