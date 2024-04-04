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

        first_pass_parse.push_back({LOCCTR, line});

        if (line.size() == 3) {
            if (LOCCTR == -1 and line[1] == "START") {
                LOCCTR = hex_to_int(line[2]);
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
            if (LOCCTR == -1) {
                // GENERATE ERROR MESSAGE: WHERE'S THE NAME OF THE PROGRAM 
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

long long int n = 0, i = 0, x = 0, b = 0, p = 0, e = 0;

std::string format1(std::vector<std::string> &LINES) {

}

std::string format2(std::vector<std::string> &LINES) {

}

std::string format3(std::vector<std::string> &LINES) {

}

std::string format4(std::vector<std::string> &LINES) {

}

std::string direct_flow(long long int location, std::string &SOURCE, std::string &OPERAND) {
    
}

void second_pass() {
    std::vector<std::string> header_record;
    std::vector<std::pair<long long int, std::string>> text_record;
    std::vector<std::string> end_record;

    for (int j = 0; j < first_pass_parse.size(); j++) {
        n = 0, i = 0, x = 0, b = 0, p = 0, e = 0;
        if (j != (first_pass_parse.size() - 1)) {
            PC = first_pass_parse[j + 1].first;
        }
        if (first_pass_parse[j].second.size() == 3) {
            if (first_pass_parse[j].second[1] == "START") {
                std::string HEADER = "H";
                HEADER += first_pass_parse[j].second[0];
                for (int y = 0; y < 6 - first_pass_parse[j].second[0]; y++) {
                    HEADER += " ";
                }
                HEADER += int_to_hex(PC, 6);
                header_record.push_back(HEADER);

                std::string END = "E";
                END += int_to_hex(PC, 6);

                end_record.push_back(END);
            } else {
                
                std::string object_code = direct_flow(first_pass_parse[j].first, first_pass_parse[j].second[1], first_pass_parse[j].second[2]);
                text_record.push_back({first_pass_parse[j].first, object_code});
                // ADD METHODS TO DEAL WITH ALL FOUR FORMATS
            }
        } else if (first_pass_parse[j].second.size() == 2) {
            if (first_pass_parse[j].second[0] == "END") {
                // DEALT ALREADY
            } else {

                std::string object_code = direct_flow(first_pass_parse[j].first, first_pass_parse[j].second[0], first_pass_parse[j].second[1]);
                text_record.push_back({first_pass_parse[j].first, object_code});
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
