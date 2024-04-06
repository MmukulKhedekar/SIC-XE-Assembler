#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <array>
#include <map>

#include <thread>
#include <chrono>

void sleep_duration(int x) {
    std::chrono::seconds duration(x);
    std::this_thread::sleep_for(duration);
}

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define WHITE   "\033[37m"
#define LIGHTBLUE "\033[94m"

void make_upper_case(std::string &s) {
    for (auto &u: s) {
        if ((int)(u) >= 97 and (int)(u) <= 96 + 26) {
            u = (char)((int)(u) - 32);
        }
    }
}

void make_lower_case(std::string &s) {
    for (auto &u: s) {
        if ((int)(u) >= 65 and (int)(u) <= 64 + 26) {
            u = (char)((int)(u) + 32);
        }
    }
}

std::string int_to_string(long long int x, long long int length) {
    std::string s = "";
    
    long long int y = x;
    while (y > 0) {
        long long int res = y % 10;
        
        s = (char)(res + '0') + s;
        y /= 10;
    }

    while (s.length() < length) {
        s = "0" + s;
    }
    
    return s;
}

std::string int_to_hex(long long int x, long long int length) {
    std::string s = "";

    long long int y = x;
    while (y > 0) {
        long long int res = y % 16;
        if (res >= 10) {
            res -= 10;
            s = (char)(res + 'A') + s;
        } else {
            s = (char)(res + '0') + s;
        }

        y /= 16;
    }

    while (s.length() < length) {
        s = "0" + s;
    }

    return s;
}

std::string int_to_binary(long long int x, long long int length) {
    std::string s = "" ;

    long long int y = x;
    while (y > 0) {
        long long int res = y % 2;
        
        s = (char)(res + '0') + s;
        y /= 2;
    }

    while (s.length() < length) {
        s = "0" + s;
    }

    return s;
}

long long int byte_size(std::string &BYTE) {
    if (BYTE[0] == 'C') {
        return BYTE.length() - 3;
    } else if (BYTE[0] == 'X') {
        return (BYTE.length() - 3) / 2;
    } else {
        // GENERATE ERROR: WHAT ARE YOU SENDING
        return -1;
    }
}

long long int word_size(std::string WORD) {
    int length = WORD.length();
    int string_to_integer = std::stoi(WORD);

    std::string string_in_hex = int_to_hex(string_to_integer, length + 1);    
    long long int len = string_in_hex.length();

    for (int i = 0; i < string_in_hex.length(); i++) {
        if (string_in_hex[i] == '0') len--;
        else break;
    }
    return (((((len + 1) / 2) + 2) / 3) * 3 == 0) ? (3): (((((len + 1) / 2) + 2) / 3) * 3);
}

long long int hex_to_int(std::string &s) {
    std::map<char, long long int> hex_values; 
    hex_values['0'] = 0;
    hex_values['1'] = 1;
    hex_values['2'] = 2;
    hex_values['3'] = 3;
    hex_values['4'] = 4;
    hex_values['5'] = 5;
    hex_values['6'] = 6;
    hex_values['7'] = 7;
    hex_values['8'] = 8;
    hex_values['9'] = 9;
    hex_values['A'] = 10;
    hex_values['B'] = 11;
    hex_values['C'] = 12;
    hex_values['D'] = 13;
    hex_values['E'] = 14;
    hex_values['F'] = 15;

    std::string t = s;
    long long int resultant = 0;
    long long int position = 1;

    while (t.size() > 0) {
        char c = t[t.size() - 1];
        t = t.substr(0, t.size() - 1);
        resultant += hex_values[c] * position;
        position *= 16;
    }

    return resultant;
}

std::map<std::string, std::pair<std::string, long long int>> optable;

void add_to_optable(std::string MNEMONIC, std::string OPCODE, long long int LENGTH) {
    optable[MNEMONIC] = std::make_pair(OPCODE, LENGTH);
}

int mnemonic_length(std::string MNEMONIC) {
    if (optable[MNEMONIC].second > 0){
        return optable[MNEMONIC].second; 
    }
    // ELSE GENERATE ERROR MESSAGE: OPCODE DOESNT EXIST!
}

std::string find_in_optable(std::string MNEMONIC) {
    std::string t = optable[MNEMONIC].first;
    if (t != ""){
        return t;
    }
    // ELSE GENERATE ERROR MESSAGE: OPCODE DOESNT EXIST!
}

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

std::map<std::string, long long int> symbol_table;

void clear_symbol_table() {
    symbol_table.clear();
}

bool exists(std::string &LABEL) {
    return (symbol_table[LABEL] > 0) ? (true) : (false);
}

void add_symbol(std::string &LABEL, long long int LOCCTR) {
    // std::cout << "adding the symbol " << LABEL << " which would be assigned " << LOCCTR << '\n';
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

std::vector<std::vector<std::string>> parse(std::string &FILE_NAME) {

    std::ifstream file(FILE_NAME);

    if (!file.is_open()) {
        std::cout << RED << "ERROR! File named: \"" << FILE_NAME << "\" could not be opened!" << RESET << '\n'; // LINE TO REMOVE LATER
        // GENERATE ERROR MESSAGE HERE: UNABLE TO OPEN THE FILE!
    } else {
        std::cout << GREEN << "File opened successfully!" << RESET << '\n';
    }
    sleep_duration(2);

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

std::vector<std::string> header_record;
std::vector<std::pair<long long int, std::string>> text_record;
std::vector<std::string> end_record;

std::vector<std::pair<long long int, std::vector<std::string>>> first_pass_parse;

long long int LOCCTR = -1;
long long int PC = 0LL;
long long int B = 0LL;

long long int n = 0, i = 0, x = 0, b = 0, p = 0, e = 0;

std::string format1(std::string &MNEMONIC, std::string &OPERAND) {
    std::string ANS = find_in_optable(MNEMONIC);

    return ANS;
}

std::string format2(std::string &MNEMONIC, std::string &OPERAND) {
    std::string ANS = find_in_optable(MNEMONIC);

    if (OPERAND.length() == 3) {
        ANS += REG[std::string(1, OPERAND[0])];
        ANS += REG[std::string(1, OPERAND[2])];
    } else if (OPERAND.length() == 1) {
        ANS += '0';
        ANS += REG[std::string(1, OPERAND[0])];

        // CHECK FOR 'CLEAR', 'SVC', 'TIXR', 'SHIFTL', 'SHIFTR'
    }
    
    return ANS;
}

std::string format3(std::string &MNEMONIC, std::string &OPERAND) {
    std::string ANS = find_in_optable(MNEMONIC);

    p = 1;
    // ADD SUPPORT FOR BASE REGISTER

    if (OPERAND[OPERAND.length() - 1] == 'X') {
        x = 1;
        OPERAND = OPERAND.substr(0, OPERAND.length() - 2);
    }

    long long int target = hex_to_int(ANS);

    if (OPERAND[0] == '@') {
        n = 1;
        i = 0;

        target += 2;
        ANS = int_to_hex(target, 2);

    } else if (OPERAND[0] == '#') {
        n = 0;
        i = 1;

        target += 1;
        ANS = int_to_hex(target, 2);

    } else {
        n = 1;
        i = 1;

        target += 3;
        ANS = int_to_hex(target, 2);

    }

    // ADD SUPPORT FOR BASE RELATIVE
    if (x == 0) {
        ANS += int_to_hex(2, 1);
    } else if (x == 1) {
        ANS += int_to_hex(10, 1);
    }

    // ADD SUPPORT FOR INDIRECT AND IMMEDIATE ADDRESSING

    long long int diff = (get_locctr(OPERAND) - PC);
    if (diff >= 0) {
        diff += 3;
    } else {
        diff = (1LL << 12) + diff;
        diff -= 3;
    }

    ANS += int_to_hex(diff, 3);
    return ANS;
}

std::string format4(std::string &MNEMONIC, std::string &OPERAND) {
    e = 1;

    // GENERATE MODIFICATION RECORDS HERE 

    std::string ANS = find_in_optable(MNEMONIC);

    // ADD SUPPORT FOR BASE REGISTER

    if (OPERAND[OPERAND.length() - 1] == 'X') {
        x = 1;
        OPERAND = OPERAND.substr(0, OPERAND.length() - 2);
    }

    long long int target = hex_to_int(ANS);

    if (OPERAND[0] == '@') {
        n = 1;
        i = 0;

        target += 2;
        ANS = int_to_hex(target, 2);

    } else if (OPERAND[0] == '#') {
        n = 0;
        i = 1;

        target += 1;
        ANS = int_to_hex(target, 2);

    } else {
        n = 1;
        i = 1;

        target += 3;
        ANS = int_to_hex(target, 2);

    }

    // ADD SUPPORT FOR BASE RELATIVE
    if (x == 0) {
        ANS += int_to_hex(1, 1);
    } else if (x == 1) {
        ANS += int_to_hex(9, 1);
    }

    // ADD SUPPORT FOR INDIRECT AND IMMEDIATE ADDRESSING

    long long int diff = get_locctr(OPERAND);

    ANS += int_to_hex(diff, 5);
    return ANS;
}

std::string direct_flow(long long int location, std::string &SOURCE, std::string &OPERAND) {
    if (SOURCE[0] == '+') {
        std::string NEW_SOURCE = SOURCE.substr(1, SOURCE.size() - 1);
        return format4(NEW_SOURCE, OPERAND);
    } 

    int len = mnemonic_length(SOURCE);

    if (len == 3) {

        return format3(SOURCE, OPERAND);
    } else if (len == 2) {

        return format2(SOURCE, OPERAND);
    } else if (len == 1) {

        return format1(SOURCE, OPERAND);
    } else {

        // GENERATE ERROR: BECAUSE MNEMONIC DOES NOT EXIST IN 
    }
}

void second_pass() {

    for (int j = 0; j < first_pass_parse.size(); j++) {
        n = 0, i = 0, x = 0, b = 0, p = 0, e = 0;
        if (j != (first_pass_parse.size() - 1)) {
            PC = first_pass_parse[j + 1].first;
        }
        if (first_pass_parse[j].second.size() == 3) {
            if (first_pass_parse[j].second[1] == "START") {
                std::string HEADER = "H";
                HEADER += first_pass_parse[j].second[0];
                for (int y = 0; y < 6 - first_pass_parse[j].second[0].length(); y++) {
                    HEADER += " ";
                }
                HEADER += int_to_hex(PC, 6);
                header_record.push_back(HEADER);

                std::string END = "E";
                END += int_to_hex(PC, 6);

                end_record.push_back(END);
            } else {

                // ADD FOR WORD AND BYTE
                if (first_pass_parse[j].second[1] == "RESW") continue;
                else if (first_pass_parse[j].second[1] == "RESB") continue;
                else if (first_pass_parse[j].second[1] == "BYTE") {
                    if (first_pass_parse[j].second[2][0] == 'C') {
                        std::string object_code = "";

                        for (int y = 0; y < first_pass_parse[j].second[2].length() - 3; y++) {
                            object_code += int_to_hex((int)(first_pass_parse[j].second[2][y + 2]), 2);
                        }
                        text_record.push_back({first_pass_parse[j].first, object_code});

                        continue;
                    } else if (first_pass_parse[j].second[2][0] == 'X') {
                        std::string object_code = first_pass_parse[j].second[2].substr(2, first_pass_parse[j].second[2].length() - 3);
                        text_record.push_back({first_pass_parse[j].first, object_code});
                    
                        continue;   
                    } else {
                        // GENERATE ERROR MESSAGE: WHAT ARE YOU TRYING TO STORE
                    }
                } else if (first_pass_parse[j].second[1] == "WORD") {
                    std::string object_code = int_to_hex(std::stoi(first_pass_parse[j].second[2]), 6);
                    text_record.push_back({first_pass_parse[j].first, object_code});
                    
                    continue;
                }
                
                std::string object_code = direct_flow(first_pass_parse[j].first, first_pass_parse[j].second[1], first_pass_parse[j].second[2]);
                text_record.push_back({first_pass_parse[j].first, object_code});
                // ADD METHODS TO DEAL WITH ALL FOUR FORMATS
            }
        } else if (first_pass_parse[j].second.size() == 2) {
            if (first_pass_parse[j].second[0] == "END") {
                // DEALT ALREADY
            } else {

                // ADD FOR WORD AND BYTE
                if (first_pass_parse[j].second[0] == "RESW") continue;
                else if (first_pass_parse[j].second[0] == "RESB") continue;
                else if (first_pass_parse[j].second[0] == "BYTE") {
                    if (first_pass_parse[j].second[1][0] == 'C') {
                        std::string object_code = "";

                        for (int y = 0; y < first_pass_parse[j].second[1].length() - 3; y++) {
                            object_code += int_to_hex((int)(first_pass_parse[j].second[1][y + 2]), 2);
                        }
                        text_record.push_back({first_pass_parse[j].first, object_code});

                        continue;
                    } else if (first_pass_parse[j].second[1][0] == 'X') {
                        std::string object_code = first_pass_parse[j].second[1].substr(2, first_pass_parse[j].second[1].length() - 3);
                        text_record.push_back({first_pass_parse[j].first, object_code});
                    
                        continue;   
                    } else {
                        // GENERATE ERROR MESSAGE: WHAT ARE YOU TRYING TO STORE
                    }
                } else if (first_pass_parse[j].second[1] == "WORD") {
                    std::string object_code = int_to_hex(std::stoi(first_pass_parse[j].second[1]), 6);
                    text_record.push_back({first_pass_parse[j].first, object_code});
                    
                    continue;
                }
                
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

void print_out_first_pass();
void print_line(std::string s) {
    int n = s.length(); 
    for (int i = 0; i < (50 - n) / 2; i++) {
        std::cout << BLUE << "-";
    }
    std::cout << BLUE << "[ " << s << " ]";
    for (int i = 0; i < (50 - n) / 2; i++) {
        std::cout << BLUE << "-";
    }
    std::cout << '\n';
}
void first_pass(std::string &FILE_NAME) {

    LOCCTR = -1;
    PC = 0LL;
    B = 0LL;

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

// /* TO BE REMOVED LATER */

//     for (auto &line: parsed_lines) {
//         for (auto &word: line) {
//             std::cout << word << ' ';
//         }
//         std::cout << '\n';
//     }

// /* REMOVE THE ABOVE CONTENT LATER */

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
            } else if (optable[line[1]].second) {
                LOCCTR += optable[line[1]].second;
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
            } else if (optable[line[0]].second) {
                LOCCTR += optable[line[0]].second;
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

/*  CONTENT TO BE REMOVED LATER */

    // for (auto &lines: first_pass_parse) {
    //     if (lines.second.size() > 1) if (lines.second[1] == "START") continue;
    //     std::cout << int_to_hex(lines.first, 6) << ' ';
    //     for (auto &word: lines.second) {
    //         std::cout << word << ' ';
    //     }
    //     std::cout << '\n';
    // }

/*  CONTENT TO BE REMOVED LATER */

    std::cout << GREEN << "First Pass completed successfully!\n" << RESET << '\n';
    sleep_duration(2);

    std::cout << YELLOW << "Press [P] to print out the result of the first pass: ";
    
    char yes;
    std::cin >> yes;

    if (yes == 'P') {
        sleep_duration(1);
        print_out_first_pass();

        std::cout << "\n" << YELLOW << "[E]nter any key to continue the assembling ";
        std::cin >> yes;
        print_line("ASSEMBLING");
    }

    second_pass();
}

void print_out_first_pass() {
    print_line("RESULT");
    for (auto &lines: first_pass_parse) {
        if (lines.second.size() == 3) {
            if (lines.second[1] == "START") {
                std::cout << '\t';
                for (auto &word: lines.second) {
                    std::cout << YELLOW << word << '\t';
                }
                std::cout << '\n';
            } else {
                std::cout << WHITE << int_to_hex(lines.first, 6) << '\t';
                
                int cnt = 0;
                for (auto &word: lines.second) {
                    if (cnt == 0) {
                        std::cout << RED << word << '\t';
                    } else if (cnt == 1){
                        std::cout << GREEN << word << '\t';
                    } else if (cnt == 2) {
                        std::cout << BLUE << word << '\t';
                    }
                    cnt++;
                }
                std::cout << '\n';
            }
        } else if (lines.second.size() == 2) {
            
            std::cout << WHITE << int_to_hex(lines.first, 6) << '\t';
            std::cout << '\t';

            int cnt = 0;
            for (auto &word: lines.second) {
                if (cnt == 0){
                    std::cout << GREEN << word << '\t';
                } else if (cnt == 1) {
                    std::cout << BLUE << word << '\t';
                }
                cnt++;
            }
            std::cout << '\n';
            
        } else {
            std::cout << WHITE << int_to_hex(lines.first, 6) << '\t';
            std::cout << '\t';
            for (auto &word: lines.second) {
                std::cout << GREEN << word  << '\t';
            }
            std::cout << '\n';
            std::cout << '\n';
        }
    }
}

int main() {

    std::cout << "Enter the name of the file to assemble: ";
    
    std::string NAME;
    std::cin >> NAME;
    
    print_line("ASSEMBLING");
    std::cout << YELLOW << "Opening the file: " << NAME << RESET << '\n';
    sleep_duration(2);

    first_pass(NAME);
}