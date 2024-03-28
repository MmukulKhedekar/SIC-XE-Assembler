#ifndef UTILS_H 
#define UTILS_H 

#include "imports.h"

void make_upper_case(std::string &s);
void make_lower_case(std::string &s);

std::string int_to_string(int x, int length);
std::string int_to_hex(int x, int length);
std::string int_to_binary(int x, int length);

long long int byte_size(std::string &BYTE);
long long int word_size(std::string WORD);

// ADD MORE UTILS IF NECESSARY

#endif 