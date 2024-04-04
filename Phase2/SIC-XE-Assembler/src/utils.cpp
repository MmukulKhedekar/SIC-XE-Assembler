#include "../include/utils.h"
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
    return (len + 1) / 2;
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

        resultant += hex_values[c] * position;
        position *= 16;
    }

    return resultant;
}

// ADD MORE UTILS IF NECESSARY
