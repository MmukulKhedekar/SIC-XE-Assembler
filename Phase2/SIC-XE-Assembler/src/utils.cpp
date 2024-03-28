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

std::string int_to_string(int x, int length) {
    std::string s = "";
    while (x > 0) {
        long long int res = x % 10;
        
        s = (char)(res + '0') + s;
        x /= 10;
    }

    while (s.length() < length) {
        s = "0" + s;
    }
    
    return s;
}

std::string int_to_hex(int x, int length) {
    std::string s = "";

    while (x > 0) {
        long long int res = x % 16;
        if (res >= 10) {
            res -= 10;
            s = (char)(res + 'A') + s;
        } else {
            s = (char)(res + '0') + s;
        }

        x /= 16;
    }

    while (s.length() < length) {
        s = "0" + s;
    }

    return s;
}

std::string int_to_binary(int x, int length) {
    std::string s = "" ;

    while (x > 0) {
        long long int res = x % 2;
        
        s = (char)(res + '0') + s;
        x /= 2;
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

// ADD MORE UTILS IF NECESSARY
