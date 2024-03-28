#ifndef SYMTAB_H 
#define SYMTAB_H 

#include "imports.h"

void clear_symbol_table();
bool exists(std::string &LABEL);
void add_symbol(std::string &LABEL, std::string &LOCCTR);
std::string get_locctr(std::string &LABEL);

#endif 