#include "../include/optab.h"

void initialise_optable() {
    // MNEMONICS SUPPORTED BY FORMAT 1
    add_to_optable("FLOAT", "C0", 1);
    add_to_optable("FIX", "C4", 1);
    add_to_optable("NORM", "C8", 1);

    add_to_optable("SIO", "F0", 1);
    add_to_optable("HIO", "F4", 1);
    add_to_optable("TIO", "F8", 1);

    // MNEMONICS SUPPORTED BY FORMAT 2
    add_to_optable("ADDR", "90", 2);
    add_to_optable("SUBR", "94", 2);
    add_to_optable("MULR", "98", 2);
    add_to_optable("DIVR", "9C", 2);
    
    add_to_optable("COMPR", "A0", 2);
    add_to_optable("SHIFTL", "A4", 2);
    add_to_optable("SHIFTR", "A8", 2);
    add_to_optable("RMO", "AC", 2);
    
    add_to_optable("SVC", "B0", 2);
    add_to_optable("CLEAR", "B4", 2);
    add_to_optable("TIXR", "B8", 2);

    // MNEMONICS SUPPORTED BY FORMAT 3/4
    add_to_optable("LDA", "00", 3);
    add_to_optable("LDX", "04", 3);
    add_to_optable("LDL", "08", 3);
    add_to_optable("STA", "0C", 3);

    add_to_optable("STX", "10", 3);
    add_to_optable("STL", "14", 3);
    add_to_optable("ADD", "18", 3);
    add_to_optable("SUB", "1C", 3);

    add_to_optable("MUL", "20", 3);
    add_to_optable("DIV", "24", 3);
    add_to_optable("COMP", "28", 3);
    add_to_optable("TIX", "2C", 3);

    add_to_optable("JEQ", "30", 3);
    add_to_optable("JGT", "34", 3);
    add_to_optable("JLT", "38", 3);
    add_to_optable("J", "3C", 3);

    add_to_optable("AND", "40", 3);
    add_to_optable("OR", "44", 3);
    add_to_optable("JSUB", "48", 3);
    add_to_optable("RSUB", "4C", 3);

    add_to_optable("LDCH", "50", 3);
    add_to_optable("STCH", "54", 3);
    add_to_optable("ADDF", "58", 3);
    add_to_optable("SUBF", "5C", 3);

    add_to_optable("MULF", "60", 3);
    add_to_optable("DIVF", "64", 3);
    add_to_optable("LDB", "68", 3);
    add_to_optable("LDS", "6C", 3);
    
    add_to_optable("LDF", "70", 3);
    add_to_optable("LDT", "74", 3);
    add_to_optable("STB", "78", 3);
    add_to_optable("STS", "7C", 3);

    add_to_optable("STF", "80", 3);
    add_to_optable("STT", "84", 3);
    add_to_optable("COMPF", "88", 3);

    add_to_optable("LPS", "D0", 3);
    add_to_optable("STI", "D4", 3);
    add_to_optable("RD", "D8", 3);
    add_to_optable("WD", "DC", 3);

    add_to_optable("TD", "E0", 3);
    add_to_optable("STSW", "E8", 3);
    add_to_optable("SSK", "EC", 3);
}

void add_to_optable(std::string &MNEMONIC, std::string &OPCODE, long long int LENGTH) {
    optable[MNEMONIC] = std::make_pair(OPCODE, LENGTH);
}

int mnemonic_length(std::string &MNEMONIC) {
    if (optable[MNEMONIC].second > 0){
        return optable[MNEMONIC].second; 
    }
    // ELSE GENERATE ERROR MESSAGE: OPCODE DOESNT EXIST!
}

std::string find_in_optable(std::string &MNEMONIC) {
    std::string t = optable[MNEMONIC].first;
    if (t != ""){
        return t;
    }
    // ELSE GENERATE ERROR MESSAGE: OPCODE DOESNT EXIST!
}