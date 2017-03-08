#include "data_types.h"
#include "string_proc.h"

void str_parse(string t_str, vector <string> &t_tokens)   //string parsing into tokens
{
    char * temp_str=new char[t_str.length()+1];
    strcpy(temp_str, t_str.c_str());
    char * p_chr=strtok(temp_str, " ");

    while(p_chr!=NULL)
       {
            t_tokens.push_back(p_chr);
            p_chr=strtok(NULL, " ");

       }

    delete[] temp_str;
}


//convert string to double number
double str_to_dbl(string t_string)
{
	replace_if(t_string.begin(), t_string.end(), [](char t){return t == 'D'; }, 'E');
	char *pEnd;
	return strtod(t_string.c_str(), &pEnd);
}

