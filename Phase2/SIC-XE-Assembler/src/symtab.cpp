#include "../include/symtab.h"

void clear_symbol_table() {
    symbol_table.clear();
}

bool exists(std::string &LABEL) {
    return (symbol_table[LABEL] > 0) ? (true) : (false);
}

void add_symbol(std::string &LABEL, long long int LOCCTR) {
    if (!exists(LABEL)) {
        symbol_table[LABEL] = LOCCTR; 
        return;
    }
    // ELSE GENERATE AN ERROR MESSAGE: SYMBOL ALREADY EXISTS!
}

long long int get_locctr(std::string &LABEL) {
    if (exists(LABEL)) {
        return symbol_table[LABEL];
    }
    // ELSE GENERATE AN ERROR MESSAGE: SYMBOL DOESNT EXIST! 
}