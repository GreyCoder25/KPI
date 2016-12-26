#include "GrammaticalAnalyzer.h"

GrammaticalAnalyzer::GrammaticalAnalyzer() {

    assumeTableInit();
    segRegNumbersInit();
    regNumbersInit();
}

void GrammaticalAnalyzer::generateListing(const vector< vector<Token> >& tokens) {

    SyntaxAnalyzer syn;
    Sentence currSentence;
    int ActiveSeg = -1;
    int currRowOffset = 0;
    string currSegDataReg = "DS";

    bool pref66;
    bool pref67;
    bool modrm, sib, opCode, value, offset, segPref, offset32, jmpIndir, jncUp, typesError;

    for (size_t i = 0; i < tokens.size(); ++i) {

        Label l;
        pref66 = false;
        pref67 = false;
        modrm = true;
        sib = opCode = value = offset = segPref = offset32 = false;
        jmpIndir = true;
        jncUp = true;
        typesError = false;
        string listingStr = "";
        int w = 1, s = 0, operCap = 0;
        int identOffset = 0, multVal = 0, immVal = 0;
        string segRegName = "", opCodeText = "";
        string firstOpReg = "", secondOpReg = "";
        string addrRegName;

        currSentence = syn.buildSentenceStructureTable(tokens[i]);
        lineOffsets.push_back(currRowOffset);

        if (currSentence.s.size() != 0) {
            if (currSentence.mL && tokens[i][currSentence.mFLN - 1].lexem != "ASSUME" || !currSentence.mL) {
                if (currRowOffset) {
                    //cout << setw (5);
                    for (int k = 0; k < (3 - (int)(log(currRowOffset) / log(16))); ++k)
                        listingStr += "0";
                    listingStr += intToHexString(currRowOffset) + " ";
                }
                else
                    listingStr += "0000 ";
            }
            //error checking

            if (tokens[i][0].type == WRONG_LEX) {
                for (size_t k = 0; k < 50 - listingStr.length(); ++k)
                    listingStr += " ";
                for (int k = 0; k < currSentence.s.size(); ++k)
                    listingStr += currSentence.s[k].lexem + " ";
                 listingStr += "\nERROR: Wrong lexem";
                 listing.push_back(listingStr);
                 continue;
            }
        }
        if (tokens[i].size() > 0 && tokens[i][0].type == IDENTIFIER && !currSentence.mL)
            if (!(tokens[i].size() > 1 && tokens[i][1].lexem == ":")) {
                for (size_t i = 0; i < 50 - listingStr.length(); ++i)
                    listingStr += " ";
                for (int i = 0; i < currSentence.s.size(); ++i)
                    listingStr += currSentence.s[i].lexem + " ";
                listingStr += "\nERROR: Wrong lexem";
                listing.push_back(listingStr);
                continue;
            }
        //label analyze
        if (currSentence.lOrN == true) {

            if (isAlreadyDeclared(tokens[i][0].lexem) && tokens[i][1].lexem != "ENDS") {
                for (size_t i = 0; i < 50 - listingStr.length(); ++i)
                    listingStr += " ";
                for (int i = 0; i < currSentence.s.size(); ++i)
                    listingStr += currSentence.s[i].lexem + " ";
                listingStr += "\nERROR: Identifier is already declared";
                listing.push_back(listingStr);
                continue;
            }
            else if (tokens[i][1].lexem != "ENDS" && tokens[i][1].lexem != "SEGMENT") {
                l.name = tokens[i][0].lexem;
                //cout << l.name << endl;
                l.value = currRowOffset;

                l.attr = segmentTable[ActiveSeg].name;
                //labelTable.push_back(l);
            }

        }
        //operation mnemocode analyze
        if (currSentence.mL == true) {

            LexemType mnemType = tokens[i][currSentence.mFLN - 1].type;
            if (mnemType == DIRECTIVE) {
                modrm = false;
                string mnemText = tokens[i][currSentence.mFLN - 1].lexem;
                if (mnemText == "DB" || mnemText == "DW" || mnemText == "DD") {
                    if (mnemText == "DB") {
                        l.type = "BYTE";
                        labelTable.push_back(l);
                        if (tokens[i][currSentence.mFLN].type == TEXT_CONST) {
                            currRowOffset += tokens[i][currSentence.mFLN].lexem.length() - 2;
                            for (size_t j = 1; j < tokens[i][currSentence.mFLN].lexem.length() - 1; ++j)
                                listingStr += intToHexString((int)(tokens[i][currSentence.mFLN].lexem[j])).substr(intToHexString((int)(tokens[i][currSentence.mFLN].lexem[j])).length() - 2, 2) + " ";
                        }
                        else {

                            currRowOffset += 1;
                        }
                    }
                    else if (mnemText == "DW") {
                        l.type = "WORD";
                        labelTable.push_back(l);
                        currRowOffset += 2;
                    }
                    else if (mnemText == "DD") {
                        l.type = "DWORD";
                        labelTable.push_back(l);
                        currRowOffset += 4;
                    }
                    l.value = currRowOffset;
                }
                else if (mnemText == "SEGMENT") {
                    if (!isInSegTable(tokens[i][0].lexem)) {
                        Segment seg;
                        seg.name = tokens[i][0].lexem;
                        segmentTable.push_back(seg);
                        ++ActiveSeg;
                    }
                    else
                        ActiveSeg = isInSegTable(tokens[i][0].lexem) - 1;
                }
                else if (mnemText == "ENDS") {
                    //ActiveSeg = 0;
                    segmentTable[ActiveSeg].length = currRowOffset;
                    currRowOffset = 0;
                }
                else if (mnemText == "ASSUME") {
                    for (size_t segRegIndex = 0; segRegIndex < currSentence.n.size(); ++segRegIndex)
                        assumeTable[tokens[i][currSentence.n[segRegIndex] - 1].lexem] = tokens[i][currSentence.n[segRegIndex] + 1].lexem;
                }
            }
            else if (mnemType == COMMAND) {
                string mnemText = tokens[i][currSentence.mFLN - 1].lexem;
                opCodeText = mnemText;
                if (mnemText == "POP" || mnemText == "STC" || mnemText == "CMP" || mnemText == "JMP")
                    currRowOffset += 1;
                else
                    currRowOffset += 2;

                if (mnemText == "CMP" || mnemText == "POP" || mnemText == "XOR" || mnemText == "MOV")
                    firstOpReg = tokens[i][currSentence.mFLN].lexem;
                if (mnemText == "MOV" || mnemText == "SUB" || mnemText == "XOR")
                    secondOpReg = tokens[i][currSentence.n[1] - 1].lexem;
                if (mnemText == "POP" || mnemText == "STC" || mnemText == "JNC")
                    modrm = false;
                if (mnemText == "JNC")
                    if (isAlreadyDeclared(tokens[i][currSentence.mFLN].lexem))
                        jncUp = false;
            }

        }
        //operands analyze
        if (currSentence.n.size() != 0) {
            for (size_t opIndex = 0; opIndex < currSentence.n.size(); ++opIndex) {
                LexOperTable t;
                for (size_t lexOpIndex = 0; lexOpIndex < currSentence.c[opIndex]; ++lexOpIndex) {
                    LexemType operLexType = tokens[i][currSentence.n[opIndex] + lexOpIndex - 1].type;

                    string operLexText = tokens[i][currSentence.n[opIndex] + lexOpIndex - 1].lexem;
                    //cout << "here" << endl;
                    if (operLexType == REG8 || operLexType == REG16 || operLexType == REG32) {
                        if (tokens[i][currSentence.n[opIndex] + lexOpIndex - 2].lexem != "[") {
                            t.hasReg = true;
                            t.regName = operLexText;
                            if (operLexType == REG8) {
                                t.regCap = 8;
                                w = 0;
                                //operCap = t.regCap;
                            }
                            else if (operLexType == REG16) {
                                t.regCap = 16;
                                //operCap = t.regCap;
                            }
                            else if (operLexType == REG32) {
                                t.regCap = 32;
                                //operCap = t.regCap;
                            }
                            if (operCap != 0 && operCap != t.regCap)
                                typesError = true;
                            operCap = t.regCap;
                        }
                        else {
                            t.hasAddrReg = true;
                            t.addrRegName = operLexText;
                            addrRegName = operLexText;
                            if (operLexType == REG8)
                                t.addrRegCap = 8;
                            else if (operLexType == REG16)
                                t.addrRegCap = 16;
                            else if (operLexType == REG32)
                                t.addrRegCap = 32;
                        }


                    }
                    else if (operLexType == TYPEDEF) {
                        if (operLexText != "PTR") {
                            t.hasPtr = true;
                            t.ptrType = operLexText;
                            if (operLexText == "WORD") {
                                pref66 = true;
                                if (operCap != 0 && operCap != 16)
                                    typesError = true;
                                operCap = 16;
                            }
                            else if (operLexText == "BYTE") {
                                w = 0;
                                if (operCap != 0 && operCap != 8)
                                    typesError = true;
                                operCap = 8;
                            }
                            else if (operLexText == "DWORD") {
                                if (operCap != 0 && operCap != 32)
                                    typesError = true;
                                operCap = 32;
                            }
                        }
                    }
                    else if (operLexType == SEG_REG) {
                        t.hasSegReplPref = true;
                        t.segRegName = operLexText;
                    }
                    else if (operLexType == IDENTIFIER) {
                        //cout << operLexText << endl;
                        int numRowInTableId;
                        if ( !(isInSegTable(operLexText)) ) {
                            if (numRowInTableId = isAlreadyDeclared(operLexText)) {
                                t.hasIdent = true;
                                t.numRowIdentTable = numRowInTableId - 1;
                                if (labelTable[numRowInTableId - 1].type == "WORD") {
                                    if (operCap != 0 && operCap != 16)
                                        typesError = true;
                                    pref66 = true;
                                    operCap = 16;
                                    offset32 = true;
                                }
                                else if (labelTable[numRowInTableId - 1].type == "BYTE") {
                                    if (operCap != 0 && operCap != 8)
                                        typesError = true;
                                    w = 0;
                                    operCap = 8;
                                    offset32 = true;
                                }
                                else if (labelTable[numRowInTableId - 1].type == "DWORD") {
                                    if (operCap != 0 && operCap != 32)
                                        typesError = true;
                                    operCap = 32;
                                    offset32 = true;
                                }

                                offset = true;
                                identOffset = labelTable[t.numRowIdentTable].value;
                            }
                            else {
                                t.hasUndeclIdent = true;
                            }
                        }
                    }
                    else if (operLexType == SINGLE_SYMB) {
                        if (operLexText == "*") {
                            t.hasMult = true;
                            sib = true;
                            offset = true;
                            identOffset = 0;
                        }
                    }
                    else if (operLexType == BIN_CONST || operLexType == DEC_CONST || operLexType == HEX_CONST) {
                        if (tokens[i][currSentence.n[opIndex] + lexOpIndex - 2].lexem != "*") {
                            t.hasConst = true;
                            value = true;
                            if (operLexType == BIN_CONST)
                                t.constVal = binStrToInt(operLexText);
                            else if (operLexType == DEC_CONST)
                                t.constVal = decStrToInt(operLexText);
                            else if (operLexType == HEX_CONST)
                                t.constVal = hexStrToInt(operLexText);
                            immVal = t.constVal;
                        }
                        else
                            multVal = decStrToInt(operLexText);
                    }

                }
                if (t.hasIdent || t.hasUndeclIdent)
                    currRowOffset += 4;
                if (t.hasMult)
                    currRowOffset += 5;
                if (t.hasReg)
                    if (t.regCap == 16)
                        pref66 = true;
                if (t.hasAddrReg)
                    if (t.addrRegCap == 16)
                        pref67 = true;
                if (t.hasPtr)
                    if (t.ptrType == "FAR") {
                        jmpIndir = false;
                        currRowOffset += 2;
                        modrm = false;
                    }
                if (t.hasSegReplPref && tokens[i][currSentence.mFLN - 1].lexem != "ASSUME")
                    if (t.segRegName != currSegDataReg) {
                        currRowOffset += 1;
                        segPref = true;
                        segRegName = t.segRegName;
                    }
                if (currSentence.mL && tokens[i][currSentence.mFLN - 1].lexem == "CMP") {
                    LexemType operLexType = tokens[i][currSentence.n[opIndex] - 1].type;
                    string cmpReg = tokens[i][currSentence.n[0] - 1].lexem;
                    if (operLexType == REG8 || operLexType == REG16 || operLexType == REG32) {
                        if (cmpReg != "AL" && cmpReg != "AX")
                            ++currRowOffset;
                        else {
                            modrm = false;
                            if (cmpReg == "AX")
                                ++currRowOffset;

                        }
                    }

                }
                if (currSentence.mL && tokens[i][currSentence.mFLN - 1].lexem == "JNC")
                    if (t.hasIdent)
                        currRowOffset -= 4;
                if (currSentence.mL && tokens[i][currSentence.mFLN - 1].lexem == "JMP")
                    if (!t.hasPtr)
                        currRowOffset += 1;
                if (t.hasConst) {
                    if (!(tokens[i][currSentence.mFLN - 1].lexem == "DB" ||
                          tokens[i][currSentence.mFLN - 1].lexem == "DW" ||
                          tokens[i][currSentence.mFLN - 1].lexem == "DD") )
                        currRowOffset += (int)(log(t.constVal) / log(256)) + 1;
                    if ((int)(log(t.constVal) / log(2)) + 1 < operCap)
                        s = 1;
                }
            }
        }
        if (typesError) {
            for (size_t k = 0; k < 50 - listingStr.length(); ++k)
                listingStr += " ";
            for (int k = 0; k < currSentence.s.size(); ++k)
                listingStr += currSentence.s[k].lexem + " ";
             listingStr += "\nERROR: Types mismatch";
             listing.push_back(listingStr);
             continue;
        }

        if (pref66)
            currRowOffset += 1;
        if (pref67)
            currRowOffset += 1;

        if (l.name != "" && l.type == "") {
            l.type = "NEAR";
            labelTable.push_back(l);
        }
        if (currSentence.mL)
            if (tokens[i][currSentence.mFLN - 1].type == COMMAND)
                opCode = true;
        //generate machine code
        if (segPref)
            listingStr += segRegNumbers[segRegName];
        if (pref67)
            listingStr += "67| ";
        if (pref66)
            listingStr += "66| ";
        if (opCode) {
            listingStr += generateOpCode(opCodeText, firstOpReg, s, w, jmpIndir, jncUp) + " ";
        }
        if (opCodeText == "JNC" && isAlreadyDeclared(tokens[i][currSentence.mFLN].lexem)) {
            listingStr += intToHexString(255 - (lineOffsets[i] + 1 - labelTable[isAlreadyDeclared(tokens[i][currSentence.mFLN].lexem) - 1].value));
        }

        if (modrm && listingStr != "") {
            string modrmStr = generateModRM(firstOpReg, secondOpReg, opCodeText, addrRegName, sib, offset32);
            if (modrmStr.length() == 1)
                listingStr += "0";
            listingStr += modrmStr;
        }
        if (sib) {
            listingStr += generateSib(multVal, addrRegName) + " ";
        }
        else
            listingStr += " ";

        if (offset) {
            if (opCodeText != "JNC" && opCodeText != "JMP") {
                if (identOffset != 0) {
                    for (int k = 0; k < (7 - (int)(log(identOffset) / log(16))); ++k)
                        listingStr += "0";
                    listingStr += intToHexString(identOffset) + " R ";
                }
                else if (multVal == 0)
                    listingStr += "00000000 R ";
                else
                    listingStr += "00000000 ";
            }
        }
        if (value) {
            string strVal = intToHexString(immVal);
            int numZero = 0;
            if (strVal.length() == 1 || strVal.length() == 3 || strVal.length() == 7)
                numZero = 1;
            else if (strVal.length() == 5)
                numZero = 3;

            for (int k = 0; k < numZero; ++k)
                listingStr += "0";
            listingStr += strVal + " ";
        }
        //write sentence

        if (currSentence.s.size() != 0) {
            //int a = listingStr.length();
            for (size_t i = 0; i < 50 - listingStr.length(); ++i)
                listingStr += " ";
            for (int i = 0; i < currSentence.s.size(); ++i)
                listingStr += currSentence.s[i].lexem + " ";
        }
        listing.push_back(listingStr);
    }

    for (size_t i = 0; i < tokens.size(); ++i) {
        currSentence = syn.buildSentenceStructureTable(tokens[i]);
        if (currSentence.mL) {
            string mnemText = tokens[i][currSentence.mFLN - 1].lexem;
            if (mnemText == "JMP") {
                string labelStr = tokens[i][tokens[i].size() - 1].lexem;
                int labelOffsetVal = labelTable[isAlreadyDeclared(labelStr) - 1].value;
                if (labelOffsetVal != 0) {
                    listing[i] +="\n";
                    for (int k = 0; k < (7 - (int)(log(labelOffsetVal) / log(16))); ++k)
                        listing[i] += "0";
                    listing[i] += intToHexString(labelOffsetVal) + " R ";
                }
                else
                    listing[i] += "\n00000000 ";
                if (tokens[i][currSentence.mFLN].lexem == "FAR")
                    listing[i] += "---- R ";
            }
            else if (mnemText == "JNC") {
                string labelStr = tokens[i][tokens[i].size() - 1].lexem;
                int labelOffsetVal = labelTable[isAlreadyDeclared(labelStr) - 1].value;
                if (labelOffsetVal > lineOffsets[i]) {
                    if (labelOffsetVal != 0) {
                        listing[i] +="\n";
                        for (int k = 0; k < (7 - (int)(log(labelOffsetVal) / log(16))); ++k)
                            listing[i] += "0";
                        listing[i] += intToHexString(labelOffsetVal) + " ";
                    }
                    listing[i] += " R ";
                }
            }
        }
    }
    //of.close();
}

int GrammaticalAnalyzer::isAlreadyDeclared(const string &labelName) {

    for (size_t i = 0; i < labelTable.size(); ++i) {
        if (labelName == labelTable[i].name)
            return (i + 1);
    }
    return 0;

}

int GrammaticalAnalyzer::isInSegTable(const string &segName) {

    for (size_t i = 0; i < segmentTable.size(); ++i)
        if (segName == segmentTable[i].name)
            return i + 1;
    return 0;
}

string GrammaticalAnalyzer::generateOpCode(const string& oCT, const string& firOpRegName, int s, int w, bool jInd, bool jUp) {

    string opCode = "";
    string wStr, sStr;
    if (w == 0)
        wStr = "0";
    else
        wStr = "1";

    if (s == 0)
        sStr = "0";
    else
        sStr = "1";

    if (oCT == "ADC")
        opCode = intToHexString(binStrToInt("100000" + sStr + wStr));
    else if (oCT == "CMP") {
        if (firOpRegName == "AL" || firOpRegName == "AX")
            opCode = intToHexString(binStrToInt("0011110" + wStr));
        else
            opCode = intToHexString(binStrToInt("100000" + sStr + wStr));
    }
    else if (oCT == "MOV")
        opCode = intToHexString(binStrToInt("1000101" + wStr));
    else if (oCT == "MUL")
        opCode = intToHexString(binStrToInt("1111011" + wStr));
    else if (oCT == "POP")
        opCode = intToHexString(binStrToInt("01011" + regNumbers[firOpRegName]));
    else if (oCT == "STC")
        opCode = intToHexString(binStrToInt("11111001"));
    else if (oCT == "SUB")
        opCode = intToHexString(binStrToInt("0010100" + wStr));
    else if (oCT == "XOR") {
        if (firOpRegName.length() >= 2)
            opCode = intToHexString(binStrToInt("0011001" + wStr));
        else
            opCode = intToHexString(binStrToInt("0011000" + wStr));
    }
    else if (oCT == "JMP") {
        if (jInd)
            opCode = intToHexString(binStrToInt("11111111"));
        else
            opCode = intToHexString(binStrToInt("11101010"));
    }
    else if (oCT == "JNC")
        if (jUp)
            opCode = "OF 83";
        else
            opCode = "73";


    return opCode;
}

string GrammaticalAnalyzer::generateModRM(const string &reg1, const string &reg2, const string &opCode, const string&aRN, bool sib, bool of32) {

    string modRM = "", mod = "", rm = "";
    if (reg1 != "" && reg2 != "")
        mod = "11";
    else
        mod = "00";

    if (sib)
        rm = "100";
    else if (of32)
        rm = "101";
    else if (aRN != "") {
        if (aRN.length() == 3)
            rm = regNumbers[aRN];
        else {
            if (aRN == "BX")
                rm = "111";
            else if (aRN == "SI")
                rm = "100";
            else if (aRN == "DI")
                rm = "101";
        }
    }

    if (opCode == "ADC")
        modRM = intToHexString(binStrToInt(mod + "010" + rm));
    else if (opCode == "CMP")
        modRM = intToHexString(binStrToInt("11111" + regNumbers[reg1]));
    else if (opCode == "JMP")
        modRM = intToHexString(binStrToInt(mod + "100" + rm));
    else if (opCode == "MOV")
        //if (reg1.length() >= 2 && reg2.length() >=2)
            modRM = intToHexString(binStrToInt("11" + regNumbers[reg1] + regNumbers[reg2]));
    else if (opCode == "MUL")    
        modRM = intToHexString(binStrToInt(mod + "100" + rm));
    else if (opCode == "SUB")
        modRM = intToHexString(binStrToInt(mod + regNumbers[reg2] + rm));
    else if (opCode == "XOR") {
        if (reg1.length() >= 2)
            modRM = intToHexString(binStrToInt(mod + regNumbers[reg1] + rm));
        else
            modRM = "14";
    }

    return modRM;
}

string GrammaticalAnalyzer::generateSib(int mult, const string &index) {

    string sib, sc, ind = regNumbers[index], base = "101";
    if (mult == 2)
        sc = "01";
    else if (mult == 4)
        sc = "10";
    else if (mult == 8)
        sc = "11";

    sib = intToHexString(binStrToInt(sc + ind + base));

    return sib;
}

void GrammaticalAnalyzer::assumeTableInit() {

    assumeTable.insert(std::pair<string, string>("CS", "Nothing") );
    assumeTable.insert(std::pair<string, string>("DS", "Nothing") );
    assumeTable.insert(std::pair<string, string>("ES", "Nothing") );
    assumeTable.insert(std::pair<string, string>("GS", "Nothing") );
    assumeTable.insert(std::pair<string, string>("FS", "Nothing") );
    assumeTable.insert(std::pair<string, string>("SS", "Nothing") );

}

void GrammaticalAnalyzer::segRegNumbersInit() {

    segRegNumbers.insert(std::pair<string, string>("CS", "2E: ") );
    segRegNumbers.insert(std::pair<string, string>("DS", "3E: ") );
    segRegNumbers.insert(std::pair<string, string>("ES", "26: ") );
    segRegNumbers.insert(std::pair<string, string>("GS", "65: ") );
    segRegNumbers.insert(std::pair<string, string>("FS", "64: ") );
    segRegNumbers.insert(std::pair<string, string>("SS", "36: ") );
}

void GrammaticalAnalyzer::regNumbersInit() {

    regNumbers.insert(std::pair<string, string>("AL", "000") );
    regNumbers.insert(std::pair<string, string>("CL", "001") );
    regNumbers.insert(std::pair<string, string>("DL", "010") );
    regNumbers.insert(std::pair<string, string>("BL", "011") );
    regNumbers.insert(std::pair<string, string>("AH", "100") );
    regNumbers.insert(std::pair<string, string>("CH", "101") );
    regNumbers.insert(std::pair<string, string>("DH", "110") );
    regNumbers.insert(std::pair<string, string>("BH", "111") );

    regNumbers.insert(std::pair<string, string>("AX", "000") );
    regNumbers.insert(std::pair<string, string>("CX", "001") );
    regNumbers.insert(std::pair<string, string>("DX", "010") );
    regNumbers.insert(std::pair<string, string>("BX", "011") );
    regNumbers.insert(std::pair<string, string>("SP", "100") );
    regNumbers.insert(std::pair<string, string>("BP", "101") );
    regNumbers.insert(std::pair<string, string>("SI", "110") );
    regNumbers.insert(std::pair<string, string>("DI", "111") );

    regNumbers.insert(std::pair<string, string>("EAX", "000") );
    regNumbers.insert(std::pair<string, string>("ECX", "001") );
    regNumbers.insert(std::pair<string, string>("EDX", "010") );
    regNumbers.insert(std::pair<string, string>("EBX", "011") );
    regNumbers.insert(std::pair<string, string>("ESP", "100") );
    regNumbers.insert(std::pair<string, string>("EBP", "101") );
    regNumbers.insert(std::pair<string, string>("ESI", "110") );
    regNumbers.insert(std::pair<string, string>("EDI", "111") );

}

void GrammaticalAnalyzer::printAssumeTable() {

    cout << endl;
    for (std::map <string, string>::iterator it = assumeTable.begin(); it != assumeTable.end(); ++it)
        cout << it->first << " - " << it->second << endl;
    cout << endl;


}

void GrammaticalAnalyzer::printLabelTable() {

    cout << endl;

    cout << "Symbols:" << endl;
    cout << "        N a m e         	Type	 Value	 Attr" << endl;
    for (size_t i = 0 ; i < labelTable.size(); ++i) {
        cout << setprecision(ios::left) << setw(10) << labelTable[i].name  << setprecision(ios::left)
             << setw(26) << labelTable[i].type << setw(8) << labelTable[i].value << " "
             << setw(8) << labelTable[i].attr << endl;
    }

    cout << endl;

}

void GrammaticalAnalyzer::printSegmentTable() {

    cout << endl;
    cout << "Segments and Groups:" << endl
         << "        N a m e         	Size	Length	 Align	Combine Class" << endl;
    for (size_t i = 0 ; i < segmentTable.size(); ++i) {
        cout << segmentTable[i].name << setw(30) << std::dec << segmentTable[i].size << setw(8)
             << std::hex << segmentTable[i].length << setw(10)
             << segmentTable[i].align << setw(8) << segmentTable[i].combine << endl;
    }


    cout << endl;
}

void GrammaticalAnalyzer::printListing() {

    for (size_t i = 0; i < listing.size(); ++i)
        cout << listing[i] << endl;

}
