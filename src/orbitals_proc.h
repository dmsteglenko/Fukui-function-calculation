#ifndef ORBITALS_PROC_H_INCLUDED
#define ORBITALS_PROC_H_INCLUDED
#include "data_types.h"



unsigned int get_nbas(ifstream &);

bool h_l_fun(Molec_Orb , Molec_Orb );

void get_orbitals(ifstream &, vector <Molec_Orb> &, unsigned int );

#endif // ORBITALS_PROC_H_INCLUDED
