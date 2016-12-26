#ifndef PUBLICDEFINES_H
#define PUBLICDEFINES_H

#include <sstream>
#include <string>

using std::string;

#include <vector>

using std::vector;

#include <set>

using std::set;

#include <map>

using std::map;

#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::ios;

#include <iomanip>

using std::setw;

#include <fstream>

using std::ifstream;
using std::ofstream;

#include <cstdlib>

using std::exit;

#include <cmath>

enum LexemType { IDENTIFIER, COMMAND, SINGLE_SYMB, TEXT_CONST, BIN_CONST, DEC_CONST,
                 HEX_CONST, DIRECTIVE, REG32, REG16, REG8, SEG_REG, WRONG_LEX, TYPEDEF };

struct Token {
    string lexem;
    LexemType type;
};

struct Sentence {
    bool lOrN; //labelOrName
    bool mL;   //mnemLex
    int mFLN;  //mnemFirstLexNumber
    vector<int> n; //operandFirstLexNumbers
    vector<int> c; //operandFirstLexCounts
    vector<Token> s; //text of the sentence
};

struct Segment {
    Segment() {
        name = "";
        size = 32;
        length = 0;
        align = "PARA";
        combine = "NONE";
    }

    string name;
    int size;
    int length;
    string align;
    string combine;
};

struct Label {
    Label() {
        name = "";
        type = "";
        value = 0;
        attr = "";
    }
    string name;
    string type;
    int value;
    string attr;
};

struct LexOperTable {
    LexOperTable () {
        hasReg = hasPtr = hasSegReplPref = hasUndeclIdent = hasAddrReg = hasMult = hasConst = hasIdent = false;
        regCap = numRowIdentTable = addrRegCap = regMultNum = regMultVal = constVal = -1;
        ptrType = regName = addrRegName = segRegName = "";
    }

    bool hasReg;
    int regCap;
    string regName;

    bool hasPtr;
    string ptrType;

    bool hasSegReplPref;
    string segRegName;

    bool hasIdent;
    int numRowIdentTable;

    bool hasUndeclIdent;

    bool hasAddrReg;
    string addrRegName;
    int addrRegCap;

    bool hasMult;
    int regMultNum;
    int regMultVal;

    bool hasConst;
    int  constVal;

};

static int binStrToInt (const string& binStr) {

    int val = 0;
    for (int i = 0; binStr[i] != 'B' && i < binStr.size(); ++i) {
        val *= 2;
        if (binStr[i] == '1')
            ++val;
    }

    return val;
}

static int decStrToInt (const string& decStr) {

    int val = 0;
    for (size_t i = 0; decStr[i] != 'D' && i < decStr.size(); ++i) {
        val *= 10;
        val += (int)decStr[i] - 48;
    }
    return val;

}

static int hexStrToInt (const string& hexStr) {

    int val = 0;
    for (size_t i = 0; hexStr[i] != 'H' && i < hexStr.size(); ++i) {
        val *= 16;
        if (hexStr[i] <= '9')
            val += (int)hexStr[i] - 48;
        else
            val += (int)hexStr[i] - 55;
    }
    return val;

}

static string intToHexString(int intValue) {

    string hexStr;

    /// integer value to hex-string
    std::stringstream sstream;
    sstream << std::hex << (int)intValue;

    hexStr= sstream.str();
    sstream.clear();    //clears out the stream-string

    return hexStr;
}

#endif // PUBLICDEFINES_H
