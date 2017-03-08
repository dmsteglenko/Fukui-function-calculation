#include "fukui_func_calc.h"
#include "data_types.h"



double orb_comp_fukui(Molec_Orb t_Orbital, Matrix t_ovlp_matr, unsigned int t_mu)             //calculates orbital component of Fukui function
{
    double sum = 0;

    for (unsigned int nu = 1; nu < t_Orbital.AO.size(); nu++)
        if (nu != t_mu) sum += t_Orbital.AO[nu].coeff * t_ovlp_matr[t_mu][nu];

    return(pow(t_Orbital.AO[t_mu].coeff, 2) + t_Orbital.AO[t_mu].coeff * sum);
}


void cond_to_site_fukui(vector <table_row> &t_tbl_row, Molec_Orb t_c_HOMO, Molec_Orb t_c_LUMO, Matrix t_c_ovlp_matr)
{
    unsigned int t = 1;
    unsigned int N = t_c_HOMO.AO.size();
    table_row tmp;

    tmp.num = 0;
    tmp.f_minus = tmp.f_plus = tmp.f_radical = 0;


    while (t < N)
    {
        if (t_c_HOMO.AO[t].atom_num != tmp.num)
        {
            if (t>1)
            {
                tmp.f_radical = (tmp.f_minus + tmp.f_plus) / 2;
                t_tbl_row.push_back(tmp);
            }
            tmp.num = t_c_HOMO.AO[t].atom_num;
            tmp.type = t_c_HOMO.AO[t].atom_type;
            tmp.f_minus = tmp.f_plus = tmp.f_radical = 0;
            tmp.f_minus += orb_comp_fukui(t_c_HOMO, t_c_ovlp_matr, t);
            tmp.f_plus += orb_comp_fukui(t_c_LUMO, t_c_ovlp_matr, t);

        }
        else
        {
            tmp.f_minus += orb_comp_fukui(t_c_HOMO, t_c_ovlp_matr, t);
            tmp.f_plus += orb_comp_fukui(t_c_LUMO, t_c_ovlp_matr, t);
        }

        t++;
        if (t == N)
        {
            tmp.f_radical = (tmp.f_minus + tmp.f_plus) / 2;
            t_tbl_row.push_back(tmp);
        }
    }
}
