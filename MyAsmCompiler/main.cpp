#include <iostream>
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "GrammaticalAnalyzer.h"

int main() {

    LexicalAnalyzer lex("/home/serhiy/MyAsmCompiler/ToRecognize.txt");
    lex.inputCode("/home/serhiy/MyAsmCompiler/CodeToCompile.asm");
    lex.makeTokens();
    lex.printLexemTable("/home/serhiy/MyAsmCompiler/lexemTable.txt");

    GrammaticalAnalyzer gr;
    gr.generateListing(lex.getTokensTable());

    gr.printListing();
    //gr.printAssumeTable();
    gr.printLabelTable();
    gr.printSegmentTable();

}
