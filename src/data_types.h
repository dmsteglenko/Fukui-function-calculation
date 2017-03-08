#ifndef DATA_TYPES_H_INCLUDED
#define DATA_TYPES_H_INCLUDED

#include <string.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <math.h>


using namespace std;




typedef vector <vector <double> > Matrix;    // defines data types for Overlap matrix

typedef struct                               // defines data types for Atomic Orbitals
{
	int atom_num;
	string atom_type;
	double coeff;
} Atomic_Orb;



typedef struct                             // defines data types for Molecular Orbitals
{
	string space;
	double eigenval;
	vector <Atomic_Orb> AO;
} Molec_Orb;



typedef struct                             // defines data types for table row
{
	int num;
	string type;
	double f_minus, f_plus, f_radical;
} table_row;



#endif // DATA_TYPES_H_INCLUDED
