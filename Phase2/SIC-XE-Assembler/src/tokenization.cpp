#include "../include/tokenization.h"

std::vector<std::vector<std::string>> parse(const std::string &FILE_NAME) {
    std::ifstream file = file(FILE_NAME);
    if (!file.is_open()) {
        // GENERATE ERROR MESSAGE HERE: UNABLE TO OPEN THE FILE!
    }

    std::vector<std::vector<std::string>> TOKENS;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream get_line(line);
        std::string WORD;

        int cnt = 0;
        bool __CONTINUE__ = false;
        while (get_line >> WORD) {
            if (cnt == 0 and WORD[0] == '.'){
                __CONTINUE__ = true;
                break;
            }
            cnt++; 

            if (cnt == 1) TOKENS.push_back(std::vector<std::string>());
            TOKENS.back().push_back(WORD);
        }
        if (__CONTINUE__) continue;
    }

    file.close();
    return TOKENS;
}   