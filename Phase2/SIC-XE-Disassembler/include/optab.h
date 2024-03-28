#ifndef OPTAB_H
#define OPTAB_H

#include <string>
#include <map>

// contains the mnemonic for a given opcode
std::map<std::string, std::string> optable_get_mnemonic;
// contains the length of instruction format for the given opcode 
std::map<std::string, int> optable_get_length;

void add_to_optable(std::string &s, std::string &t);
void initialise_optable();

#endif