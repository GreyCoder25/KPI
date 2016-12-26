#include "SyntaxAnalyzer.h"

SyntaxAnalyzer::SyntaxAnalyzer(const vector< vector<Token> > &codeToks){

    codeTokens = codeToks;

}

SyntaxAnalyzer::SyntaxAnalyzer(){

}

SyntaxAnalyzer::~SyntaxAnalyzer(){

}

bool SyntaxAnalyzer::isIdentifier(const Token &lex){

    return (lex.type == IDENTIFIER);

}

Sentence SyntaxAnalyzer::buildSentenceStructureTable(const vector<Token> &sentence){

    bool labelOrName = false;
    bool mnemLex = false;
    int mnemFirstLexNum = 0;
    vector<int> operandLexCounts;
    vector<int> operandFirstLexNumbers;

    if (sentence.size() != 0) {

        int i = 0;
        if (sentence.size() >= 2) {
            if ( isIdentifier(sentence[0]) && sentence[1].lexem == ":" ) {
                labelOrName = true;
                i = 2;
            }
            else if ( (isIdentifier(sentence[0]) && sentence[1].type == DIRECTIVE)) {
                labelOrName = true;
                i = 1;
            }
        }

        mnemFirstLexNum = i + 1;
        if (sentence[i].type == COMMAND || sentence[i].type == DIRECTIVE) {
                mnemLex = true;
                ++i;
            }
            else {
                mnemLex = false;
                mnemFirstLexNum = 0;
            }

        for (; i < sentence.size(); ++i) {
            operandLexCounts.push_back(0);
            operandFirstLexNumbers.push_back(i + 1);
            for (; i < sentence.size() && sentence[i].lexem != ","; ++i) {
                ++operandLexCounts[operandLexCounts.size() - 1];
            }
        }
    }

    Sentence retS;
    retS.lOrN = labelOrName;
    retS.mL = mnemLex;
    retS.mFLN = mnemFirstLexNum;
    retS.c = operandLexCounts;
    retS.n = operandFirstLexNumbers;
    retS.s = sentence;

    return retS;
}

void SyntaxAnalyzer::printSentenceStructureTable(const char *fn, const Sentence &s) {

    ofstream of(fn, ios::app);

    for (int j = 0; j < s.s.size(); ++j)
        of<<s.s[j].lexem<<' ';
    of<<endl;

    of<<"Label field"<<setw(20)<<"Mnemocode field";
    for (int j = 0; j < s.c.size(); ++j)
        of<<setw(7)<<j + 1<<" operand field"<<setw(10);
    of<<endl;

    of<<setw(5)<<s.lOrN<<setw(15)<<s.mFLN<<setw(10)<<s.mL;
    for (int j = 0; j < s.c.size(); ++j)
        of<<setw(10)<<s.n[j]<<setw(10)<<s.c[j];
    of<<endl<<endl;

    of.close();
}

void SyntaxAnalyzer::showSentenceStructureTable(const Sentence &s) {

    for (int j = 0; j < s.s.size(); ++j)
        cout<<s.s[j].lexem<<' ';
    cout<<endl;

    cout<<"Label field"<<setw(20)<<"Mnemocode field";
    for (int j = 0; j < s.c.size(); ++j)
        cout<<setw(7)<<j + 1<<" operand field";
    cout<<endl;

    cout<<"Lex num"<<setw(15)<<"№"<<setw(10)<<"num";
    for (int j = 0; j < s.c.size(); ++j)
        cout<<setw(12)<<"№"<<setw(10)<<"num";
    cout<<endl;

    cout<<setw(5)<<s.lOrN<<setw(15)<<s.mFLN<<setw(10)<<s.mL;
    for (int j = 0; j < s.c.size(); ++j)
        cout<<setw(10)<<s.n[j]<<setw(10)<<s.c[j];
    cout<<endl<<endl;

}

