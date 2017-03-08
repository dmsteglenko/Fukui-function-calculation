#include "printed_line_types.h"

void print_lt_1(ofstream & t_out_file)
{
	for (int i = 0; i<80; i++)
		t_out_file << "-";
	t_out_file << endl;
}

void print_lt_2(ofstream & t_out_file)
{
	for (int i = 0; i<80; i++)
		t_out_file << "=";
	t_out_file << endl;
}

void print_blank(ofstream & t_out_file)
{
	for (int i = 0; i<4; i++)
		t_out_file << endl;
}

