#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include "PublicDefines.h"

class LexicalAnalyzer {

public:
    LexicalAnalyzer(const char *);
    ~LexicalAnalyzer();
    void inputCode(const char *);
    void printLexemTable();
    void printLexemTable(const char *);
    void makeTokens();
    const vector < vector<Token> >& getTokensTable();
    int getCodeSize();

private:
    void splitToLexems();
    //void makeTokens();

    vector < vector<string> > lexems;
    vector < vector<Token> > tokens;
    vector<string> code;

    set<string> directives;
    set<string> registers32;
    set<string> registers16;
    set<string> registers8;
    set<string> segmentRegisters;
    set<string> commands;
    set<string> typedefOperators;

    string alphabet, idChars, numChars, singleCharLexems, lexDividers, quoteChars;

    bool isDirective(const string &);
    bool isRegister32(const string &);
    bool isRegister16(const string &);
    bool isRegister8(const string &);
    bool isSegmentRegister(const string &);
    bool isCommand(const string &);
    bool isTypedefOperator(const string &);
    bool inAlphabet(char);
    bool isIdChar(char);
    bool isNumChar(char);
    bool isSingleCharLexem(char);
    bool isLexDivider(char);
    bool isQuoteChar(char);

};

#endif // LEXICALANALYZER_H
