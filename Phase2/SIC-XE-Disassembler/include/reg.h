#ifndef REG_H 
#define REG_H 

#include <map>

std::map<char, int> reg;

void add_registers(char c, int x);
void initialise_registers();

#endif 