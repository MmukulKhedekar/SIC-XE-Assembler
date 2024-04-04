#ifndef ASSEMBLER_H 
#define ASSEMBLER_H 

void first_pass(const std::string &FILE_NAME);
std::string format1(std::vector<std::string> &LINES);
std::string format2(std::vector<std::string> &LINES);
std::string format3(std::vector<std::string> &LINES);
std::string format4(std::vector<std::string> &LINES);
std::string direct_flow(long long int location, std::string &SOURCE, std::string &OPERAND);
void second_pass();

#endif 