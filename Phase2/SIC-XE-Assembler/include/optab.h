#ifndef OPTAB_H
#define OPTAB_H

#include "imports.h"

void initialise_optable();
void add_to_optable(std::string &MNEMONIC, std::string &OPCODE, int LENGTH);
std::string find_in_optable(std::string &MNEMONIC);
int mnemonic_length(std::string &MNEMONIC);

#endif