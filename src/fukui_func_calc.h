#ifndef FUKUI_FUNC_CALC_H_INCLUDED
#define FUKUI_FUNC_CALC_H_INCLUDED
#include "data_types.h"



double orb_comp_fukui(Molec_Orb , Matrix , unsigned int );

void cond_to_site_fukui(vector <table_row> & , Molec_Orb , Molec_Orb , Matrix );

#endif // FUKUI_FUNC_CALC_H_INCLUDED
