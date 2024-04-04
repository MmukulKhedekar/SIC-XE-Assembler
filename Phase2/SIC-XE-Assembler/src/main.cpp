#include "../include/assembler.hpp"
#include "../include/tokenization.hpp"
#include "../include/optab.hpp"
#include "../include/symtab.hpp"
#include "../include/reg.hpp"
#include "../include/utils.hpp"
#include "../include/validity.hpp"

int main() {
    std::cout << "HELLO WELCOME TO MY ASSEMBLER" << '\n';

    while (true) {
        std::cout << "ENTER NAME OF THE FILE TO ASSEMBLE\n";
        
        std::string NAME;
        std::cin >> NAME;

        first_pass(NAME);

        for (auto u: text_record) {
            std::cout << u.first << ' ' << u.second << '\n';
        }
    }
}