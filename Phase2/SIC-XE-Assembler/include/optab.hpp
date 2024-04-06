#ifndef OPTAB_H
#define OPTAB_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <array>
#include <map>

std::map<std::string, std::pair<std::string, long long int>> optable;

void initialise_optable();
void add_to_optable(std::string &MNEMONIC, std::string &OPCODE, long long int LENGTH);
std::string find_in_optable(std::string &MNEMONIC);
int mnemonic_length(std::string &MNEMONIC);

#endif