#include "overlap_matr_proc.h"
#include "data_types.h"
#include "string_proc.h"

bool test_ovlp_matr(std::ifstream &tm_in_file)
{
	std::string tm_str;
	bool beg_matr, end_matr;
	beg_matr = end_matr = false;
	while (!tm_in_file.eof())
	{
		getline(tm_in_file, tm_str);
		if (strstr(tm_str.c_str(), "*** Overlap ***") != NULL) beg_matr = true;
		if (strstr(tm_str.c_str(), "*** Kinetic Energy ***") != NULL) end_matr = true;
	}
	tm_in_file.clear();
	tm_in_file.seekg(0, tm_in_file.beg);
	return (beg_matr && end_matr);
}



void fill_ovlp_matr(int t_size, Matrix &t_ovlp_matr)    // fill upper diagonal elements of Overlap matrix
{
	for (int i = 1; i < t_size - 1; i++)
	for (int j = i + 1; j < t_size; j++)
		t_ovlp_matr[i][j] = t_ovlp_matr[j][i];
}



void get_ovlp_matr(ifstream &sm_in_file, Matrix  &sm_ovlp_matr)                //get overlap matrix from file
{
	string str;
	vector <string> columns;
	int m = 1;               // m-strings
	int a = 1, b = 2, c = 3, d = 4, e = 5;   //subcolumns in overlap matrix

	getline(sm_in_file, str);

	while (strstr(str.c_str(), "*** Overlap ***") == NULL)    //search begining Overlap matrix
		getline(sm_in_file, str);

	getline(sm_in_file, str);

	while (strstr(str.c_str(), "*** Kinetic Energy ***") == NULL)  //strstr(str.c_str(),"*** Kinetic Energy ***")==NULL
	{
		columns.clear();

		str_parse(str, columns);

		if (str[6] == ' ')
		{
			if (columns.size()>0) a = atoi(columns[0].c_str());
			if (columns.size()>1) b = atoi(columns[1].c_str());
			if (columns.size()>2) c = atoi(columns[2].c_str());
			if (columns.size()>3) d = atoi(columns[3].c_str());
			if (columns.size()>4) e = atoi(columns[4].c_str());
			columns.clear();
		}
		else
		{
			m = atoi(columns[0].c_str());
			if (columns.size()>1)	sm_ovlp_matr[m][a] = str_to_dbl(columns[1]);
			if (columns.size()>2)	sm_ovlp_matr[m][b] = str_to_dbl(columns[2]);
			if (columns.size()>3)	sm_ovlp_matr[m][c] = str_to_dbl(columns[3]);
			if (columns.size()>4)	sm_ovlp_matr[m][d] = str_to_dbl(columns[4]);
			if (columns.size()>5)	sm_ovlp_matr[m][e] = str_to_dbl(columns[5]);
		}

		getline(sm_in_file, str);
	}

}
