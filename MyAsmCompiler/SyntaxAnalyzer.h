#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H

#include "PublicDefines.h"

class SyntaxAnalyzer {

public:
    SyntaxAnalyzer();
    SyntaxAnalyzer(const vector < vector<Token> > &);
    ~SyntaxAnalyzer();
    Sentence buildSentenceStructureTable(const vector<Token> &);
    void printSentenceStructureTable(const char *, const Sentence &);
    void showSentenceStructureTable(const Sentence &);

private:
    vector < vector<Token> > codeTokens;

    bool isIdentifier(const Token &);
};

#endif // SYNTAXANALYZER_H
