#include <"include/optab.h">

int get_length_from_optable(std::string &s) {
    if (!optable_get_length[s]) {
        return optable_get_length[s];
    }
    // else generate error message that the following opcode does not exist in the optable and terminate the program
}

std::string get_mnemonic_from_optable (std::string &s) {
    if (!optable_get_mnemonic[s]) {
        return optable_get_mnemonic[s];
    }
    // else generate an error message that the following opcode does not exist and terminate the program
} 

void add_to_optable(std::string &s, std::string &t, int x) {
    optable_get_mnemonic[t] = s;
    optable_get_length[t] = x;
    
}

void initialise_optable() {
    // fill in this later on
    add_to_optable("RSUB", "4C", 6);
    
}