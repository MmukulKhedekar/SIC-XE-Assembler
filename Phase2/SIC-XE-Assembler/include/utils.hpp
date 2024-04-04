#ifndef UTILS_H 
#define UTILS_H 

#include "imports.h"

void make_upper_case(std::string &s);
void make_lower_case(std::string &s);

std::string int_to_string(long long int x, long long int length);
std::string int_to_hex(long long int x, long long int length);
std::string int_to_binary(long long int x, long long int length);

long long int byte_size(std::string &BYTE);
long long int word_size(std::string WORD);
long long int hex_to_int(std::string &s);

// ADD MORE UTILS IF NECESSARY

#endif 