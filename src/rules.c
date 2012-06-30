#include "rules.h"

int Rule_Carry_Forward_Alive_Cell(int neighbours)
{
	return neighbours == 2 || neighbours == 3;
}

int Rule_Carry_Forward_Dead_Cell(int neighbours)
{
	return neighbours == 3;
}

int Rule_Carry_Forward_Cell(int cell_alive, int neighbours)
{
	return cell_alive
		? Rule_Carry_Forward_Alive_Cell(neighbours)
		: Rule_Carry_Forward_Dead_Cell(neighbours);
}
