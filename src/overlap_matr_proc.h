#ifndef OVERLAP_MATR_PROC_H_INCLUDED
#define OVERLAP_MATR_PROC_H_INCLUDED
#include "data_types.h"




// test input file for presence Overlap matrix
bool test_ovlp_matr(std::ifstream &);


// fill upper diagonal elements of Overlap matrix
void fill_ovlp_matr(int, Matrix &);


//get overlap matrix from input file
void get_ovlp_matr(std::ifstream &, Matrix  &);



#endif // OVERLAP_MATR_PROC_H_INCLUDED
