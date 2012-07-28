#ifndef GOL_RULE_H
#define GOL_RULE_H

/* Rules Methods */
int Rule_Carry_Forward_Cell_On_Alive(int neighbours);
int Rule_Carry_Forward_Cell_On_Dead(int neighbours);
int Rule_Carry_Forward_Cell(int cell_alive, int neighbours);
/* Rules Methods */

#endif
