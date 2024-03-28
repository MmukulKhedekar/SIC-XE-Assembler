#include "../include/assembler.h"
#include "../include/tokenization.h"
#include "../include/optab.h"
#include "../include/symtab.h"
#include "../include/reg.h"
#include "../include/utils.h"
#include "../include/validity.h"

long long int LOCCTR = -1;
std::vector<std::pair<long long int, std::vector<std::string>>> first_pass_parse;

long long int PC = 0LL;
long long int B = 0LL;

void first_pass(const std::string &FILE_NAME) {
    first_pass_parse.clear();
    if (!optable.size()) {
        initialise_optable();
    }

    if (!REG.size()) {
        initialise_registers();
    }
    clear_symbol_table();

    std::string is_txt_file = ".txt";
    if (FILE_NAME.find(is_txt_file) == std::string::npos) {
        FILE_NAME += is_txt_file;
    }

    auto parsed_lines = parse(FILE_NAME);
    for (auto &line: parsed_lines) {
        for (auto &word: line) {
            make_upper_case(word);
        }

        if (line.size() == 3) {
            first_pass_parse.push_back({LOCCTR, line});
            if (LOCCTR == -1 and line[1] == "START") {
                LOCCTR = std::stoi(line[2]);
            } else if (LOCCTR == -1 and line[1] != "START") {
                // GENERATE ERROR MESSAGE: WHERE THE START AT BRO?
            }

            add_symbol(line[0], LOCCTR);

            if (line[1] == "RESW") {
                LOCCTR += std::stoi(line[2]) * 3;
            } else if (line[1] == "RESB") {
                LOCCTR += std::stoi(line[2]);
            } else if (line[1] == "WORD") {
                LOCCTR += word_size(line[2]); 
            } else if (line[1] == "BYTE") {
                LOCCTR += byte_size(line[2]);
            } else if (line[1][0] == '+') {
                LOCCTR += 4;
            } else if (line[1] == "END") {
                break;    
            } else if (optab[line[1]].second) {
                LOCCTR += optab[line[1]].second;
            } else {
                // GENERATE ERROR MESSAGE: WHAT ELSE IS THERE
            }

        } else if (line.size() == 2) {
            first_pass_parse.push_back({LOCCTR, line});
            if (LOCCTR == -1 and line[0] == "START") {
                LOCCTR = std::stoi(line[1]);
            } else if (LOCCTR == -1 and line[0] != "START") {
                // GENERATE ERROR MESSAGE: WHERE THE START AT BRO?
            }

            if (line[0] == "RESW") {
                LOCCTR += std::stoi(line[1]) * 3;
            } else if (line[0] == "RESB") {
                LOCCTR += std::stoi(line[1]);
            } else if (line[0] == "WORD") {
                LOCCTR += word_size(line[1]); 
            } else if (line[0] == "BYTE") {
                LOCCTR += byte_size(line[1]);
            } else if (line[0][0] == '+') {
                LOCCTR += 4;
            } else if (line[0] == "END") {
                break;    
            } else if (optab[line[0]].second) {
                LOCCTR += optab[line[0]].second;
            } else {
                // GENERATE ERROR MESSAGE: WHAT ELSE IS THERE
            }
        } else if (line.size() == 1) {
            if (LOCCTR == -1){
                // GENERATE ERROR MESSAGE: HOW TF
            }
            if (line[0] == "RSUB"){
                LOCCTR += 3;
            } else {
                // GENERATE ERROR MESSAGE: WHAT YOU DOIN
            }
        } else {
            // GENERATE ERROR MESSAGE COZ WHAT?
        }
    }

    second_pass();
}

void second_pass() {
    std::vector<std::string> header_record;
    std::vector<std::pair<std::string, std::string>> text_record;
    std::vector<std::string> end_record;

    for (int j = 0; j < first_pass_parse.size(); j++) {
        int n = 0, i = 0, x = 0, b = 0, p = 0, e = 0;
        if (j != (first_pass_parse.size() - 1)) {
            PC = first_pass_parse[j + 1].first;
        }
        if (first_pass_parse[j].second.size() == 3) {
            if (first_pass_parse[j].second[1] == "START") {
                header_record.push_back(first_pass_parse[j].second[0]);
                header_record.push_back(first_pass_parse[j].second[2]);
                header_record.push_back(first_pass_parse[1].first);
                header_record.push_back(first_pass_parse[first_pass_parse.size() - 1].first);
            } else {
                // ADD METHODS TO DEAL WITH ALL FOUR FORMATS
            }
        } else if (first_pass_parse[j].second.size() == 2) {
            if (first_pass_parse[j].second[0] == "END") {
                end_record.push_back(header_record[1]);
            } else {
                // ADD METHODS TO DEAL WITH ALL FOUR FORMATS
            }         
        } else if (first_pass_parse[j].second.size() == 1) {
            if (first_pass_parse[j].second[0] == "RSUB") {
                text_record.push_back({first_pass_parse[j].first, "4F0000"});
            } else {
                // GENERATE ERROR PLEASE
            }
        } else {
            // THROW ERROR, OTHER LENGTHS ARE NOT ALLOWED
        }
    }
}
