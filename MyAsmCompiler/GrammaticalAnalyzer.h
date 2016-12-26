#ifndef GRAMMATICALANALYZER_H
#define GRAMMATICALANALYZER_H

#include "PublicDefines.h"
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"

class GrammaticalAnalyzer {

private:
    vector<Segment> segmentTable;
    vector<Label> labelTable;
    map<string, string> assumeTable;
    map <string, string> regNumbers;
    map <string, string> segRegNumbers;
    //map <string, string> addr16;
    vector <string> listing;
    vector <int> lineOffsets;

    int isAlreadyDeclared(const string&);
    int isInSegTable(const string&);
    void assumeTableInit();
    void regNumbersInit();
    void segRegNumbersInit();
    string generateOpCode(const string&, const string&, int, int, bool, bool);
    string generateModRM(const string&, const string&, const string&, const string&, bool, bool);
    string generateSib(int, const string&);
    string generateJumpOpcode();
    /*bool isRegister32(const string &);
    bool isRegister16(const string &);
    bool isRegister8(const string &);*/

public:
    GrammaticalAnalyzer();
    void printAssumeTable();
    void printLabelTable();
    void printSegmentTable();
    void printListing();
    void generateListing(const vector< vector<Token> >&);
    //void secondPass(const vector<string> &);

};

#endif // GRAMMATICALANALYZER_H
