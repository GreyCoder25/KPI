#include "LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer(const char *recLexFile) {

    ifstream rlf(recLexFile, ios::in);

    if (!rlf){
        cerr<<"Opening file error"<<endl;
        exit(1);
    }

    string buf;

    while (rlf>>buf && buf != ";")
        directives.insert(buf);

    while (rlf>>buf && buf != ";")
        typedefOperators.insert(buf);

    while (rlf>>buf && buf != ";")
        registers32.insert(buf);

    while (rlf>>buf && buf != ";")
        registers16.insert(buf);

    while (rlf>>buf && buf != ";")
        registers8.insert(buf);

    while (rlf>>buf && buf != ";")
        segmentRegisters.insert(buf);

    while (rlf>>buf && buf != ";")
        commands.insert(buf);

    std::getline(rlf, alphabet);//!
    std::getline(rlf, alphabet);
    std::getline(rlf, idChars);
    std::getline(rlf, numChars);
    std::getline(rlf, singleCharLexems);
    lexDividers += (char)0x9;
    lexDividers += ' ';
    std::getline(rlf, quoteChars);

}

LexicalAnalyzer::~LexicalAnalyzer() {

}

const vector <vector <Token> >& LexicalAnalyzer::getTokensTable(){

    return tokens;

}

int LexicalAnalyzer::getCodeSize() {

    return code.size();

}

bool LexicalAnalyzer::isDirective(const string &s) { return directives.find(s) != directives.end(); }

bool LexicalAnalyzer::isRegister32(const string &s) { return registers32.find(s) != registers32.end(); }

bool LexicalAnalyzer::isRegister16(const string &s) { return registers16.find(s) != registers16.end(); }

bool LexicalAnalyzer::isRegister8(const string &s) { return registers8.find(s) != registers8.end(); }

bool LexicalAnalyzer::isSegmentRegister(const string &s) { return segmentRegisters.find(s) != segmentRegisters.end(); }

bool LexicalAnalyzer::isCommand(const string &s) { return commands.find(s) != commands.end(); }

bool LexicalAnalyzer::isTypedefOperator(const string &s) { return typedefOperators.find(s) != typedefOperators.end(); }

bool LexicalAnalyzer::inAlphabet(char c) { return alphabet.find(c) != string::npos; }

bool LexicalAnalyzer::isIdChar(char c) { return idChars.find(c) != string::npos; }

bool LexicalAnalyzer::isNumChar(char c) { return numChars.find(c) != string::npos; }

bool LexicalAnalyzer::isSingleCharLexem(char c) { return singleCharLexems.find(c) != string::npos; }

bool LexicalAnalyzer::isLexDivider(char c) { return lexDividers.find(c) != string::npos; }

bool LexicalAnalyzer::isQuoteChar(char c) { return quoteChars.find(c) != string::npos; }

void LexicalAnalyzer::inputCode(const char *codeFileName) {

    ifstream cf(codeFileName, ios::in);

    if (!cf) {
        cerr<<"Opening file error"<<endl;
        exit(1);
    }

    string buf;
    while(getline(cf, buf))
        code.push_back(buf);

    cf.close();

    for (size_t i = 0; i < code.size(); ++i) {
        bool quote = false;
        for (size_t j = 0; j < code[i].size(); ++j) {
            if (isQuoteChar(code[i][j]) && !quote)
                quote = true;
            else if (isQuoteChar(code[i][j]) && quote)
                quote = false;
            if (!quote)
                code[i][j] = toupper(code[i][j]);
        }
    }

    //for (int i = 0; i < code.size(); ++i)
    //    cout<<code[i]<<endl;
    lexems.resize(code.size());
    tokens.resize(code.size());
}

void LexicalAnalyzer::splitToLexems() {

    for (size_t i = 0; i < code.size(); ++i) {
        string buf;
        for (size_t j = 0; j < code[i].size(); ++j) {
            if ( isLexDivider(code[i][j]) ) {
                if (!buf.empty()) {
                    lexems[i].push_back(buf);
                    buf.clear();
                }
            }
            else if (isSingleCharLexem(code[i][j])) {
                if (!buf.empty()) {
                    lexems[i].push_back(buf);
                    buf.clear();
                }
                buf += code[i][j];
                lexems[i].push_back(buf);
                buf.clear();
            }
            else {
                buf += code[i][j];
            }
        }
        if (!buf.empty()) {
            lexems[i].push_back(buf);
            buf.clear();
        }
    }

    /*for (int i = 0; i < lexems.size(); ++i){
        for (int j = 0; j < lexems[i].size(); ++j)
            cout<<lexems[i][j]<<' ';
        cout<<endl;
    }*/

}

void LexicalAnalyzer::makeTokens() {

    splitToLexems();

    for (size_t i = 0; i < lexems.size(); ++i) {
        Token tmp;
        for (size_t j = 0; j < lexems[i].size(); ++j) {

            tmp.lexem = lexems[i][j];

            if (isDirective(tmp.lexem))
                tmp.type = DIRECTIVE;
            else if (isTypedefOperator(tmp.lexem))
                tmp.type = TYPEDEF;
            else if (isRegister32(tmp.lexem))
                tmp.type = REG32;
            else if (isRegister16(tmp.lexem))
                tmp.type = REG16;
            else if (isRegister8(tmp.lexem))
                tmp.type = REG8;
            else if (isSegmentRegister(tmp.lexem))
                tmp.type = SEG_REG;
            else if (isCommand(tmp.lexem))
                tmp.type = COMMAND;
            else if ( isQuoteChar(tmp.lexem[0]) && isQuoteChar(tmp.lexem[tmp.lexem.length() - 1]) )
                tmp.type = TEXT_CONST;
            else if ( isNumChar(tmp.lexem[0]) ) {
                if (tmp.lexem[tmp.lexem.length() - 1] == 'B') {
                    tmp.type = BIN_CONST;
                    for (size_t i = 0; i < tmp.lexem.length() - 1; ++i)
                        if (tmp.lexem[i] != '0' && tmp.lexem[i] != '1') {
                            tmp.type = WRONG_LEX;
                            break;
                        }
                }
                else if (tmp.lexem[tmp.lexem.length() - 1] == 'D' || isNumChar(tmp.lexem[tmp.lexem.length() - 1])) {
                    tmp.type = DEC_CONST;
                    for (size_t i = 0; i < tmp.lexem.length() - 1; ++i)
                        if ( !isNumChar(tmp.lexem[i]) ) {
                            tmp.type = WRONG_LEX;
                            break;
                        }
                }
                else if (tmp.lexem[tmp.lexem.length() - 1] == 'H') {
                    tmp.type = HEX_CONST;
                    for (size_t i = 0; i < tmp.lexem.length() - 1; ++i)
                        if ( !isNumChar(tmp.lexem[i]) && !(tmp.lexem[i] >= 'A' && tmp.lexem[i] <= 'F') ) {
                            tmp.type = WRONG_LEX;
                            break;
                        }
                }
                else {
                    tmp.type = WRONG_LEX;
                }
            }
            else if (tmp.lexem.length() == 1) {
                if (isSingleCharLexem(tmp.lexem[0]))
                    tmp.type = SINGLE_SYMB;
                else
                    tmp.type = IDENTIFIER;
            }
            else{
                tmp.type = IDENTIFIER;
                for (size_t i = 0; i <  tmp.lexem.length(); ++i)
                    if ( !isIdChar(tmp.lexem[i]) ) {
                        tmp.type = WRONG_LEX;
                        break;
                    }
            }
            tokens[i].push_back(tmp);
        }
    }

}

void LexicalAnalyzer::printLexemTable() {

    for (size_t i = 0; i < tokens.size(); ++i) {
        cout<<(i + 1)<<" row:"<<endl;
        cout<<setw(20)<<"Lexem"<<setw(20)<<"length"<<setw(20)<<"Type"<<endl;
        for (size_t j = 0; j < tokens[i].size(); ++j) {
            cout<<setw(20)<<tokens[i][j].lexem<<setw(20)<<tokens[i][j].lexem.length()<<setw(20);

            if (tokens[i][j].type == DIRECTIVE)
                cout<<"DIRECTIVE"<<endl;
            else if (tokens[i][j].type == TYPEDEF)
                cout<<"TYPEDEF OPERATOR"<<endl;
            else if (tokens[i][j].type == REG32)
                cout<<"REG32"<<endl;
            else if (tokens[i][j].type == REG16)
                cout<<"REG16"<<endl;
            else if (tokens[i][j].type == REG8)
                cout<<"REG8"<<endl;
            else if (tokens[i][j].type == COMMAND)
                cout<<"COMMAND"<<endl;
            else if (tokens[i][j].type == SEG_REG)
                cout<<"SEG_REG"<<endl;
            else if (tokens[i][j].type == IDENTIFIER)
                cout<<"IDENTIFIER"<<endl;
            else if (tokens[i][j].type == SINGLE_SYMB)
                cout<<"SINGLE_SYMB"<<endl;
            else if (tokens[i][j].type == TEXT_CONST)
                cout<<"TEXT_CONST"<<endl;
            else if (tokens[i][j].type == BIN_CONST)
                cout<<"BIN_CONST"<<endl;
            else if (tokens[i][j].type == DEC_CONST)
                cout<<"DEC_CONST"<<endl;
            else if (tokens[i][j].type == HEX_CONST)
                cout<<"HEX_CONST"<<endl;
            else if (tokens[i][j].type == WRONG_LEX)
                cout<<"WRONG_LEX"<<endl;

        }
        cout<<endl;
    }

}

void LexicalAnalyzer::printLexemTable(const char *outputFile) {

    ofstream of(outputFile);

    for (size_t i = 0; i < tokens.size(); ++i) {
        of<<(i + 1)<<" row:"<<endl;
        of<<setw(20)<<"Lexem"<<setw(20)<<"length"<<setw(20)<<"Type"<<endl;
        for (size_t j = 0; j < tokens[i].size(); ++j) {
            of<<setw(20)<<tokens[i][j].lexem<<setw(20)<<tokens[i][j].lexem.length()<<setw(20);

            if (tokens[i][j].type == DIRECTIVE)
                of<<"DIRECTIVE"<<endl;
            else if (tokens[i][j].type == TYPEDEF)
                of<<"TYPEDEF OPERATOR"<<endl;
            else if (tokens[i][j].type == REG32)
                of<<"REG32"<<endl;
            else if (tokens[i][j].type == REG16)
                of<<"REG16"<<endl;
            else if (tokens[i][j].type == REG8)
                of<<"REG8"<<endl;
            else if (tokens[i][j].type == COMMAND)
                of<<"COMMAND"<<endl;
            else if (tokens[i][j].type == SEG_REG)
                of<<"SEG_REG"<<endl;
            else if (tokens[i][j].type == IDENTIFIER)
                of<<"IDENTIFIER"<<endl;
            else if (tokens[i][j].type == SINGLE_SYMB)
                of<<"SINGLE_SYMB"<<endl;
            else if (tokens[i][j].type == TEXT_CONST)
                of<<"TEXT_CONST"<<endl;
            else if (tokens[i][j].type == BIN_CONST)
                of<<"BIN_CONST"<<endl;
            else if (tokens[i][j].type == DEC_CONST)
                of<<"DEC_CONST"<<endl;
            else if (tokens[i][j].type == HEX_CONST)
                of<<"HEX_CONST"<<endl;
            else if (tokens[i][j].type == WRONG_LEX)
                of<<"WRONG_LEX"<<endl;

        }
        of<<endl;
    }
    of.close();

}
