#include <bits/stdc++.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

std::string gethex(std::string &s){
    std::map<char, std::string> hex_strings;
    hex_strings['0'] = "0000";
    hex_strings['1'] = "0001";
    hex_strings['2'] = "0010";
    hex_strings['3'] = "0011";
    hex_strings['4'] = "0100";
    hex_strings['5'] = "0101";
    hex_strings['6'] = "0110";
    hex_strings['7'] = "0111";
    hex_strings['8'] = "1000";
    hex_strings['9'] = "1001";
    hex_strings['a'] = "1010";
    hex_strings['b'] = "1011";
    hex_strings['c'] = "1100";
    hex_strings['d'] = "1101";
    hex_strings['e'] = "1110";
    hex_strings['f'] = "1111";    

    std::string res = "";
    for (auto c: s){
        res += hex_strings[c];
    }

    return res;
}

std::string check(std::string &s){
    std::string res = "";
    for (auto c: s){
        res += std::tolower(c);
    }

    bool pass = true;

    for (auto c: res){
        if ((int)(c) > 96 + 6 or (int)(c) < 48 or ((int)(c) > 48 + 9 and (int)(c) < 97)) pass = false;
    }
    
    if (!pass){
        res = "?";
    }

    return res;
}

void format1(std::string s){
    std::map<std::string, bool> mp;
    
    mp["c0"] = true;
    mp["c4"] = true;
    mp["c8"] = true;
    mp["f0"] = true;    
    mp["f4"] = true;
    mp["f8"] = true;

    bool check = mp[s];
    if (check){
        std::cout << GREEN << "Valid Instruction!" << RESET << '\n';
        std::cout << YELLOW << "Instruction Format: Format 1" << RESET << '\n';
    } else {
        std::cout << RED << "Invalid Instruction!"  << RESET << '\n';
        std::cout << RED << "Instruction Format: Format 1" << RESET << '\n';
        std::cout << RED << "Invalid Opcode Provided!" << RESET << '\n';
    }
}

void format2(std::string s){
    std::map<std::string, bool> mp;

    mp["90"] = true;
    mp["b4"] = true;
    mp["a0"] = true;
    mp["9c"] = true;
    mp["98"] = true;
    mp["ac"] = true;
    mp["a4"] = true;
    mp["a8"] = true;
    mp["94"] = true;
    mp["b0"] = true;
    mp["b8"] = true;

    std::map<std::string, bool> reg;

    reg["0"] = true;
    reg["1"] = true;
    reg["2"] = true;
    reg["3"] = true;
    reg["4"] = true;
    reg["5"] = true;
    reg["6"] = true;
    reg["8"] = true;
    reg["9"] = true;

    std::string opcode = s.substr(0, 2);
    std::string r1 = s.substr(2, 1);
    std::string r2 = s.substr(3, 1); 

    bool check = mp[opcode] & reg[r1] & reg[r2];
    if (check) {
        std::cout << GREEN << "Valid Instruction!" << RESET << '\n';
        std::cout << YELLOW << "Instruction Format: Format 2" << RESET << '\n';
    } else {
        std::cout << RED << "Invalid Instruction!" << RESET << '\n';
        std::cout << RED << "Instruction Format: Format 2" << RESET << '\n';
        if (!mp[opcode]){
            std::cout << RED << "Invalid Opcode Provided!" << RESET << '\n';
        }
        if (!reg[r1]){
            std::cout << RED << "Invalid Register 1 Operand" << RESET << '\n';
        } 
        if (!reg[r2]){
            std::cout << RED << "Invalid Register 2 Operand" << RESET << '\n';
        }
    }
}

void format3(std::string s){
    std::string h = gethex(s);
    std::string opcode = s.substr(0, 2);

    bool check = true;
    if (h[11] == '1') check &= false;

    int n = (h[6] == '1');
    int i = (h[7] == '1');
    if (n == 1 and i == 1){
        int x = (h[8] == '1');
        int b = (h[9] == '1');
        int p = (h[10] == '1');
        int e = (h[11] == '1');

        std::map<std::string, bool> mp;
        mp["1b"] = true;
        mp["5b"] = true;
        mp["43"] = true;
        mp["2b"] = true;
        mp["8b"] = true;
        mp["27"] = true;
        mp["67"] = true;
        mp["3f"] = true;
        mp["33"] = true;
        mp["37"] = true;
        mp["3b"] = true;
        mp["4b"] = true;
        mp["03"] = true;
        mp["6b"] = true;
        mp["53"] = true;
        mp["73"] = true;
        mp["0b"] = true;
        mp["6f"] = true;
        mp["77"] = true;
        mp["07"] = true;
        mp["d3"] = true;
        mp["23"] = true;
        mp["63"] = true;
        mp["47"] = true;
        mp["db"] = true;
        mp["4f"] = true;
        mp["ef"] = true;
        mp["0f"] = true;
        mp["7b"] = true;
        mp["57"] = true;
        mp["83"] = true;
        mp["d7"] = true;
        mp["17"] = true;
        mp["7f"] = true;
        mp["eb"] = true;
        mp["87"] = true;
        mp["13"] = true;
        mp["1f"] = true;
        mp["5f"] = true;
        mp["e3"] = true;
        mp["2f"] = true;
        mp["df"] = true;

        check &= mp[opcode];

        if (b == 1 and p == 1) check &= false;

        if (check){
            std::cout << GREEN << "Valid Instruction!" << RESET << '\n';
            std::cout << YELLOW << "Instruction Format: Format 3" << RESET << '\n';
            std::cout << GREEN << "n = " << n << " and " << "i = " << i << " => Simple Addressing Type (for SIC/XE Instructions) " << RESET << '\n';
            std::cout << GREEN << "x = " << x;
            if (x == 0){
                std::cout << " => Direct Addressing Mode" << RESET << '\n';
            } else {
                std::cout << " => Indexed Addressing Mode" << RESET << '\n';
            }
            std::cout << GREEN << "b = " << b;
            if (b == 1){
                std::cout << " => Base-Relative Addressing Mode" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << GREEN << "p = " << p;
            if (p == 1){
                std::cout << " => PC-Relative Addressing Mode" << RESET << '\n'; 
            } else {
                std::cout << RESET << '\n';
            }
        } else {
            std::cout << RED << "Invalid Instruction!" << RESET << '\n';
            std::cout << RED << "Instruction Format: Format 3" << RESET << '\n';
            std::cout << RED << "n = " << n << " and " << "i = " << i << " => Simple Addressing Type (for SIC/XE Instructions) " << RESET << '\n';
            std::cout << RED << "x = " << x;
            if (x == 0){
                std::cout << " => Direct Addressing Mode" << RESET << '\n';
            } else {
                std::cout << " => Indexed Addressing Mode" << RESET << '\n';
            }
            std::cout << RED << "b = " << b;
            if (b == 1){
                std::cout << " => Base-Relative Addressing Mode" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << RED << "p = " << p;
            if (p == 1){
                std::cout << " => PC-Relative Addressing Mode" << RESET << '\n'; 
            } else {
                std::cout << RESET << '\n';
            }
            if (h[11] == '1'){
                std::cout << RED << "Extended Bit Set => Wrong Instruction Format" << RESET << '\n';
            }
            if (!mp[opcode]){
                std::cout << RED << "Invalid Opcode Provided" << RESET << '\n';
            }
            if (b == 1 and p == 1){
                std::cout << RED << "Both Bits b and p Cannot Be Set!" << RESET << '\n';
            }
        }

    } else if (n == 0 and i == 0){
        int x = (h[8] == '1');

        std::map<std::string, bool> mp;
        mp["18"] = true;
        // mp["58"] = true;
        mp["40"] = true;
        mp["28"] = true;
        // mp["88"] = true;
        mp["24"] = true;
        // mp["64"] = true;
        mp["3c"] = true;
        mp["30"] = true;
        mp["34"] = true;
        mp["38"] = true;
        mp["48"] = true;
        mp["00"] = true;
        // mp["68"] = true;
        mp["50"] = true;
        // mp["70"] = true;
        mp["08"] = true;
        // mp["6c"] = true;
        // mp["74"] = true;
        mp["04"] = true;
        // mp["d0"] = true;
        mp["20"] = true;
        // mp["60"] = true;
        mp["44"] = true;
        mp["d8"] = true;
        mp["4c"] = true;
        // mp["ec"] = true;
        mp["0c"] = true;
        // mp["78"] = true;
        mp["54"] = true;
        // mp["80"] = true;
        // mp["d4"] = true;
        mp["14"] = true;
        // mp["7c"] = true;
        mp["e8"] = true;
        // mp["84"] = true;
        mp["10"] = true;
        mp["1c"] = true;
        // mp["5c"] = true;
        mp["e0"] = true;
        mp["2c"] = true;
        mp["dc"] = true;

        check &= mp[opcode];

        if (check){
            std::cout << GREEN << "Valid Instruction!" << RESET << '\n';
            std::cout << YELLOW << "Instruction Format: Format 3" << RESET << '\n';
            std::cout << GREEN << "n = " << n << " and " << "i = " << i << " => Simple Addressing Type (for SIC Instructions) " << RESET << '\n';
            std::cout << GREEN << "x = " << x;
            if (x == 0){
                std::cout << " => Direct Addressing Mode" << RESET << '\n';
            } else {
                std::cout << " => Indexed Addressing Mode" << RESET << '\n';
            }
        } else {
            std::cout << RED << "Invalid Instruction!" << RESET << '\n';
            std::cout << RED << "Instruction Format: Format 3" << RESET << '\n';
            std::cout << RED << "n = " << n << " and " << "i = " << i << " => Simple Addressing Type (for SIC Instructions) " << RESET << '\n';
            std::cout << RED << "x = " << x;
            if (x == 0){
                std::cout << " => Direct Addressing Mode" << RESET << '\n';
            } else {
                std::cout << " => Indexed Addressing Mode" << RESET << '\n';
            }
            if (h[11] == '1'){
                std::cout << RED << "Extended Bit Set => Wrong Instruction Format" << RESET << '\n';
            }
            if (!mp[opcode]){
                std::cout << RED << "Invalid Opcode Provided" << RESET << '\n';
            }
        }
    } else if (n == 1 and i == 0){
        int x = (h[8] == '1');
        int b = (h[9] == '1');
        int p = (h[10] == '1');
        int e = (h[11] == '1');

        std::map<std::string, bool> mp;
        mp["1a"] = true;
        mp["5a"] = true;
        mp["42"] = true;
        mp["2a"] = true;
        mp["8a"] = true;
        mp["26"] = true;
        mp["66"] = true;
        mp["3e"] = true;
        mp["32"] = true;
        mp["36"] = true;
        mp["3a"] = true;
        mp["4a"] = true;
        mp["02"] = true;
        mp["6a"] = true;
        mp["52"] = true;
        mp["72"] = true;
        mp["0a"] = true;
        mp["6e"] = true;
        mp["76"] = true;
        mp["06"] = true;
        mp["d2"] = true;
        mp["22"] = true;
        mp["62"] = true;
        mp["46"] = true;
        mp["da"] = true;
        mp["4e"] = true;
        mp["ee"] = true;
        mp["0e"] = true;
        mp["7a"] = true;
        mp["56"] = true;
        mp["82"] = true;
        mp["d6"] = true;
        mp["16"] = true;
        mp["7e"] = true;
        mp["ea"] = true;
        mp["86"] = true;
        mp["12"] = true;
        mp["1e"] = true;
        mp["5e"] = true;
        mp["e2"] = true;
        mp["2e"] = true;
        mp["de"] = true;

        check &= mp[opcode];

        if (x == 1) check &= false;
        if (b == 1 and p == 1) check &= false;

        if (check){
            std::cout << GREEN << "Valid Instruction!" << RESET << '\n';
            std::cout << YELLOW << "Instruction Format: Format 3" << RESET << '\n';
            std::cout << GREEN << "n = " << n << " and " << "i = " << i << " => Indirect Addressing Type (for SIC/XE Instructions) " << RESET << '\n';
            std::cout << GREEN << "x = " << x;
            if (x == 0){
                std::cout << " => Direct Addressing Mode" << RESET << '\n';
            } else {
                std::cout << " => Indexed Addressing Mode" << RESET << '\n';
            }
            std::cout << GREEN << "b = " << b;
            if (b == 1){
                std::cout << " => Base-Relative Addressing Mode" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << GREEN << "p = " << p;
            if (p == 1){
                std::cout << " => PC-Relative Addressing Mode" << RESET << '\n'; 
            } else {
                std::cout << RESET << '\n';
            }
        } else {
            std::cout << RED << "Invalid Instruction!" << RESET << '\n';
            std::cout << RED << "Instruction Format: Format 3" << RESET << '\n';
            std::cout << RED << "n = " << n << " and " << "i = " << i << " => Indirect Addressing Type (for SIC/XE Instructions) " << RESET << '\n';
            std::cout << RED << "x = " << x;
            if (x == 0){
                std::cout << " => Direct Addressing Mode" << RESET<< '\n';
            } else {
                std::cout << " => Indexed Addressing Mode" << RESET << '\n';
            }
            std::cout << RED << "b = " << b;
            if (b == 1){
                std::cout << " => Base-Relative Addressing Mode" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << RED << "p = " << p;
            if (p == 1){
                std::cout << " => PC-Relative Addressing Mode" << RESET << '\n'; 
            } else {
                std::cout << RESET << '\n';
            }
            if (h[11] == '1'){
                std::cout << RED << "Extended Bit Set => Wrong Instruction Format" << RESET << '\n';
            }
            if (!mp[opcode]){
                std::cout << RED << "Invalid Opcode Provided" << RESET << '\n';
            }
            if (b == 1 and p == 1){
                std::cout << RED << "Both Bits b and p Cannot Be Set!" << RESET << '\n';
            }
            if (x == 1){
                std::cout << RED << "Indexed Addressing Mode Cannot Be Used with Indirect Addressing Type" << RESET << '\n';
            }
        }

    } else if (n == 0 and i == 1){
        int x = (h[8] == '1');
        int b = (h[9] == '1');
        int p = (h[10] == '1');
        int e = (h[11] == '1');

        std::map<std::string, bool> mp;
        mp["19"] = true;
        mp["59"] = true;
        mp["41"] = true;
        mp["29"] = true;
        mp["89"] = true;
        mp["25"] = true;
        mp["65"] = true;
        mp["3d"] = true;
        mp["31"] = true;
        mp["35"] = true;
        mp["39"] = true;
        mp["49"] = true;
        mp["01"] = true;
        mp["69"] = true;
        mp["51"] = true;
        mp["71"] = true;
        mp["09"] = true;
        mp["6d"] = true;
        mp["75"] = true;
        mp["05"] = true;
        mp["d1"] = true;
        mp["21"] = true;
        mp["61"] = true;
        mp["45"] = true;
        mp["d9"] = true;
        mp["4d"] = true;
        mp["ed"] = true;
        mp["0d"] = true;
        mp["79"] = true;
        mp["55"] = true;
        mp["81"] = true;
        mp["d5"] = true;
        mp["15"] = true;
        mp["7d"] = true;
        mp["e9"] = true;
        mp["85"] = true;
        mp["11"] = true;
        mp["1d"] = true;
        mp["5d"] = true;
        mp["e1"] = true;
        mp["2d"] = true;
        mp["dd"] = true;

        check &= mp[opcode];

        if (x == 1) check &= false;
        if (b == 1 and p == 1) check &= false;

        if (check){
            std::cout << GREEN << "Valid Instruction!" << RESET << '\n';
            std::cout << YELLOW << "Instruction Format: Format 3" << RESET << '\n';
            std::cout << GREEN << "n = " << n << " and " << "i = " << i << " => Immediate Addressing Type (for SIC/XE Instructions) " << RESET << '\n';
            std::cout << GREEN << "x = " << x;
            if (x == 0){
                std::cout << " => Direct Addressing Mode" << RESET << '\n';
            } else {
                std::cout << " => Indexed Addressing Mode" << RESET << '\n';
            }
            std::cout << GREEN << "b = " << b;
            if (b == 1){
                std::cout << " => Base-Relative Addressing Mode" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << GREEN << "p = " << p;
            if (p == 1){
                std::cout << " => PC-Relative Addressing Mode" << RESET << '\n'; 
            } else {
                std::cout << RESET << '\n';
            }
        } else {
            std::cout << RED << "Invalid Instruction!" << RESET << '\n';
            std::cout << RED << "Instruction Format: Format 3" << RESET << '\n';
            std::cout << RED << "n = " << n << " and " << "i = " << i << " => Immediate Addressing Type (for SIC/XE Instructions) " << RESET << '\n';
            std::cout << RED << "x = " << x;
            if (x == 0){
                std::cout << " => Direct Addressing Mode" << RESET << '\n';
            } else {
                std::cout << " => Indexed Addressing Mode" << RESET << '\n';
            }
            std::cout << RED << "b = " << b;
            if (b == 1){
                std::cout << " => Base-Relative Addressing Mode" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << RED << "p = " << p;
            if (p == 1){
                std::cout << " => PC-Relative Addressing Mode" << RESET << '\n'; 
            } else {
                std::cout << RESET << '\n';
            }
            if (h[11] == '1'){
                std::cout << RED << "Extended Bit Set => Wrong Instruction Format" << RESET << '\n';
            }
            if (!mp[opcode]){
                std::cout << RED << "Invalid Opcode Provided" << RESET << '\n';
            }
            if (b == 1 and p == 1){
                std::cout << RED << "Both Bits b and p Cannot Be Set!" << RESET << '\n';
            }
            if (x == 1){
                std::cout << RED << "Indexed Addressing Mode Cannot Be Used with Immediate Addressing Type" << RESET << '\n';
            }
        }
    }
}

void format4(std::string s){
    std::string h = gethex(s);

    std::string opcode = s.substr(0, 2);
    bool check = true;
    if (h[11] == '0') check &= false;
    
    int n = (h[6] == '1');
    int i = (h[7] == '1');
    int x = (h[8] == '1');
    int b = (h[9] == '1');
    int p = (h[10] == '1');
    int e = (h[11] == '1');

    if (n == 1 and i == 1){
        std::map<std::string, bool> mp;
        mp["1b"] = true;
        mp["5b"] = true;
        mp["43"] = true;
        mp["2b"] = true;
        mp["8b"] = true;
        mp["27"] = true;
        mp["67"] = true;
        mp["3f"] = true;
        mp["33"] = true;
        mp["37"] = true;
        mp["3b"] = true;
        mp["4b"] = true;
        mp["03"] = true;
        mp["6b"] = true;
        mp["53"] = true;
        mp["73"] = true;
        mp["0b"] = true;
        mp["6f"] = true;
        mp["77"] = true;
        mp["07"] = true;
        mp["d3"] = true;
        mp["23"] = true;
        mp["63"] = true;
        mp["47"] = true;
        mp["db"] = true;
        mp["4f"] = true;
        mp["ef"] = true;
        mp["0f"] = true;
        mp["7b"] = true;
        mp["57"] = true;
        mp["83"] = true;
        mp["d7"] = true;
        mp["17"] = true;
        mp["7f"] = true;
        mp["eb"] = true;
        mp["87"] = true;
        mp["13"] = true;
        mp["1f"] = true;
        mp["5f"] = true;
        mp["e3"] = true;
        mp["2f"] = true;
        mp["df"] = true;

        check &= mp[opcode];

        if (b == 1 or p == 1) check &= false;

        if (check){
            std::cout << GREEN << "Valid Instruction!" << RESET << '\n';
            std::cout << YELLOW << "Instruction Format: Format 4" << RESET << '\n';
            std::cout << GREEN << "n = " << n << " and " << "i = " << i << " => Simple Addressing Type (for SIC/XE Instructions) " << RESET << '\n';
            std::cout << GREEN << "x = " << x;
            if (x == 0){
                std::cout << " => Direct Addressing Mode" << RESET << '\n';
            } else {
                std::cout << " => Indexed Addressing Mode" << RESET << '\n';
            }
            std::cout << GREEN << "b = " << b;
            if (b == 1){
                std::cout << " => Base-Relative Addressing Mode" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << GREEN << "p = " << p;
            if (p == 1){
                std::cout << " => PC-Relative Addressing Mode" << RESET << '\n'; 
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << GREEN << "e = " << e;
            if (e == 1){
                std::cout << " => Extended Instruction Format" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }
        } else {
            std::cout << RED << "Invalid Instruction!" << RESET << '\n';
            std::cout << RED << "Instruction Format: Format 4" << RESET << '\n';
            std::cout << RED << "n = " << n << " and " << "i = " << i << " => Simple Addressing Type (for SIC/XE Instructions) " << RESET << '\n';
            std::cout << RED << "x = " << x;
            if (x == 0){
                std::cout << " => Direct Addressing Mode" << RESET << '\n';
            } else {
                std::cout << " => Indexed Addressing Mode" << RESET << '\n';
            }
            std::cout << RED << "b = " << b;
            if (b == 1){
                std::cout << " => Base-Relative Addressing Mode" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << RED << "p = " << p;
            if (p == 1){
                std::cout << " => PC-Relative Addressing Mode" << RESET << '\n'; 
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << RED << "e = " << e;
            if (e == 1){
                std::cout << " => Extended Instruction Format" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }

            if (!mp[opcode]){
                std::cout << RED << "Invalid Opcode Provided!" << RESET << '\n';
            }
            if (e == 0){
                std::cout << RED << "Extended Bit Must Be Set!" << RESET << '\n';
            }
            if (b == 1 or p == 1){
                std::cout << RED << "Bits b or p Cannot be Set in Extended Instruction Format" << RESET << '\n';
            }
        }
    } else if (n == 0 and i == 0){
        std::cout << RED << "Invalid Instruction!" << RESET << '\n';
        std::cout << RED << "Instruction Format: Format 4" << RESET << '\n';
        std::cout << RED << "n = " << n << " and " << "i = " << i << RESET << '\n';
        std::cout << RED << "x = " << x;
        if (x == 0){
            std::cout << " => Direct Addressing Mode" << RESET << '\n';
        } else {
            std::cout << " => Indexed Addressing Mode" << RESET << '\n';
        }
        std::cout << RED << "b = " << b;
        if (b == 1){
            std::cout << " => Base-Relative Addressing Mode" << RESET << '\n';
        } else {
            std::cout << RESET << '\n';
        }
        std::cout << RED << "p = " << p;
        if (p == 1){
            std::cout << " => PC-Relative Addressing Mode" << RESET << '\n'; 
        } else {
            std::cout << RESET << '\n';
        }
        std::cout << RED << "e = " << e;
        if (e == 1){
            std::cout << "Extended Instruction Format" << RESET << '\n';
        } else {
            std::cout << RESET << '\n';
        }

        if (e == 0){
            std::cout << RED << "Extended Bit Must Be Set!" << RESET << '\n';
        }
        if (b == 1 or p == 1){
            std::cout << RED << "Bits b or p Cannot be Set in Extended Instruction Format" << RESET << '\n';
        }
        if (n == 0 and i == 0){
            std::cout << RED << "Extended Instruction Format Cannot be Used with n = 0 and i = 0" << RESET << '\n';
        }

    } else if (n == 1 and i == 0){
        std::map<std::string, bool> mp;
        mp["1a"] = true;
        mp["5a"] = true;
        mp["42"] = true;
        mp["2a"] = true;
        mp["8a"] = true;
        mp["26"] = true;
        mp["66"] = true;
        mp["3e"] = true;
        mp["32"] = true;
        mp["36"] = true;
        mp["3a"] = true;
        mp["4a"] = true;
        mp["02"] = true;
        mp["6a"] = true;
        mp["52"] = true;
        mp["72"] = true;
        mp["0a"] = true;
        mp["6e"] = true;
        mp["76"] = true;
        mp["06"] = true;
        mp["d2"] = true;
        mp["22"] = true;
        mp["62"] = true;
        mp["46"] = true;
        mp["da"] = true;
        mp["4e"] = true;
        mp["ee"] = true;
        mp["0e"] = true;
        mp["7a"] = true;
        mp["56"] = true;
        mp["82"] = true;
        mp["d6"] = true;
        mp["16"] = true;
        mp["7e"] = true;
        mp["ea"] = true;
        mp["86"] = true;
        mp["12"] = true;
        mp["1e"] = true;
        mp["5e"] = true;
        mp["e2"] = true;
        mp["2e"] = true;
        mp["de"] = true;

        check &= mp[opcode];

        if (x == 1) check &= false;
        if (b == 1 or p == 1) check &= false;

        if (check){
            std::cout << GREEN << "Valid Instruction!" << RESET << '\n';
            std::cout << YELLOW << "Instruction Format: Format 4" << RESET << '\n';
            std::cout << GREEN << "n = " << n << " and " << "i = " << i << " => Indirect Addressing Type (for SIC/XE Instructions) " << RESET << '\n';
            std::cout << GREEN << "x = " << x;
            if (x == 0){
                std::cout << " => Direct Addressing Mode" << RESET << '\n';
            } else {
                std::cout << " => Indexed Addressing Mode" << RESET << '\n';
            }
            std::cout << GREEN << "b = " << b;
            if (b == 1){
                std::cout << " => Base-Relative Addressing Mode" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << GREEN << "p = " << p;
            if (p == 1){
                std::cout << " => PC-Relative Addressing Mode" << RESET << '\n'; 
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << GREEN << "e = " << e;
            if (e == 1){
                std::cout << " => Extended Instruction Format" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }
        } else {
            std::cout << RED << "Invalid Instruction!" << RESET << '\n';
            std::cout << RED << "Instruction Format: Format 4" << RESET << '\n';
            std::cout << RED << "n = " << n << " and " << "i = " << i << " => Indirect Addressing Type (for SIC/XE Instructions) " << RESET << '\n';
            std::cout << RED << "x = " << x;
            if (x == 0){
                std::cout << " => Direct Addressing Mode" << RESET << '\n';
            } else {
                std::cout << " => Indexed Addressing Mode" << RESET << '\n';
            }
            std::cout << RED << "b = " << b;
            if (b == 1){
                std::cout << " => Base-Relative Addressing Mode" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << RED << "p = " << p;
            if (p == 1){
                std::cout << " => PC-Relative Addressing Mode" << RESET << '\n'; 
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << RED << "e = " << e;
            if (e == 1){
                std::cout << " => Extended Instruction Format" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }

            if (!mp[opcode]){
                std::cout << RED << "Invalid Opcode Provided!" << RESET << '\n';
            }
            if (e == 0){
                std::cout << RED << "Extended Bit Must Be Set!" << RESET << '\n';
            }
            if (b == 1 or p == 1){
                std::cout << RED << "Bits b or p Cannot be Set in Extended Instruction Format" << RESET << '\n';
            }
            if (x == 1){
                std::cout << RED << "Indexed Addressing Mode Cannot Be Used with Indirect Addressing Type" << RESET << '\n';
            }
        }
    } else if (n == 0 and i == 1){
        std::map<std::string, bool> mp;
        mp["19"] = true;
        mp["59"] = true;
        mp["41"] = true;
        mp["29"] = true;
        mp["89"] = true;
        mp["25"] = true;
        mp["65"] = true;
        mp["3d"] = true;
        mp["31"] = true;
        mp["35"] = true;
        mp["39"] = true;
        mp["49"] = true;
        mp["01"] = true;
        mp["69"] = true;
        mp["51"] = true;
        mp["71"] = true;
        mp["09"] = true;
        mp["6d"] = true;
        mp["75"] = true;
        mp["05"] = true;
        mp["d1"] = true;
        mp["21"] = true;
        mp["61"] = true;
        mp["45"] = true;
        mp["d9"] = true;
        mp["4d"] = true;
        mp["ed"] = true;
        mp["0d"] = true;
        mp["79"] = true;
        mp["55"] = true;
        mp["81"] = true;
        mp["d5"] = true;
        mp["15"] = true;
        mp["7d"] = true;
        mp["e9"] = true;
        mp["85"] = true;
        mp["11"] = true;
        mp["1d"] = true;
        mp["5d"] = true;
        mp["e1"] = true;
        mp["2d"] = true;
        mp["dd"] = true;

        check &= mp[opcode];

        if (x == 1) check &= false;
        if (b == 1 or p == 1) check &= false;

        if (check){
            std::cout << GREEN << "Valid Instruction!" << RESET  << '\n';
            std::cout << YELLOW << "Instruction Format: Format 4" << RESET << '\n';
            std::cout << GREEN << "n = " << n << " and " << "i = " << i << " => Immediate Addressing Type (for SIC/XE Instructions) " << RESET << '\n';
            std::cout << GREEN << "x = " << x;
            if (x == 0){
                std::cout << " => Direct Addressing Mode" << RESET << '\n';
            } else {
                std::cout << " => Indexed Addressing Mode" << RESET << '\n';
            }
            std::cout << GREEN << "b = " << b;
            if (b == 1){
                std::cout << " => Base-Relative Addressing Mode" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << GREEN << "p = " << p;
            if (p == 1){
                std::cout << " => PC-Relative Addressing Mode" << RESET << '\n'; 
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << GREEN << "e = " << e;
            if (e == 1){
                std::cout << " => Extended Instruction Format" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }
        } else {
            std::cout << RED << "Invalid Instruction!" << RESET << '\n';
            std::cout << RED << "Instruction Format: Format 3" << RESET << '\n';
            std::cout << RED << "n = " << n << " and " << "i = " << i << " => Immediate Addressing Type (for SIC/XE Instructions) " << RESET << '\n';
            std::cout << RED << "x = " << x;
            if (x == 0){
                std::cout << " => Direct Addressing Mode" << RESET << '\n';
            } else {
                std::cout << " => Indexed Addressing Mode" << RESET << '\n';
            }
            std::cout << RED << "b = " << b;
            if (b == 1){
                std::cout << " => Base-Relative Addressing Mode" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << RED << "p = " << p;
            if (p == 1){
                std::cout << " => PC-Relative Addressing Mode" << RESET << '\n'; 
            } else {
                std::cout << RESET << '\n';
            }
            std::cout << RED << "e = " << e;
            if (e == 1){
                std::cout << " => Extended Instruction Format" << RESET << '\n';
            } else {
                std::cout << RESET << '\n';
            }

            if (!mp[opcode]){
                std::cout << RED << "Invalid Opcode Provided" << RESET << '\n';
            }
            if (e == 0){
                std::cout << RED << "Extended Bit Must Be Set!" << RESET << '\n';
            }
            if (b == 1 or p == 1){
                std::cout << RED << "Both Bits b and p Cannot Be Set!" << RESET << '\n';
            }
            if (x == 1){
                std::cout << RED << "Indexed Addressing Mode Cannot Be Used with Immediate Addressing Type" << RESET << '\n';
            }
        }
    }
}

int main() {
    std::string s;
    
    while (true){
        std::cout << "Enter your SIC or SIC/XE instruction (in hex): ";
        std::cin >> s;

        s = check(s);
        int len = s.length();

        switch (len) {
            case 2:
                format1(s);
                break;
            case 4:
                format2(s);
                break; 
            case 6:
                format3(s);
                break;
            case 8:
                format4(s);
                break; 
            default:
                std::cout << "Incorrect Instruction Length! Please Enter the correct instruction again" << '\n';
                break;
        }
    }
}