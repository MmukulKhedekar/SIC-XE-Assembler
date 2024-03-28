#include "../include/reg.h"

std::map<std::string, int> REG;

void initialise_registers() {
    REG["A"] = 0;
    REG["X"] = 1;
    REG["L"] = 2;
    REG["B"] = 3;
    REG["S"] = 4;
    REG["T"] = 5;
    REG["F"] = 6;
    REG["PC"] = 8;
    REG["SW"] = 9;
}