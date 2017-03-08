#include "orbitals_proc.h"
#include "data_types.h"
#include "string_proc.h"



// get Number of basis functions
unsigned int get_nbas(ifstream &s_in_file)
{
    string s_str;
    vector <string> NBas;
    getline(s_in_file, s_str);

    while (strstr(s_str.c_str(), "NBasis =") == NULL)
        getline(s_in_file, s_str);
    str_parse(s_str, NBas);
    if (NBas[1]!="=") s_str=NBas[1].substr(1, NBas[1].size());
    else s_str=NBas[2];
    return atoi(s_str.c_str());
}


// homo and lumo binary pred
bool h_l_fun(Molec_Orb t_homo, Molec_Orb t_lumo)
{
    return (strstr(t_homo.space.c_str(), "O") != NULL && strstr(t_lumo.space.c_str(), "V") != NULL);
}



// Get vector of Molecular orbitals
void get_orbitals(ifstream &o_in_file, vector <Molec_Orb> &orb_vec, unsigned int t_N)
{
    string t_o_str;
    vector <string> o_columns;
    orb_vec.resize(t_N);
    for (unsigned i = 0; i<t_N; i++)                  //set size vector of all orbitals
        orb_vec[i].AO.resize(t_N);

    getline(o_in_file, t_o_str);
    while (strstr(t_o_str.c_str(), "Molecular Orbital Coefficients") == NULL)
        getline(o_in_file, t_o_str);

    o_columns.clear();
    int a = 1, b = 2, c = 3, d = 4, e = 5;
    int t_number=0;
    string t_type;

    unsigned int column_count=0;
    unsigned int blocks = 0;
    bool flag=false;

    while ( blocks < t_N / 5)
    {

        for (unsigned i = 0; i<t_N+2; i++)
        {
            getline(o_in_file, t_o_str);
            if (!(strstr(t_o_str.c_str(), "Density Matrix:") == NULL))
            {
                flag=true;
                break;
            }
            str_parse(t_o_str, o_columns);

            if (i == 0)
            {
                if (o_columns.size()>0) a = atoi(o_columns[0].c_str());
                if (o_columns.size()>1) b = atoi(o_columns[1].c_str());
                if (o_columns.size()>2) c = atoi(o_columns[2].c_str());
                if (o_columns.size()>3) d = atoi(o_columns[3].c_str());
                if (o_columns.size()>4) e = atoi(o_columns[4].c_str());
            }

            if (i == 1)
            {
                if (o_columns.size()>0) orb_vec[a].space = o_columns[0];
                if (o_columns.size()>1) orb_vec[b].space = o_columns[1];
                if (o_columns.size()>2) orb_vec[c].space = o_columns[2];
                if (o_columns.size()>3) orb_vec[d].space = o_columns[3];
                if (o_columns.size()>4) orb_vec[e].space = o_columns[4];

                column_count = o_columns.size();
            }

            if (i == 2)
            {
                if (o_columns.size()>2) orb_vec[a].eigenval = str_to_dbl(o_columns[2]);
                if (o_columns.size()>3) orb_vec[b].eigenval = str_to_dbl(o_columns[3]);
                if (o_columns.size()>4) orb_vec[c].eigenval = str_to_dbl(o_columns[4]);
                if (o_columns.size()>5) orb_vec[d].eigenval = str_to_dbl(o_columns[5]);
                if (o_columns.size()>6) orb_vec[e].eigenval = str_to_dbl(o_columns[6]);
            }

            if (i>2)
            {
                if (o_columns.size() == 9)
                {
                    t_number = atoi(o_columns[1].c_str());
                    t_type = o_columns[2];
                }
                orb_vec[a].AO[i - 2].atom_num = orb_vec[b].AO[i - 2].atom_num = orb_vec[c].AO[i - 2].atom_num = orb_vec[d].AO[i - 2].atom_num = orb_vec[e].AO[i - 2].atom_num = t_number;
                orb_vec[a].AO[i - 2].atom_type = orb_vec[b].AO[i - 2].atom_type = orb_vec[c].AO[i - 2].atom_type = orb_vec[d].AO[i - 2].atom_type = orb_vec[e].AO[i - 2].atom_type = t_type;

                if (column_count > 0) orb_vec[a].AO[i - 2].coeff = str_to_dbl(o_columns[o_columns.size() - column_count + 0]);
                if (column_count > 1) orb_vec[b].AO[i - 2].coeff = str_to_dbl(o_columns[o_columns.size() - column_count + 1]);
                if (column_count > 2) orb_vec[c].AO[i - 2].coeff = str_to_dbl(o_columns[o_columns.size() - column_count + 2]);
                if (column_count > 3) orb_vec[d].AO[i - 2].coeff = str_to_dbl(o_columns[o_columns.size() - column_count + 3]);
                if (column_count > 4) orb_vec[e].AO[i - 2].coeff = str_to_dbl(o_columns[o_columns.size() - column_count + 4]);


            }

            o_columns.clear();
        }

        if (flag) break;
        ++blocks;
    }

}

