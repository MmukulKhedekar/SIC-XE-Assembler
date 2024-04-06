#ifndef SYMTAB_H 
#define SYMTAB_H 

#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <array>
#include <map>

std::map<std::string, long long int> symbol_table;

void clear_symbol_table();
bool exists(std::string &LABEL);
void add_symbol(std::string &LABEL, long long int);
long long int get_locctr(std::string &LABEL);

#endif 