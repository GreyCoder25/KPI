#-------------------------------------------------
#
# Project created by QtCreator 2016-03-16T14:33:14
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = MyAsmCompiler
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    LexicalAnalyzer.cpp \
    SyntaxAnalyzer.cpp \
    GrammaticalAnalyzer.cpp

HEADERS += \
    LexicalAnalyzer.h \
    PublicDefines.h \
    SyntaxAnalyzer.h \
    GrammaticalAnalyzer.h

OTHER_FILES += \
    CodeToCompile.asm \
    ToRecognize.txt \
    lexemTable.txt \
    sentenceStructure.txt \
    listing.lst
