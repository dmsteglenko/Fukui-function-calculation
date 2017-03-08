#// fukui.cpp : Defines the entry point for the console application.
//
#include <iomanip>

#include "overlap_matr_proc.h"
#include "data_types.h"
#include "string_proc.h"
#include "orbitals_proc.h"
#include "fukui_func_calc.h"
#include "printed_line_types.h"


using namespace std;



ofstream out_file;
ifstream in_file;





int main(int argc, char* argv[])
{
	Molec_Orb HOMO, LUMO;                        // defines frontier orbitals
	vector <Molec_Orb> Orbitals;                 // defines all molecular orbitals

	string path(argv[1]);

	in_file.open(path.c_str(), ios::in);
	if (!in_file)
	{
		cerr << "File " << path << " can't be opened" << endl;
		exit(1);
	}


	if (!test_ovlp_matr(in_file))
	{
		cerr << "Can't find overlap matrix" << endl;
		exit(1);
	}

	path[path.size() - 3] = 'f';
	path[path.size() - 2] = 'u';
	path[path.size() - 1] = 'k';

	unsigned int N = 1;                                   // matrix size
	N += get_nbas(in_file);
	Matrix overlap_matr;

	overlap_matr.resize(N);                     // set matrix size
	for (unsigned int i = 0; i < N; i++)
		overlap_matr[i].resize(N);



	get_ovlp_matr(in_file, overlap_matr);       // get overlap matrix "overlap_matr"


	fill_ovlp_matr(N, overlap_matr);            // fill empty positions

	get_orbitals(in_file, Orbitals, N);

	in_file.close();

	vector <Molec_Orb>::iterator it=adjacent_find(Orbitals.begin(), Orbitals.end(), h_l_fun);
	HOMO = *it;
	LUMO=*(++it);


	vector <table_row> table;                  // defines table of Fukui functions

	cond_to_site_fukui(table, HOMO, LUMO, overlap_matr);      // calculate values and fills table of Fukui functions

	out_file.open(path.c_str(), ios::out);
	out_file.precision(4);


	out_file << "These descriptors of reactivity are defined in the framework of DFT." << endl << endl;
	out_file << "Software implementation corresponds to the way described in the article :"  << endl;
	out_file << "Renato R. Contreras, Patricio Fuentealba, Marcelo Galván, Patricia Pérez. " << endl;
	out_file << "\"A direct evaluation of regional Fukui functions in molecules\". ";
	out_file << "Chemical Physics Letters, V. 304, (1999), p. 405-413." << endl;


	print_blank(out_file);

	out_file << "       Global reactivity descriptors" << endl;
	print_lt_2(out_file);

	out_file << " mu     =" << setw(10) << right << fixed << 27.211*((HOMO.eigenval+LUMO.eigenval)/2) << "  eV" << \
	"                         ! defined as (E_homo + E_lumo)/2" << endl << endl;

	out_file << " eta    =" << setw(10) << right << fixed << 27.211*((LUMO.eigenval - HOMO.eigenval)) << "  eV" << \
	"                         ! defined as (E_lumo - E_homo)" << endl << endl;

	out_file << " omega  =" << setw(10) << right << fixed << 27.211* \
	(pow((HOMO.eigenval+LUMO.eigenval)/2, 2)/(2*(LUMO.eigenval - HOMO.eigenval))) << "  eV" << \
	"                         ! defined as (mu^2)/(2*eta)" << endl;

	print_lt_2(out_file);
	print_blank(out_file);

	out_file << "       Table of condensed to atom Fukui functions" << endl;

	print_lt_1(out_file);

	out_file << "   Atom    " << "    f(-)" << "        f(+)" << "        f(0)" << endl;
	print_lt_2(out_file);

	double norm_f_plus, norm_f_minus, norm_f_radical;
	norm_f_plus=norm_f_minus=norm_f_radical=0;

	for (unsigned int i = 0; i < table.size(); i++)
	{
	norm_f_minus+=table[i].f_minus;
	norm_f_plus+=table[i].f_plus;
	norm_f_radical+=table[i].f_radical;

	out_file << " " << setw(6) << left << table[i].num;
	out_file << setw(4) << table[i].type;
	out_file << setw(9) << fixed << right << table[i].f_minus;
	out_file << setw(12) << fixed << right << table[i].f_plus;
	out_file << setw(12) << fixed << right << table[i].f_radical << endl;
	}

	print_lt_2(out_file);
	out_file << "Norm:         " << norm_f_minus << "      " << norm_f_plus << "      " << norm_f_radical << endl;

	print_blank(out_file);

	out_file << "For the global descriptors of reactivity see:" << endl;
	out_file << "Robert G. Parr, László v. Szentpály, Shubin Liu. \"Electrophilicity Index\". " << endl;
	out_file << "J. Am. Chem. Soc., 1999, 121 (9), pp 1922–1924"  << endl << endl;

	out_file.close();



	return 0;

}
